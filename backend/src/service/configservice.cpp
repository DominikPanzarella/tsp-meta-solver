#include "service/configservice.h"
#include "repository/configrepository.h"

ConfigService::ConfigService() : repositoryLayer(std::make_unique<ConfigRepository>()){
}

const std::shared_ptr<IConfigService>& ConfigService::getInstance(){
    static std::shared_ptr<IConfigService> mySelf(new ConfigService());
    return mySelf;
}

void ConfigService::readConfiguration(const std::string& path) {
    repositoryLayer->readConfiguration(path);
}
    
const LKH3Config& ConfigService::getLKH3Config() const {
    return repositoryLayer->getLKH3Config();
}

const ConcordeConfig& ConfigService::getConcordeConfig() const {
    return repositoryLayer->getConcordeConfig();
}

const GeneralConfig& ConfigService::getGeneralConfig() const {
    return repositoryLayer->getGeneralConfig();
}