#pragma once

#include "repository/configuration2/iconfigprovider.h"

class ConfigProvider : public IConfigProvider{
public:

    ConfigProvider() =default;

    ~ConfigProvider() =default;

    virtual JSON read(const std::string& file_path) override ;

    virtual void configure(std::vector<std::shared_ptr<IProblem>> problems) override;

    virtual std::vector<std::string> getEnabledAlgorithms() override;

    virtual std::shared_ptr<NearestInsertionGeneralSetting> getNearestInsertionSettings() override;

    virtual std::shared_ptr<NearestNeighbourGeneralSetting> getNearestNeighbourSettings() override;

    virtual std::shared_ptr<FarthestInsertionGeneralSetting> getFarthestInsertionSettings() override;

    virtual std::shared_ptr<ConcordeGeneralSetting> getConcordeSettings() override;

    virtual std::shared_ptr<LKH3GeneralSetting> getLKH3Settings() override;

private:
    JSON m_json;

    std::shared_ptr<NearestInsertionGeneralSetting> m_ni;

    std::shared_ptr<NearestNeighbourGeneralSetting> m_nn;

    std::shared_ptr<FarthestInsertionGeneralSetting> m_fi;

    std::shared_ptr<ConcordeGeneralSetting> m_cc;

    std::shared_ptr<LKH3GeneralSetting> m_lkh3;

    void configureNI();

    void configureNN();

    void configureFI();
    
    void configureCC();

    void configureLKH3();

};