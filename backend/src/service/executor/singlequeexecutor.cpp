#include "service/executor/singlequeexecutor.h"


void SingleQueueExecutor::add(const std::shared_ptr<IAlgorithm>& algo,
    const std::shared_ptr<IProblem>& problem){
        m_tasks.emplace_back(std::make_unique<ExecutionTask>(algo, problem));
    }

void SingleQueueExecutor::run(){
    for(auto& task : m_tasks){
        auto result = task->execute();
    }
}

void SingleQueueExecutor::clear(){
    m_tasks.clear();
}