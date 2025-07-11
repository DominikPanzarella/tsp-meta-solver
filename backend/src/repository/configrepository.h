#pragma once

#include "service/iconfigrepository.h"
#include "repository/configuration2/iconfigprovider.h"

class ConfigRepository : public IConfigRepository{
public:

    ConfigRepository();

    virtual ~ConfigRepository() = default;

    virtual void read(const std::string& file_path) override ;

    virtual void configure(std::vector<std::shared_ptr<IProblem>> problems) override;

    virtual std::vector<std::string> getEnabledAlgorithms() override;

    virtual std::shared_ptr<NearestInsertionGeneralSetting> getNearestInsertionSettings() override;

    virtual std::shared_ptr<NearestNeighbourGeneralSetting> getNearestNeighbourSettings() override;

    virtual std::shared_ptr<FarthestInsertionGeneralSetting> getFarthestInsertionSettings() override;

    virtual std::shared_ptr<ConcordeGeneralSetting> getConcordeSettings() override;

    virtual std::shared_ptr<LKH3GeneralSetting> getLKH3Settings() override;

private:

    std::shared_ptr<IConfigProvider> configProvider;
};