#pragma once


#include "service/algorithm/lkh3config.h"
#include "service/algorithm/concordeconfig.h"
#include "service/algorithm/generalconfig.h"

class IConfigRepository{
public:

    virtual ~IConfigRepository() = default;

    virtual void readConfiguration(const std::string& path) = 0; 
    
    virtual const LKH3Config& getLKH3Config() const =0;

    virtual const ConcordeConfig& getConcordeConfig() const = 0;

    virtual const GeneralConfig& getGeneralConfig() const = 0;
};