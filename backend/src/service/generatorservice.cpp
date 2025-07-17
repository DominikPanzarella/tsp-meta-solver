#include "service/generatorservice.h"
#include <iostream>

GeneratorService::GeneratorService(std::shared_ptr<IGenerator> generator){
    m_generator = generator;
}

std::vector<std::vector<int>> GeneratorService::generate(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const {
    return m_generator->generate(n, shortestPathSolver);
}


std::vector<std::vector<int>> GeneratorService::generate(int a, int b, int c,const std::shared_ptr<IShortestPath>& shortestPathSolver) const {
    return m_generator->generate(a,b,c,shortestPathSolver);
}
