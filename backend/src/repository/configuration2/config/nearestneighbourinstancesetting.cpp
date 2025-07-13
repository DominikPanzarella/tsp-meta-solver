#include "repository/configuration2/config/nearestneighbourinstancesetting.h"


NearestNeighbourInstanceSetting::NearestNeighbourInstanceSetting(int m_startingNode) : m_startingNode{m_startingNode}
{
}

int NearestNeighbourInstanceSetting::getStartingNode(){
    return m_startingNode;
}

