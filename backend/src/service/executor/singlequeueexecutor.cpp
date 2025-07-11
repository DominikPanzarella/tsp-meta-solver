#include "service/executor/singlequeueexecutor.h"

#include "service/algorithm/solutioncollector.h"

SingleQueueExecutor::SingleQueueExecutor()
    : m_solutionCollector(std::make_shared<SolutionCollector>()) {}


void SingleQueueExecutor::add(const std::shared_ptr<IAlgorithm>& algo,
    const std::shared_ptr<IProblem>& problem, const std::shared_ptr<IInstanceSetting>& setting){
        m_tasks.emplace_back(std::make_unique<ExecutionTask>(algo, problem, setting));
    }

void SingleQueueExecutor::run(){
    for(auto& task : m_tasks){
        std::shared_ptr<ISolution> result = task->execute();
        m_solutionCollector->addSolution(task->getAlgorithm()->name(),result);          //TODO: need to pass the whole pointer to the algo
    }
}

void SingleQueueExecutor::clear(){
    m_tasks.clear();
}

const std::shared_ptr<ISolutionCollector>& SingleQueueExecutor::getSolutionCollector() const {
    return m_solutionCollector;
}