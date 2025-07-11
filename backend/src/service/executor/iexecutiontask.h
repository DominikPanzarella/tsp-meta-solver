#pragma once

#include "service/problem/iproblem.h"
#include "service/algorithm/isolution.h"
#include "service/algorithm/ialgorithm.h"
#include "repository/configuration2/config/iinstancesetting.h"

class IExecutionTask{
public:
    virtual ~IExecutionTask() = default;

    virtual std::shared_ptr<ISolution> execute() =0;

    virtual std::shared_ptr<IAlgorithm> getAlgorithm() const =0;

    virtual std::shared_ptr<IProblem> getProblem() const =0;

    virtual std::shared_ptr<IInstanceSetting> getInstanceSetting() const =0;
};