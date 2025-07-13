#pragma once

#include "repository/configuration2/config/igeneralsetting.h"

class NearestNeighbourGeneralSetting : public IGeneralSetting {
public:
    
    NearestNeighbourGeneralSetting() =default;
    
    int getHardInstancesNumberOfNodes();
    
    void setHardInstancesNumberOfNodes(int nodes);

    bool getRandomStartingNode();

    void setRandomStartingNode(bool value);
    
private:
        
    // HARD INSTANCES SETTINGS
    int numberOfNodes;

    bool randomStartingNode;
        
};