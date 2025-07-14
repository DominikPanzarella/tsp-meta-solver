#pragma once

#include <vector>
#include "service/problem/iproblem.h"

class IShortestPath{
public:

    ~IShortestPath() = default;

    // Returns shortest distances from src to all other vertices
    virtual std::vector<std::vector<int>> shortestPath(std::vector<std::vector<int>> adj) const = 0;
};