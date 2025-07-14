#include "repository/configuration2/config/farthestinsertiongeneralsetting.h"


std::vector<int> FarthestInsertionGeneralSetting::getHardInstancesNumberOfNodes(){
    return m_nodes;
}

void FarthestInsertionGeneralSetting::setHardInstancesNumberOfNodes(    std::vector<int> nodes){
    m_nodes = nodes;
}

void FarthestInsertionGeneralSetting::setSeed(int seed){
    m_seed = seed;
}

int FarthestInsertionGeneralSetting::getSeed(){
    return m_seed;
}