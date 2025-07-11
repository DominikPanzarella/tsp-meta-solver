#include "repository/configuration2/config/nearestinsertiongeneralsetting.h"


int NearestInsertionGeneralSetting::getHardInstancesNumberOfNodes(){
    return numberOfNodes;
}

void NearestInsertionGeneralSetting::setHardInstancesNumberOfNodes(int nodes){
    numberOfNodes = nodes;
}