#pragma once

#include "service/executor/iexecutor.h"

#include "service/algorithm/isolutioncollector.h"
#include "service/executor/iexecutiontask.h"

#include <deque>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <random>


class WorkStealingExecutor : public IExecutor {
    public:
        WorkStealingExecutor(int numThreads = 4);
        ~WorkStealingExecutor();
        void add(const std::shared_ptr<IAlgorithm>& algo,
                 const std::shared_ptr<IProblem>& problem,const std::shared_ptr<IInstanceSetting>& setting) override;
        void run() override;
        void clear() override;
        const std::shared_ptr<ISolutionCollector>& getSolutionCollector() const override;
        std::vector<size_t> getQueueSizes() const;
    
    private:
    
        void worker(int id);
        bool tryStealTask(int workerId, std::unique_ptr<IExecutionTask>& task);
        
        int m_numThreads;
        std::vector<std::thread> m_workers;
        std::vector<std::deque<std::unique_ptr<IExecutionTask>>> m_queues;
        std::vector<std::mutex> m_mutexes;  // Changed from unique_ptr to direct objects
        
        std::atomic<bool> m_stop{false};
        std::atomic<bool> m_running{false};
        std::condition_variable m_cv;
        std::mutex m_cvMutex;
        
        std::shared_ptr<ISolutionCollector> m_solutionCollector;
        std::atomic<int> m_nextQueue{0};
        
        // Additional synchronization for safer shutdown
        std::atomic<int> m_activeWorkers{0};
        std::mutex m_solutionMutex;  // Protect solution collector access
};