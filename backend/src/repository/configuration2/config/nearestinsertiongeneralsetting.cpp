#include "repository/configuration2/config/nearestinsertiongeneralsetting.h"


std::vector<int> NearestInsertionGeneralSetting::getHardInstancesNumberOfNodes(){
    return m_nodes;
}
    
void NearestInsertionGeneralSetting::setHardInstancesNumberOfNodes(std::vector<int> nodes){
    m_nodes = nodes;
}

void NearestInsertionGeneralSetting::setSeed(int seed){
    m_seed = seed;
}

int NearestInsertionGeneralSetting::getSeed(){
    return m_seed;
}