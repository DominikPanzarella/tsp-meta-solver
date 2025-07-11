#pragma once

#include "controller/iexecutorservice.h"
#include "service/executor/iexecutor.h"

class ExecutorService : public IExecutorService {
public:
    ~ExecutorService() = default;

    static const std::shared_ptr<ExecutorService>& getInstance();

    virtual void add(const std::shared_ptr<IAlgorithm>& algo,
        const std::shared_ptr<IProblem>& problem, const std::shared_ptr<IInstanceSetting>& setting) override;

    virtual void run() override;

    virtual void clear() override;

    virtual const std::shared_ptr<ISolutionCollector>& getSolutionCollector() const override;

private:
    std::unique_ptr<IExecutor> executor;

    ExecutorService();

};