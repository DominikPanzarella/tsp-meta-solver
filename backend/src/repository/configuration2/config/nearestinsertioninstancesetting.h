#pragma once

#include "repository/configuration2/config/iinstancesetting.h"

class NearestInsertionInstanceSetting : public IInstanceSetting {
public:

    NearestInsertionInstanceSetting(int m_startingNode = 0);

    int getStartingNode();

private:
    int m_startingNode;
};