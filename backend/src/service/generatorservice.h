#pragma once

#include "controller/igeneratorservice.h"
#include "service/generator/igenerator.h"

class GeneratorService : public IGeneratorService {
public:

    GeneratorService(std::shared_ptr<IGenerator> generator);

    ~GeneratorService() =default;

    virtual std::vector<std::vector<int>> generate(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const override;

    virtual std::vector<std::vector<int>> generate(int a, int b, int c,const std::shared_ptr<IShortestPath>& shortestPathSolver) const override;

private:

    std::shared_ptr<IGenerator> m_generator;

};