#include "service/executor/executiontask.h"

ExecutionTask::ExecutionTask(std::shared_ptr<IAlgorithm> algo,
    std::shared_ptr<IProblem> problem, std::shared_ptr<IInstanceSetting> setting)
    : m_problem{std::move(problem)},
    m_algo{std::move(algo)},           //Init list
    m_instanceSetting{std::move(setting)}
    {
    //Empty constructor
    }

std::shared_ptr<ISolution> ExecutionTask::execute() {
    //Start measuring exec time
    auto start = std::chrono::high_resolution_clock::now(); 

    //Execution
    const auto& solution =  m_algo->execute(m_problem, m_instanceSetting);

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

std::shared_ptr<IInstanceSetting> ExecutionTask::getInstanceSetting() const{
    return m_instanceSetting;
}
