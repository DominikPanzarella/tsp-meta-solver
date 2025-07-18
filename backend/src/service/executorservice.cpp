#include "service/executorservice.h"
#include "service/executor/singlequeueexecutor.h"

// ----- Implementation

ExecutorService::ExecutorService() : executor(std::make_unique<SingleQueueExecutor>())
{
}

const std::shared_ptr<ExecutorService>& ExecutorService::getInstance()
{
    static std::shared_ptr<ExecutorService> mySelf(new ExecutorService());
    return mySelf;
}

 void ExecutorService::add(const std::shared_ptr<IAlgorithm>& algo, const std::shared_ptr<IProblem>& problem,const std::shared_ptr<IInstanceSetting>& setting) 
{
    executor->add(algo,problem, setting);
}

void ExecutorService::run(){
    executor->run();
}

void ExecutorService::clear() {
    executor->clear();
}

const std::shared_ptr<ISolutionCollector>& ExecutorService::getSolutionCollector() const{
    return executor->getSolutionCollector();
}
