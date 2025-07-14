#pragma once

#include <vector>
#include "repository/configuration2/config/nearestneighbourgeneralsetting.h"
#include "repository/configuration2/config/nearestinsertiongeneralsetting.h"
#include "repository/configuration2/config/concordegeneralsetting.h"
#include "repository/configuration2/config/lkh3generalsetting.h"
#include "repository/configuration2/config/farthestinsertiongeneralsetting.h"
#include "service/problem/iproblem.h"


class IConfigService{
public: 
    virtual ~IConfigService() = default;

    virtual void read(const std::string& file_path) =0 ;

    virtual void configureProblems(std::vector<std::shared_ptr<IProblem>> problems) =0;

    virtual void configureAlgorithms() =0;

    virtual std::vector<std::string> getEnabledAlgorithms() =0;

    virtual std::shared_ptr<NearestInsertionGeneralSetting> getNearestInsertionSettings() =0;

    virtual std::shared_ptr<NearestNeighbourGeneralSetting> getNearestNeighbourSettings() =0;

    virtual std::shared_ptr<FarthestInsertionGeneralSetting> getFarthestInsertionSettings() =0;

    virtual std::shared_ptr<ConcordeGeneralSetting> getConcordeSettings() =0;

    virtual std::shared_ptr<LKH3GeneralSetting> getLKH3Settings() =0;

};