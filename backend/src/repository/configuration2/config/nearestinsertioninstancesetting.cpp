#include "repository/configuration2/config/nearestinsertioninstancesetting.h"


NearestInsertionInstanceSetting::NearestInsertionInstanceSetting(int m_startingNode) : m_startingNode{m_startingNode}
{
}

int NearestInsertionInstanceSetting::getStartingNode(){
    return m_startingNode;
}
