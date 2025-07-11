#include "repository/configuration2/config/farthestinsertiongeneralsetting.h"


int FarthestInsertionGeneralSetting::getHardInstancesNumberOfNodes(){
    return numberOfNodes;
}

void FarthestInsertionGeneralSetting::setHardInstancesNumberOfNodes(int nodes){
    numberOfNodes = nodes;
}