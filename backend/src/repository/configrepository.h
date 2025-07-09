#pragma once

#include "repository/configuration/iconfigurationprovider.h"
#include "service/iconfigrepository.h"

class ConfigRepository : public IConfigRepository{
public:

    ConfigRepository();
    

    virtual void readConfiguration(const std::string& path) override; 

    virtual const LKH3Config& getLKH3Config() const override;

    virtual const ConcordeConfig& getConcordeConfig() const override;

    virtual const GeneralConfig& getGeneralConfig() const override;
protected:
    
private:
    std::shared_ptr<IConfigurationProvider>  configProvider;
    
};