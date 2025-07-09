#pragma once

#include "controller/iconfigservice.h"

class ConfigController {
public:

    ~ConfigController() = default;

    static const std::shared_ptr<ConfigController>& getInstance();

    void readConfiguration(const std::string& path); 
    
    const LKH3Config& getLKH3Config() const;

    const ConcordeConfig& getConcordeConfig() const;

    const GeneralConfig& getGeneralConfig() const;


private:
    std::shared_ptr<IConfigService> serviceLayer;

    ConfigController();

};