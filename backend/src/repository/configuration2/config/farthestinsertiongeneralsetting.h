#pragma once

#include "repository/configuration2/config/igeneralsetting.h"
#include <vector>

class FarthestInsertionGeneralSetting : public IGeneralSetting {
public:

    FarthestInsertionGeneralSetting() =default;

    std::vector<int> getHardInstancesNumberOfNodes();

    void setHardInstancesNumberOfNodes(std::vector<int> nodes);

    void setSeed(int seed);

    int getSeed();

private:
    
    // HARD INSTANCES SETTINGS
    std::vector<int> m_nodes;

    int m_seed;
    
};