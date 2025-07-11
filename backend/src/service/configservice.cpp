#include "service/configservice.h"
#include "repository/configrepository.h"

ConfigService::ConfigService() : repositoryLayer(std::make_unique<ConfigRepository>())
{
}

const std::shared_ptr<IConfigService> &ConfigService::getInstance()
{
    static std::shared_ptr<IConfigService> mySelf(new ConfigService());
    return mySelf;
}

void ConfigService::read(const std::string &file_path)
{
    repositoryLayer->read(file_path);
}

void ConfigService::configure(std::vector<std::shared_ptr<IProblem>> problems)
{
    repositoryLayer->configure(problems);
}

std::vector<std::string> ConfigService::getEnabledAlgorithms()
{
    return repositoryLayer->getEnabledAlgorithms();
}

std::shared_ptr<NearestInsertionGeneralSetting> ConfigService::getNearestInsertionSettings()
{
    return repositoryLayer->getNearestInsertionSettings();
}

std::shared_ptr<NearestNeighbourGeneralSetting> ConfigService::getNearestNeighbourSettings()
{
    return repositoryLayer->getNearestNeighbourSettings();
}

std::shared_ptr<FarthestInsertionGeneralSetting> ConfigService::getFarthestInsertionSettings()
{
    return repositoryLayer->getFarthestInsertionSettings();
}

std::shared_ptr<ConcordeGeneralSetting> ConfigService::getConcordeSettings()
{
    return repositoryLayer->getConcordeSettings();
}

std::shared_ptr<LKH3GeneralSetting> ConfigService::getLKH3Settings()
{
    return repositoryLayer->getLKH3Settings();
}
