#pragma once

#include "repository/configuration/iconfigurationprovider.h"
#include <unordered_map>

class ConfigurationProvider : public IConfigurationProvider{
public:
    ConfigurationProvider() =default;
    
    virtual void readConfiguration(const std::string& path) override;

    virtual const LKH3Config& getLKH3Config() const override;

    virtual const ConcordeConfig& getConcordeConfig() const override;

    virtual const GeneralConfig& getGeneralConfig() const override;
    
private:
    LKH3Config m_lkh3Config;

    ConcordeConfig m_concordeConfig; 

    GeneralConfig m_generalConfig;


    void constructLKH3Config(std::unordered_map<std::string, std::string> map);

    void constructConcordeConfig(std::unordered_map<std::string, std::string> map);

    void constructGeneralConfig(std::unordered_map<std::string, std::string> map);
};
    