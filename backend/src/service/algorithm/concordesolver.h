#pragma once

#include "service/algorithm/ialgorithm.h"
#include "concordeconfig.h"

class ConcordeSolver : public IAlgorithm{
public:

    explicit ConcordeSolver(const std::string& concordePath, ConcordeConfig config = {});

    virtual std::shared_ptr<ISolution> execute(std::shared_ptr<IProblem> problem) override;

    virtual std::string name() const override;

    void setConfig(const ConcordeConfig& config);

    void resetConfig();
    
private:

    std::string m_concordePath;

    std::string m_workingDir;

    ConcordeConfig m_config;

    bool runConcorde(const std::string& tspFile, const std::string& problemName);

    std::shared_ptr<ISolution> readSolution(std::shared_ptr<IProblem> problem);

};