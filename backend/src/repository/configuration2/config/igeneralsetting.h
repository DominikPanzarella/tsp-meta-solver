#pragma once

#include "repository/configuration2/config/isetting.h"
#include "repository/configuration2/config/iinstancesetting.h"


class IGeneralSetting : public ISetting{
public:

    void addInstance(const std::string& name, std::shared_ptr<IInstanceSetting> setting){
        instances[name] = std::move(setting);
    }

    std::shared_ptr<IInstanceSetting> getInstance(const std::string& name){
        if(instances.contains(name))
            return instances[name];
        else
            return nullptr;
    }

    bool hasInstance(const std::string& name) const {
        return instances.contains(name);
    }

    const std::unordered_map<std::string, std::shared_ptr<IInstanceSetting>>& getInstances(){
        return instances;
    }

protected:
    std::unordered_map<std::string, std::shared_ptr<IInstanceSetting>> instances;
};