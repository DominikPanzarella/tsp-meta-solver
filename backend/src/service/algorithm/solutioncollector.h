#pragma once

#include "isolutioncollector.h"

class SolutionCollector : public ISolutionCollector{
public:

    SolutionCollector() =default;

    virtual ~SolutionCollector() =default;

    virtual void addSolution(std::shared_ptr<ISolution> solution) override;

    virtual const std::vector<std::shared_ptr<ISolution>>& getSolutions() const override;

    virtual void reset() override;

    virtual int size() const override;
    
private:
    std::vector<std::shared_ptr<ISolution>> m_solutions;
    
};