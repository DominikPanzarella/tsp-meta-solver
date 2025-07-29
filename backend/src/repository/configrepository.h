#pragma once

#include "service/iconfigrepository.h"
#include "repository/configuration2/iconfigprovider.h"
#include <memory>
#include <vector>
#include "repository/configuration2/config/nearestinsertiongeneralsetting.h"
#include "repository/configuration2/config/nearestneighbourgeneralsetting.h"
#include "repository/configuration2/config/farthestinsertiongeneralsetting.h"
#include "repository/configuration2/config/concordegeneralsetting.h"
#include "repository/configuration2/config/lkh3generalsetting.h"
#include <string>

class ConfigRepository : public IConfigRepository{
public:

    ConfigRepository();

    virtual ~ConfigRepository() = default;

    virtual void read(const std::string& file_path) override ;

    virtual void configureProblems(std::vector<std::shared_ptr<IProblem>> problems) override;

    virtual void configureAlgorithms() override;

    virtual std::vector<std::string> getEnabledAlgorithms() override;

    virtual std::shared_ptr<NearestInsertionGeneralSetting> getNearestInsertionSettings() override;

    virtual std::shared_ptr<NearestNeighbourGeneralSetting> getNearestNeighbourSettings() override;

    virtual std::shared_ptr<FarthestInsertionGeneralSetting> getFarthestInsertionSettings() override;

    virtual std::shared_ptr<ConcordeGeneralSetting> getConcordeSettings() override;

    virtual std::shared_ptr<LKH3GeneralSetting> getLKH3Settings() override;

private:

    std::shared_ptr<IConfigProvider> configProvider;
};