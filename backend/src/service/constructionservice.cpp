#include "service/constructionservice.h"
#include "repository/constructionrepository.h"

ConstructionService::ConstructionService() : repositoryLayer(std::make_unique<ConstructionRepository>()){
}


const std::shared_ptr<ConstructionService>& ConstructionService::getInstance(){
    static std::shared_ptr<ConstructionService> mySelf(new ConstructionService());
    return mySelf;
}


void ConstructionService::construct(std::string path, const std::string& filename, const std::vector<std::vector<int>>& adjMatrix) const {
    repositoryLayer->construct(path, filename, adjMatrix);
}
