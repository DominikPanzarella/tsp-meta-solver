#pragma once

#include "repository/configuration2/iconfigprovider.h"
#include "repository/configuration2/compute/icomputesetting.h"

class ConfigProvider : public IConfigProvider{
public:

    static const std::shared_ptr<ConfigProvider>& getInstance();

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

    std::unique_ptr<IComputeSetting> m_cs;

    std::shared_ptr<NearestInsertionGeneralSetting> m_ni;

    std::shared_ptr<NearestNeighbourGeneralSetting> m_nn;

    std::shared_ptr<FarthestInsertionGeneralSetting> m_fi;

    std::shared_ptr<ConcordeGeneralSetting> m_cc;

    std::shared_ptr<LKH3GeneralSetting> m_lkh3;

    void configureNI(std::vector<std::shared_ptr<IProblem>> problems);

    void configureNN(std::vector<std::shared_ptr<IProblem>> problems);

    void configureFI(std::vector<std::shared_ptr<IProblem>> problems);
    
    void configureCC(std::vector<std::shared_ptr<IProblem>> problems);

    void configureLKH3(std::vector<std::shared_ptr<IProblem>> problems);

    ConfigProvider();

};