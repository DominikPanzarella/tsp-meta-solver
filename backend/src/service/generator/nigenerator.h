#pragma once

#include "service/generator/igenerator.h"

class NIGenerator : public IGenerator{
public:

    ~NIGenerator() =default;

    static const std::shared_ptr<NIGenerator>& getInstance();

    virtual std::vector<std::vector<int>> generate(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const override;

    virtual std::vector<std::vector<int>> generate(int a, int b, int c,const std::shared_ptr<IShortestPath> &shortestPathSolver) const override;


private:
    NIGenerator() =default;
};