#include "service/executor/executiontask.h"

ExecutionTask::ExecutionTask(std::shared_ptr<IAlgorithm> algo,
    std::shared_ptr<IProblem> problem)
    : m_problem{std::move(problem)},
    m_algo{std::move(algo)}           //Init list
    {
    //Empty constructor
    }

std::shared_ptr<ISolution> ExecutionTask::execute() {
    return m_algo->execute(m_problem);
}


std::shared_ptr<IAlgorithm> ExecutionTask::getAlgorithm() const{
    return m_algo;
}

std::shared_ptr<IProblem> ExecutionTask::getProblem() const{
    return m_problem;
}
