#pragma once

#include "service/algorithm/generalconfig.h"
#include "service/algorithm/lkh3config.h"
#include "service/algorithm/concordeconfig.h"

class IConfigService{
public: 
    virtual ~IConfigService() = default;

    virtual void readConfiguration(const std::string& path) = 0; 
    
    virtual const LKH3Config& getLKH3Config() const =0;

    virtual const ConcordeConfig& getConcordeConfig() const = 0;

    virtual const GeneralConfig& getGeneralConfig() const = 0;
};