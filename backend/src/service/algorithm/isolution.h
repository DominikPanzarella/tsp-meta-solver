#pragma once

#include "repository/problem/iproblem.h"
#include "service/algorithm/ipath.h"

class ISolution{
public:
    virtual ~ISolution()=default;

    virtual const std::shared_ptr<IProblem> getProblem() const = 0;
    
    virtual void setPath(std::shared_ptr<IPath> path) =0;

    virtual const std::shared_ptr<IPath>& getPath() const =0;

    virtual double getCost() const = 0;

    virtual void setExecutionTime(int ms) = 0;

    virtual int getExecutionTime() const = 0;

    virtual int getDimension() const =0;

    virtual void reset() = 0;

};