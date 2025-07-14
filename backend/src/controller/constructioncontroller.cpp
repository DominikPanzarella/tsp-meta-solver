#include "controller/constructioncontroller.h"
#include "service/constructionservice.h"
#include "service/generatorservice.h"
#include "service/generator/nigenerator.h"

ConstructionController::ConstructionController(){
    serviceLayer = ConstructionService::getInstance();
    ni_service = GeneratorService::getInstance(NIGenerator::getInstance());
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
