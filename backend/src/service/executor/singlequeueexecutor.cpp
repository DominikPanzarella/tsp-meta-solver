#include "service/executor/singlequeueexecutor.h"

#include "service/algorithm/solutioncollector.h"

SingleQueueExecutor::SingleQueueExecutor()
    : m_solutionCollector(std::make_shared<SolutionCollector>()) {}


void SingleQueueExecutor::add(const std::shared_ptr<IAlgorithm>& algo,
    const std::shared_ptr<IProblem>& problem){
        m_tasks.emplace_back(std::make_unique<ExecutionTask>(algo, problem));
    }

void SingleQueueExecutor::run(){
    for(auto& task : m_tasks){
        std::shared_ptr<ISolution> result = task->execute();
        m_solutionCollector->addSolution(result);
    }
}

void SingleQueueExecutor::clear(){
    m_tasks.clear();
}

const std::shared_ptr<ISolutionCollector>& SingleQueueExecutor::getSolutionCollector() const {
    return m_solutionCollector;
}