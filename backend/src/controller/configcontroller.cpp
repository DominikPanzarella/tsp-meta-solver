#include "controller/configcontroller.h"
#include "service/configservice.h"


ConfigController::ConfigController() {
    serviceLayer = ConfigService::getInstance();
}

const std::shared_ptr<ConfigController>& ConfigController::getInstance(){
    static std::shared_ptr<ConfigController> mySelf(new ConfigController());
    return mySelf;
}

void ConfigController::readConfiguration(const std::string& path){
    serviceLayer->readConfiguration(path);
}
    
const LKH3Config& ConfigController::getLKH3Config() const{
    return serviceLayer->getLKH3Config();
}

const ConcordeConfig& ConfigController::getConcordeConfig() const{
    return serviceLayer->getConcordeConfig();
}

const GeneralConfig& ConfigController::getGeneralConfig() const{
    return serviceLayer->getGeneralConfig();
}