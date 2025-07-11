#pragma once

#include "controller/iconfigservice.h"
#include "service/iconfigrepository.h"


class ConfigService : public IConfigService{
public:
    ~ConfigService() = default;

    static const std::shared_ptr<IConfigService>& getInstance();

    virtual void read(const std::string& file_path) override ;

    virtual void configure(std::vector<std::shared_ptr<IProblem>> problems) override;

    virtual std::vector<std::string> getEnabledAlgorithms() override;

    virtual std::shared_ptr<NearestInsertionGeneralSetting> getNearestInsertionSettings() override;

    virtual std::shared_ptr<NearestNeighbourGeneralSetting> getNearestNeighbourSettings() override;

    virtual std::shared_ptr<FarthestInsertionGeneralSetting> getFarthestInsertionSettings() override;

    virtual std::shared_ptr<ConcordeGeneralSetting> getConcordeSettings() override;

    virtual std::shared_ptr<LKH3GeneralSetting> getLKH3Settings() override;

private:

    ConfigService();

    std::unique_ptr<IConfigRepository> repositoryLayer;
};