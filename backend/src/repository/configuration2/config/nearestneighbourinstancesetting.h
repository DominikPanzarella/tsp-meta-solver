#pragma once

#include "repository/configuration2/config/iinstancesetting.h"

class NearestNeighbourInstanceSetting : public IInstanceSetting {
public:

    NearestNeighbourInstanceSetting(int m_startingNode = 0);

    int getStartingNode();

private:
    int m_startingNode;
};