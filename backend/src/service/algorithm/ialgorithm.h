#pragma once

#include <iostream>
#include "repository/problem/iproblem.h"
#include "service/algorithm/isolution.h"

//Algorithm Interface
class IAlgorithm{
public:
    virtual std::shared_ptr<ISolution> execute(std::shared_ptr<IProblem> problem) = 0;

    virtual ~IAlgorithm() = default;

    virtual std::string name() const = 0;

};