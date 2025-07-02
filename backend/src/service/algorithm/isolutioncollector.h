#pragma once

#include "service/algorithm/isolution.h"
#include <vector>
#include <unordered_map>

class ISolutionCollector{
public:
    
    virtual ~ISolutionCollector() =default;

    virtual void addSolution(const std::string& algorithm,std::shared_ptr<ISolution> solution) =0;

    virtual const std::unordered_map<std::string, std::vector<std::shared_ptr<ISolution>>>& getSolutions() const =0;

    virtual void reset() = 0;

    virtual int size() const =0;

};