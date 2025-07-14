#include "repository/configuration2/config/nearestneighbourgeneralsetting.h"

std::vector<int> NearestNeighbourGeneralSetting::getHardInstancesNumberOfNodes(){
    return m_nodes;
}
    
void NearestNeighbourGeneralSetting::setHardInstancesNumberOfNodes(std::vector<int> nodes){
    m_nodes = nodes;
}

bool NearestNeighbourGeneralSetting::getRandomStartingNode(){
    return randomStartingNode;
}

void NearestNeighbourGeneralSetting::setRandomStartingNode(bool value){
    randomStartingNode = value;
}

void NearestNeighbourGeneralSetting::setSeed(int seed){
    m_seed = seed;
}

int NearestNeighbourGeneralSetting::getSeed(){
    return m_seed;
}