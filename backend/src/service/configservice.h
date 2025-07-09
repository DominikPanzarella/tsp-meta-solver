#pragma once

#include "controller/iconfigservice.h"
#include "service/iconfigrepository.h"


class ConfigService : public IConfigService{
public:

    ~ConfigService() = default;

    static const std::shared_ptr<IConfigService>& getInstance();

    virtual void readConfiguration(const std::string& path) override; 
    
    virtual const LKH3Config& getLKH3Config() const override;

    virtual const ConcordeConfig& getConcordeConfig() const override;

    virtual const GeneralConfig& getGeneralConfig() const override;


private:

    std::unique_ptr<IConfigRepository> repositoryLayer;

    ConfigService();

};