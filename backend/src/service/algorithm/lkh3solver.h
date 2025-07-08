#pragma once

#include "service/algorithm/ialgorithm.h"
#include "lkh3config.h" 

/*
    C++ wrapper for LKH3 algorithm (version 3.0.13) downloaded at http://akira.ruc.dk/~keld/research/LKH-3/
*/
class LKH3Solver : public IAlgorithm{
public:

    explicit LKH3Solver(const std::string& lkhPath,  const std::string& resourcesPath, LKH3Config config = {});

    virtual std::shared_ptr<ISolution> execute(std::shared_ptr<IProblem> problem) override;

    virtual std::string name() const override;

    void setConfig(LKH3Config config);

    void resetConfig();
private:

    std::string m_lkhPath;

    std::string m_workingDir;

    LKH3Config m_config;

    std::string m_resourcesPath;

    std::string writeParamFile(const std::string& paramFile);

    bool runLKH(const std::string& paramFile);

    std::shared_ptr<ISolution> readSolution(std::shared_ptr<IProblem> problem);

    void prepareForProblem(const std::shared_ptr<IProblem>& problem, std::string tspFile, std::string solFile);


};

