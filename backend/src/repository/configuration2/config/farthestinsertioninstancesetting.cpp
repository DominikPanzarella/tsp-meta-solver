#include "repository/configuration2/config/farthestinsertioninstancesetting.h"


FarthestInsertionInstanceSetting::FarthestInsertionInstanceSetting(int m_startingNode) : m_startingNode{m_startingNode}
{
}

int FarthestInsertionInstanceSetting::getStartingNode(){
    return m_startingNode;
}