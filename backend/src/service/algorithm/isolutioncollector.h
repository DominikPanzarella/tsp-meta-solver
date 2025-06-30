#pragma once

#include "service/algorithm/isolution.h"
#include <vector>

class ISolutionCollector{
public:
    
    virtual ~ISolutionCollector() =default;

    virtual void addSolution(std::shared_ptr<ISolution> solution) =0;

    virtual const std::vector<std::shared_ptr<ISolution>>& getSolutions() const =0;

    virtual void reset() = 0;

    virtual int size() const =0;

};