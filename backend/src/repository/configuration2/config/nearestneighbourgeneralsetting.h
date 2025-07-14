#pragma once

#include "repository/configuration2/config/igeneralsetting.h"
#include <vector>

class NearestNeighbourGeneralSetting : public IGeneralSetting {
public:
    
    NearestNeighbourGeneralSetting() =default;
    
    std::vector<int> getHardInstancesNumberOfNodes();
    
    void setHardInstancesNumberOfNodes(std::vector<int> nodes);

    bool getRandomStartingNode();

    void setRandomStartingNode(bool value);

    void setSeed(int seed);

    int getSeed();
    
private:
        
    // HARD INSTANCES SETTINGS
    std::vector<int> m_nodes;

    bool randomStartingNode;

    int m_seed;
        
};