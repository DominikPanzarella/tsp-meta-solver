#pragma once

#include "repository/configuration2/compute/icomputesetting.h"

class ComputeStartingNode : public IComputeSetting{

public:

    ComputeStartingNode() = default;

    ~ComputeStartingNode() = default;

    virtual std::pair<int, int> computeShortestEdge(std::shared_ptr<IProblem> problem) const override;

    virtual std::vector<std::pair<int, int>> computeShortestEdges(std::shared_ptr<IProblem> problem) const override;

    virtual std::pair<int, int> computeLongestEdge(std::shared_ptr<IProblem> problem) const override;

    virtual std::vector<std::pair<int, int>> computeLongestEdges(std::shared_ptr<IProblem> problem) const override;
};