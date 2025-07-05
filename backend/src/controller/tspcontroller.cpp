#include "controller/tspcontroller.h"
#include "service/tspservice.h"


TspController::TspController() {
    serviceLayer = TspService::getInstance();
}

const std::shared_ptr<TspController>& TspController::getInstance(){
    static std::shared_ptr<TspController> mySelf(new TspController());
    return mySelf;
}

std::shared_ptr<IProblem> TspController::read(const std::string& file_path) {
    return serviceLayer->read(file_path);
}

bool TspController::write(std::string file_path, std::string extension, const std::shared_ptr<ISolutionCollector>& solutionCollector){
    return serviceLayer->write(file_path, extension, solutionCollector);
}
