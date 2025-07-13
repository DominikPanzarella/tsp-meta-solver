#include "repository/configuration2/config/nearestneighbourgeneralsetting.h"

int NearestNeighbourGeneralSetting::getHardInstancesNumberOfNodes(){
    return numberOfNodes;
}

void NearestNeighbourGeneralSetting::setHardInstancesNumberOfNodes(int nodes){
    numberOfNodes = nodes;
}

bool NearestNeighbourGeneralSetting::getRandomStartingNode(){
    return randomStartingNode;
}

void NearestNeighbourGeneralSetting::setRandomStartingNode(bool value){
    randomStartingNode = value;
}