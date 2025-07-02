#pragma once

#include "service/algorithm/ialgorithm.h"

class ConcordeSolver : public IAlgorithm{
public:

    explicit ConcordeSolver(const std::string& concordePath);

    virtual std::shared_ptr<ISolution> execute(std::shared_ptr<IProblem> problem) override;

    virtual std::string name() const override;
    
private:

};