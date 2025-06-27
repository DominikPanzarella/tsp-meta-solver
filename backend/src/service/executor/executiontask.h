#pragma once


#include <iostream>

#include "service/executor/iexecutiontask.h"

class ExecutionTask : public IExecutionTask{
public:

    ExecutionTask(std::shared_ptr<IAlgorithm> algo,
                    std::shared_ptr<IProblem> problem);

    virtual std::shared_ptr<ISolution> execute() override;
    
    virtual std::shared_ptr<IAlgorithm> getAlgorithm() const override;
    
    virtual std::shared_ptr<IProblem> getProblem() const override;

private:
    std::shared_ptr<IProblem> m_problem;
    
    std::shared_ptr<IAlgorithm> m_algo;

};