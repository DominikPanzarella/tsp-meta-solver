#include "controller/executorcontroller.h"
#include "service/executorservice.h"

ExecutorController::ExecutorController() {
    serviceLayer = ExecutorService::getInstance();
}

const std::shared_ptr<ExecutorController>& ExecutorController::getInstance(){
    static std::shared_ptr<ExecutorController> mySelf(new ExecutorController());
    return mySelf;
}

void ExecutorController::add(const std::shared_ptr<IAlgorithm>& algo, const std::shared_ptr<IProblem>& problem)
{
    serviceLayer->add(algo, problem);
}

void ExecutorController::run() const {
    serviceLayer->run();
}

void ExecutorController::clear(){
    serviceLayer->clear();
}

const std::shared_ptr<ISolutionCollector>& ExecutorController::getSolutionCollector() const{
    return serviceLayer->getSolutionCollector();
}

