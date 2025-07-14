#include "service/generatorservice.h"

GeneratorService::GeneratorService(std::shared_ptr<IGenerator> generator){
    m_generator = generator;
}

const std::shared_ptr<GeneratorService>& GeneratorService::getInstance(std::shared_ptr<IGenerator> generator){
    static std::shared_ptr<GeneratorService> mySelf(new GeneratorService(generator));
    return mySelf;
}

std::vector<std::vector<int>> GeneratorService::generate(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const {
    return m_generator->generate(n, shortestPathSolver);
}
