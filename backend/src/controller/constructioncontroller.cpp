#include "controller/constructioncontroller.h"
#include "service/constructionservice.h"
#include "service/generatorservice.h"
#include "service/generator/nigenerator.h"
#include "service/generator/nngenerator.h"
#include "service/generator/integratilitygapgenerator.h"
#include <iostream>

ConstructionController::ConstructionController(){
    serviceLayer = ConstructionService::getInstance();
    ni_service = std::make_shared<GeneratorService>(NIGenerator::getInstance());
    nn_service = std::make_shared<GeneratorService>(NNGenerator::getInstance());
    cc_service = std::make_shared<GeneratorService>(IntegralityGapGenerator::getInstance());
}


const std::shared_ptr<ConstructionController>& ConstructionController::getInstance(){
    static std::shared_ptr<ConstructionController> myself(new ConstructionController());
    return myself;
}

void ConstructionController::construct(std::string path, const std::string& filename, const std::vector<std::vector<int>>& adjMatrix) const{
    serviceLayer->construct(path, filename, adjMatrix);
}

std::vector<std::vector<int>> ConstructionController::generateNI(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const{
    return ni_service->generate(n, shortestPathSolver);
}

std::vector<std::vector<int>> ConstructionController::generateNN(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const{
    return nn_service->generate(n, shortestPathSolver);
}

std::vector<std::vector<int>> ConstructionController::generateFI(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const{
    return fi_service->generate(n, shortestPathSolver);
}

std::vector<std::vector<int>> ConstructionController::generateIG(int a, int b, int c, const std::shared_ptr<IShortestPath>& shortestPathSolver) const{
    return cc_service->generate(a,b,c,shortestPathSolver);
}
