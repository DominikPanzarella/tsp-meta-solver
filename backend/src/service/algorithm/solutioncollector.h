#pragma once

#include "isolutioncollector.h"
#include <mutex>


class SolutionCollector : public ISolutionCollector{
public:

    SolutionCollector() =default;

    virtual ~SolutionCollector() =default;

    virtual void addSolution(const std::string& algorithm,std::shared_ptr<ISolution> solution) override;

    virtual const std::unordered_map<std::string, std::vector<std::shared_ptr<ISolution>>>& getSolutions() const override;

    virtual void reset() override;

    virtual int size() const override;
    
private:
    mutable std::mutex m_mutex;
    std::unordered_map<std::string, std::vector<std::shared_ptr<ISolution>>> m_solutionsByAlgo;
    
};