#include "service/tspservice.h"
#include "repository/tsprepository.h"

// ----- Implementation

TspService::TspService() {
    repositoryLayer = std::make_unique<TspRepository>();
}

const std::shared_ptr<TspService>& TspService::getInstance(){
    static std::shared_ptr<TspService> mySelf(new TspService());
    return mySelf;
}


std::shared_ptr<IProblem> TspService::read(const std::string& file_path) {
    return repositoryLayer->read(file_path);
}

bool TspService::write(std::string file_path, std::string extension, const std::shared_ptr<ISolutionCollector>& solutionCollector){
    return repositoryLayer->write(file_path, extension, solutionCollector);
}
