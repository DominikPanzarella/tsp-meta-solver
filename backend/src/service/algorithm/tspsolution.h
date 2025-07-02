#pragma once

#include "isolution.h"

class TspSolution : public ISolution{
public:

    TspSolution() =default;

    TspSolution(std::shared_ptr<IPath> path, std::shared_ptr<IProblem> problem);

    virtual ~TspSolution()=default;
    
    virtual void setPath(std::shared_ptr<IPath> path) override;

    virtual const std::shared_ptr<IPath>& getPath() const override;

    virtual double getCost() const override;

    //TODO: how to track time? and labelling? to improve

    virtual void setExecutionTime(int ms) override;
    
    virtual int getExecutionTime() const override;

    virtual int getDimension() const override;

    virtual const std::shared_ptr<IProblem> getProblem() const override;

private:

    std::shared_ptr<IPath> m_path;

    std::shared_ptr<IProblem> m_problem;

    int m_executionTimeMs = 0.0;          //ms
};