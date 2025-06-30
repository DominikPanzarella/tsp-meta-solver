#pragma once

#include "ipath.h"
#include <vector>

class Path : public IPath{
public:

    Path() = default;

    Path(const std::vector<int>& nodes, double cost);

    virtual ~Path() = default;

    virtual void reset() override;

    virtual void setNodes(const std::vector<int>& tour) override;

    virtual const std::vector<int>& nodes() const override;

    virtual void setCost(double c) override;

    virtual double getCost() const override;

private:

    double m_cost;

    std::vector<int> m_nodes;
};