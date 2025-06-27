#pragma once

#include "service/executor/iexecutor.h"

class SingleQueueExecutor : public IExecutor {
public:

    virtual void add(const std::shared_ptr<IAlgorithm>& algo,
        const std::shared_ptr<IProblem>& problem) override;

    virtual void run() override;

    virtual void clear() override;

private:
    std::vector<std::unique_ptr<IExecutionTask>> m_tasks;
    
    //TODO: how to collect results ?????
};