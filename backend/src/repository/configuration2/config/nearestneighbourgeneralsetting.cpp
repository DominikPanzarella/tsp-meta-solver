#include "repository/configuration2/config/nearestneighbourgeneralsetting.h"

int NearestNeighbourGeneralSetting::getHardInstancesNumberOfNodes(){
    return numberOfNodes;
}

void NearestNeighbourGeneralSetting::setHardInstancesNumberOfNodes(int nodes){
    numberOfNodes = nodes;
}