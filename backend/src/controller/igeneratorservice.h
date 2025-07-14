#pragma once
#include <vector>


#include "service/generator/shortestPath/ishortestpath.h"
class IGeneratorService {
public:

    virtual ~IGeneratorService() =default;

    virtual std::vector<std::vector<int>> generate(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const =0;

private:

};