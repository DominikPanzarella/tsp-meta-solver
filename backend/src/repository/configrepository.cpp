#include "repository/configrepository.h"

#include "repository/configuration2/configprovider.h"

ConfigRepository::ConfigRepository() {
    configProvider = ConfigProvider::getInstance();
}


void ConfigRepository::read(const std::string& file_path){
    configProvider->read(file_path);
}

void ConfigRepository::configureProblems(std::vector<std::shared_ptr<IProblem>> problems){
    configProvider->configureProblems(problems);
}

void ConfigRepository::configureAlgorithms(){
    configProvider->configureAlgorithms();
}

std::vector<std::string> ConfigRepository::getEnabledAlgorithms(){
    return configProvider->getEnabledAlgorithms();
}

std::shared_ptr<NearestInsertionGeneralSetting> ConfigRepository::getNearestInsertionSettings(){
    return configProvider->getNearestInsertionSettings();
}

std::shared_ptr<NearestNeighbourGeneralSetting> ConfigRepository::getNearestNeighbourSettings(){
    return configProvider->getNearestNeighbourSettings();
}

std::shared_ptr<FarthestInsertionGeneralSetting> ConfigRepository::getFarthestInsertionSettings(){
    return configProvider->getFarthestInsertionSettings();
}

std::shared_ptr<ConcordeGeneralSetting> ConfigRepository::getConcordeSettings(){
    return configProvider->getConcordeSettings();
}

std::shared_ptr<LKH3GeneralSetting> ConfigRepository::getLKH3Settings(){
    return configProvider->getLKH3Settings();
}
