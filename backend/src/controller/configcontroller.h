#pragma once

#include "controller/iconfigservice.h"
#include <memory>
#include <vector>
#include <string>
#include "service/problem/iproblem.h"
#include "repository/configuration2/config/nearestinsertiongeneralsetting.h"
#include "repository/configuration2/config/nearestneighbourgeneralsetting.h"
#include "repository/configuration2/config/farthestinsertiongeneralsetting.h"
#include "repository/configuration2/config/concordegeneralsetting.h"
#include "repository/configuration2/config/lkh3generalsetting.h"


class ConfigController
{
public:
    ~ConfigController() = default;

    static const std::shared_ptr<ConfigController> &getInstance();

    void read(const std::string &file_path);

    virtual void configureProblems(std::vector<std::shared_ptr<IProblem>> problems);

    virtual void configureAlgorithms();

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