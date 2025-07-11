#include "controller/configcontroller.h"
#include "service/configservice.h"


ConfigController::ConfigController() {
    serviceLayer = ConfigService::getInstance();
}

const std::shared_ptr<ConfigController>& ConfigController::getInstance(){
    static std::shared_ptr<ConfigController> mySelf(new ConfigController());
    return mySelf;
}

void ConfigController::read(const std::string &file_path){
    serviceLayer->read(file_path);
}

void ConfigController::configure(std::vector<std::shared_ptr<IProblem>> problems){ 
    serviceLayer->configure(problems);
}

std::vector<std::string> ConfigController::getEnabledAlgorithms(){
    return serviceLayer->getEnabledAlgorithms();
 }

std::shared_ptr<NearestInsertionGeneralSetting> ConfigController::getNearestInsertionSettings(){
    return serviceLayer->getNearestInsertionSettings();
 }

std::shared_ptr<NearestNeighbourGeneralSetting> ConfigController::getNearestNeighbourSettings(){
    return serviceLayer->getNearestNeighbourSettings();
 }

std::shared_ptr<FarthestInsertionGeneralSetting> ConfigController::getFarthestInsertionSettings(){
    return serviceLayer->getFarthestInsertionSettings();
 }

std::shared_ptr<ConcordeGeneralSetting> ConfigController::getConcordeSettings(){
    return serviceLayer->getConcordeSettings();
 }

std::shared_ptr<LKH3GeneralSetting> ConfigController::getLKH3Settings(){
    return serviceLayer->getLKH3Settings();
 }