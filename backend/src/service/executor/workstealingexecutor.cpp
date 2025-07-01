#include "workstealingexecutor.h"

#include "service/executor/executiontask.h"

#include "service/algorithm/solutioncollector.h"

WorkStealingExecutor::WorkStealingExecutor(int numThreads)
    : m_numThreads(numThreads),
      m_queues(numThreads),
      m_mutexes(numThreads),  
      m_solutionCollector(std::make_shared<SolutionCollector>()) {
    
    // Start worker threads
    m_workers.reserve(numThreads);
    for (int i = 0; i < m_numThreads; i++) {
        m_workers.emplace_back([this, i]() { this->worker(i); });
    }
}

WorkStealingExecutor::~WorkStealingExecutor() {
    // Signal stop
    m_stop.store(true, std::memory_order_release);
    m_running.store(false, std::memory_order_release);
    
    // Wake up all waiting threads
    {
        std::lock_guard<std::mutex> lock(m_cvMutex);
        m_cv.notify_all();
    }
    
    // Wait for all workers to finish
    for (auto& worker : m_workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void WorkStealingExecutor::add(const std::shared_ptr<IAlgorithm>& algo, 
                              const std::shared_ptr<IProblem>& problem) {
    if (m_stop.load(std::memory_order_acquire)) {
        return;  // Don't add tasks if stopping
    }
    
    // Round-robin task assignment
    int targetQueue = m_nextQueue.fetch_add(1, std::memory_order_relaxed) % m_numThreads;
    
    {
        std::lock_guard<std::mutex> lock(m_mutexes[targetQueue]);
        m_queues[targetQueue].emplace_back(std::make_unique<ExecutionTask>(algo, problem));
    }
    
    // Notify waiting workers
    if (m_running.load(std::memory_order_acquire)) {
        std::lock_guard<std::mutex> lock(m_cvMutex);
        m_cv.notify_all();
    }
}

void WorkStealingExecutor::run() {
    if (m_stop.load(std::memory_order_acquire)) {
        return;
    }
    
    // Start execution
    m_running.store(true, std::memory_order_release);
    
    // Wake up all workers
    {
        std::lock_guard<std::mutex> lock(m_cvMutex);
        m_cv.notify_all();
    }
    
    // Wait for all tasks to complete
    while (m_running.load(std::memory_order_acquire) && !m_stop.load(std::memory_order_acquire)) {
        bool allEmpty = true;
        
        // Check if all queues are empty
        for (int i = 0; i < m_numThreads; ++i) {
            std::lock_guard<std::mutex> lock(m_mutexes[i]);
            if (!m_queues[i].empty()) {
                allEmpty = false;
                break;
            }
        }
        
        if (allEmpty) {
            // Give a small grace period for workers to finish current tasks
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            
            // Check again to be sure
            allEmpty = true;
            for (int i = 0; i < m_numThreads; ++i) {
                std::lock_guard<std::mutex> lock(m_mutexes[i]);
                if (!m_queues[i].empty()) {
                    allEmpty = false;
                    break;
                }
            }
            
            if (allEmpty) {
                break;
            }
        }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    
    m_running.store(false, std::memory_order_release);
}

void WorkStealingExecutor::clear() {
    // Stop execution
    bool wasRunning = m_running.exchange(false, std::memory_order_acq_rel);
    
    // Clear all queues
    for (int i = 0; i < m_numThreads; ++i) {
        std::lock_guard<std::mutex> lock(m_mutexes[i]);
        m_queues[i].clear();
    }
    
    // Create new solution collector
    {
        std::lock_guard<std::mutex> lock(m_solutionMutex);
        m_solutionCollector = std::make_shared<SolutionCollector>();
    }
}

const std::shared_ptr<ISolutionCollector>& WorkStealingExecutor::getSolutionCollector() const {
    return m_solutionCollector;
}

bool WorkStealingExecutor::tryStealTask(int workerId, std::unique_ptr<IExecutionTask>& task) {
    thread_local std::random_device rd;
    thread_local std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(0, m_numThreads - 1);
    
    // Try to steal from random queues
    for (int attempt = 0; attempt < m_numThreads; ++attempt) {
        int victim = dist(rng);
        if (victim == workerId) {
            continue;  // Don't steal from self
        }
        
        // Try to lock victim's queue (non-blocking to avoid deadlock)
        std::unique_lock<std::mutex> victimLock(m_mutexes[victim], std::try_to_lock);
        if (victimLock.owns_lock() && !m_queues[victim].empty()) {
            // Steal from back (LIFO) for better cache locality
            task = std::move(m_queues[victim].back());
            m_queues[victim].pop_back();
            return true;
        }
    }
    
    return false;
}

void WorkStealingExecutor::worker(int id) {
    m_activeWorkers.fetch_add(1, std::memory_order_relaxed);
    
    while (!m_stop.load(std::memory_order_acquire)) {
        std::unique_ptr<IExecutionTask> task = nullptr;
        
        // Try to get task from own queue first
        {
            std::lock_guard<std::mutex> lock(m_mutexes[id]);
            if (!m_queues[id].empty()) {
                task = std::move(m_queues[id].front());
                m_queues[id].pop_front();
            }
        }
        
        // If no task in own queue and we're running, try work stealing
        if (!task && m_running.load(std::memory_order_acquire)) {
            tryStealTask(id, task);
        }
        
        // Execute task if found
        if (task) {
            try {
                auto solution = task->execute();
                if (solution) {
                    // Thread-safe solution collection
                    std::lock_guard<std::mutex> lock(m_solutionMutex);
                    if (m_solutionCollector) {  // Check if still valid
                        m_solutionCollector->addSolution(solution);
                    }
                }
            } catch (const std::exception& e) {
                // Log error if logging is available
                // For now, just continue with next task
            } catch (...) {
                // Handle any other exceptions
            }
        } else if (!m_stop.load(std::memory_order_acquire)) {
            // Wait for new tasks or stop signal
            std::unique_lock<std::mutex> lock(m_cvMutex);
            m_cv.wait_for(lock, std::chrono::milliseconds(50), [this]() {
                return m_stop.load(std::memory_order_acquire) || 
                       m_running.load(std::memory_order_acquire);
            });
        }
    }
    
    m_activeWorkers.fetch_sub(1, std::memory_order_relaxed);
}

std::vector<size_t> WorkStealingExecutor::getQueueSizes() const {
    std::vector<size_t> sizes(m_numThreads, 0);
    for (int i = 0; i < m_numThreads; ++i) {
        //std::lock_guard<std::mutex> lock(m_mutexes[i]);
        sizes[i] = m_queues[i].size();
    }
    return sizes;
}