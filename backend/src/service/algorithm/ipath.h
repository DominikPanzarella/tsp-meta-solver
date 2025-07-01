#pragma once

#include <iostream>

class IPath{
public:
    virtual ~IPath() = default;

    virtual void reset() =0;

    virtual void setNodes(const std::vector<int>& tour) =0;

    virtual const std::vector<int>& nodes() const =0;

    virtual void setCost(double c) = 0;

    virtual double getCost() const =0;

    virtual int getDimension() const =0;
};