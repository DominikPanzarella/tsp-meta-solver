#include "service/executor/executiontask.h"

ExecutionTask::ExecutionTask(std::shared_ptr<IAlgorithm> algo,
    std::shared_ptr<IProblem> problem)
    : m_problem{std::move(problem)},
    m_algo{std::move(algo)}           //Init list
    {
    //Empty constructor
    }

std::shared_ptr<ISolution> ExecutionTask::execute() {
    //Start measuring exec time
    auto start = std::chrono::high_resolution_clock::now(); 

    //Execution
    const auto& solution =  m_algo->execute(m_problem);

    //Stop measuring execution time
    auto end = std::chrono::high_resolution_clock::now();
    int execTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    //Set execution time
    solution->setExecutionTime(execTimeUs);

    return solution;
}


std::shared_ptr<IAlgorithm> ExecutionTask::getAlgorithm() const{
    return m_algo;
}

std::shared_ptr<IProblem> ExecutionTask::getProblem() const{
    return m_problem;
}
