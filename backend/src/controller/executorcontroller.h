#pragma once

#include "controller/iexecutorservice.h"

class ExecutorController {
public:
    ~ExecutorController() = default;

    static const std::shared_ptr<ExecutorController>& getInstance();


    void add(const std::shared_ptr<IAlgorithm>& algo, const std::shared_ptr<IProblem>& problem);

    void run() const;

    void clear();

    const std::shared_ptr<ISolutionCollector>& getSolutionCollector() const;


private:

    std::shared_ptr<IExecutorService> serviceLayer;

    ExecutorController();

};