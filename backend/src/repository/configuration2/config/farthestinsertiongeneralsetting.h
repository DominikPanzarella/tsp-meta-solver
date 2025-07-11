#pragma once

#include "repository/configuration2/config/igeneralsetting.h"

class FarthestInsertionGeneralSetting : public IGeneralSetting {
public:

    FarthestInsertionGeneralSetting() =default;

    int getHardInstancesNumberOfNodes();

    void setHardInstancesNumberOfNodes(int nodes);

private:
    
    // HARD INSTANCES SETTINGS
    int numberOfNodes;
    
};