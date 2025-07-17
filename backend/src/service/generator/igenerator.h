#pragma once

#include "service/generator/shortestPath/ishortestpath.h"
#include <vector>

class IGenerator {
public:
    virtual ~IGenerator() =default;
    
    virtual std::vector<std::vector<int>> generate(int n, const std::shared_ptr<IShortestPath>& shortestPathSolver) const = 0;

    virtual std::vector<std::vector<int>> generate(int a, int b, int c,const std::shared_ptr<IShortestPath> &shortestPathSolver) const = 0;
};