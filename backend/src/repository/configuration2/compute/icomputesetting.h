#pragma once

#include "service/problem/iproblem.h"
#include <vector>

class IComputeSetting{
public:
    virtual ~IComputeSetting() = default;

    virtual std::pair<int, int> computeShortestEdge(std::shared_ptr<IProblem> problem) const = 0;

    virtual std::vector<std::pair<int, int>> computeShortestEdges(std::shared_ptr<IProblem> problem) const = 0;

    virtual std::pair<int, int> computeLongestEdge(std::shared_ptr<IProblem> problem) const = 0;

    virtual std::vector<std::pair<int, int>> computeLongestEdges(std::shared_ptr<IProblem> problem) const = 0;
    
};