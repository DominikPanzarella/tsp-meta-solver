#pragma once

#include "controller/iconfigservice.h"

class ConfigController
{
public:
    ~ConfigController() = default;

    static const std::shared_ptr<ConfigController> &getInstance();

    void read(const std::string &file_path);

    void configure(std::vector<std::shared_ptr<IProblem>> problems);

    std::vector<std::string> getEnabledAlgorithms();

    std::shared_ptr<NearestInsertionGeneralSetting> getNearestInsertionSettings();

    std::shared_ptr<NearestNeighbourGeneralSetting> getNearestNeighbourSettings();

    std::shared_ptr<FarthestInsertionGeneralSetting> getFarthestInsertionSettings();

    std::shared_ptr<ConcordeGeneralSetting> getConcordeSettings();

    std::shared_ptr<LKH3GeneralSetting> getLKH3Settings();

private:
    std::shared_ptr<IConfigService> serviceLayer;

    ConfigController();
};