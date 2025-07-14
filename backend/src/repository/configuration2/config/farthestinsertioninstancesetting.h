#pragma once

#include "repository/configuration2/config/iinstancesetting.h"

class FarthestInsertionInstanceSetting : public IInstanceSetting {
public:

    FarthestInsertionInstanceSetting(int m_startingNode = 0);

    int getStartingNode();
    

private:
    int m_startingNode;
};