#pragma once

#include "service/algorithm/ialgorithm.h"
#include "service/algorithm/isolutioncollector.h"

class IExecutorService{
public: 
    virtual ~IExecutorService() = default;

    virtual void add(const std::shared_ptr<IAlgorithm>& algo,
        const std::shared_ptr<IProblem>& problem) = 0;

    virtual void run() = 0;

    virtual void clear() = 0;

    virtual const std::shared_ptr<ISolutionCollector>& getSolutionCollector() const = 0;
};