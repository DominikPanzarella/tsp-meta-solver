#pragma once

#include "controller/igeneratorservice.h"
#include "service/generator/igenerator.h"

class GeneratorService : public IGeneratorService {
public:

    ~GeneratorService() =default;

    static const std::shared_ptr<GeneratorService>& getInstance(std::shared_ptr<IGenerator> generator);

    virtual std::vector<std::vector<int>> generate(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const override;

private:

    std::shared_ptr<IGenerator> m_generator;

    GeneratorService(std::shared_ptr<IGenerator> generator);

};