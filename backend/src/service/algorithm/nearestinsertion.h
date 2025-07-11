#pragma once

#include "service/algorithm/ialgorithm.h"

class NearestInsertion : public IAlgorithm {
public:

    virtual std::shared_ptr<ISolution> execute(std::shared_ptr<IProblem> problem, std::shared_ptr<IInstanceSetting> instanceSettings) override;

    virtual std::string name() const override;

    NearestInsertion() =default;   

private:

};