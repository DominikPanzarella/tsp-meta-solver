#pragma once

#include "service/generator/igenerator.h"

class IntegralityGapGenerator : public IGenerator
{
public:
    ~IntegralityGapGenerator() = default;

    static const std::shared_ptr<IntegralityGapGenerator> &getInstance();

    virtual std::vector<std::vector<int>> generate(int n, const std::shared_ptr<IShortestPath> &shortestPathSolver) const override;

    virtual std::vector<std::vector<int>> generate(int a, int b, int c,const std::shared_ptr<IShortestPath> &shortestPathSolver) const override;

private:
    IntegralityGapGenerator() = default;
};