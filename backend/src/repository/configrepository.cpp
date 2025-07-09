#include "repository/configrepository.h"

#include "repository/configuration/configurationprovider.h"

ConfigRepository::ConfigRepository(){
    configProvider = std::make_shared<ConfigurationProvider>();
}


void ConfigRepository::readConfiguration(const std::string& path){
    configProvider->readConfiguration(path);
}

const LKH3Config& ConfigRepository::getLKH3Config() const {
    return configProvider->getLKH3Config();
}

const ConcordeConfig& ConfigRepository::getConcordeConfig() const {
    return configProvider->getConcordeConfig();
}

const GeneralConfig& ConfigRepository::getGeneralConfig() const {
    return configProvider->getGeneralConfig();
}