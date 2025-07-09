#pragma once

#include "service/algorithm/ialgorithm.h"

class NearestNeighbour : public IAlgorithm {
public:

    virtual std::shared_ptr<ISolution> execute(std::shared_ptr<IProblem> problem) override;

    virtual std::string name() const override;

    NearestNeighbour(int startingNode = 0);

    int getStartingNode() const;

    void setStartingNode(int startingNode);

private:
int m_startingNode;

};