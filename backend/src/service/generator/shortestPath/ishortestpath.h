#pragma once

#include <vector>
#include "service/problem/iproblem.h"

class IShortestPath{
public:
    // Returns shortest distances from src to all other vertices
    virtual std::vector<std::pair<int,int>> shortestPath(std::shared_ptr<IProblem> problem, int src) const = 0;
};