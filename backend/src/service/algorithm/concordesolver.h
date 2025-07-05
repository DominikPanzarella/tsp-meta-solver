#pragma once

#include "service/algorithm/ialgorithm.h"

class ConcordeSolver : public IAlgorithm{
public:

    explicit ConcordeSolver(const std::string& concordePath);

    virtual std::shared_ptr<ISolution> execute(std::shared_ptr<IProblem> problem) override;

    virtual std::string name() const override;
    
private:

    std::string m_concordePath;

    std::string m_workingDir;

    bool runConcorde(const std::string& tspFile, const std::string& problemName);

    std::shared_ptr<ISolution> readSolution(std::shared_ptr<IProblem> problem);


};