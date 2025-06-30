#pragma once

#include "service/executor/iexecutor.h"
#include "service/algorithm/isolutioncollector.h"

class SingleQueueExecutor : public IExecutor {
public:

    SingleQueueExecutor() = default;

    virtual ~SingleQueueExecutor() =default;

    virtual void add(const std::shared_ptr<IAlgorithm>& algo,
        const std::shared_ptr<IProblem>& problem) override;

    virtual void run() override;

    virtual void clear() override;

    virtual const std::shared_ptr<ISolutionCollector>& getSolutionCollector() const override;

private:
    std::vector<std::unique_ptr<IExecutionTask>> m_tasks;

    std::shared_ptr<ISolutionCollector> m_solutionCollector;
    
};