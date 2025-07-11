#pragma once

#include "repository/configuration2/config/igeneralsetting.h"

class NearestInsertionGeneralSetting : public IGeneralSetting {
public:

    NearestInsertionGeneralSetting() =default;

    int getHardInstancesNumberOfNodes();

    void setHardInstancesNumberOfNodes(int nodes);

private:
    
    // HARD INSTANCES SETTINGS
    int numberOfNodes;
    
};