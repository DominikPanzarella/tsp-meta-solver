#pragma once

#include "service/algorithm/ialgorithm.h"

/*
    C++ wrapper for LKH3 algorithm (version 3.0.13) downloaded at http://akira.ruc.dk/~keld/research/LKH-3/
*/
class LKH3Solver : public IAlgorithm{
public:

    explicit LKH3Solver(const std::string& lkhPath);

    virtual std::shared_ptr<ISolution> execute(std::shared_ptr<IProblem> problem) override;

    virtual std::string name() const override;
    
private:

    std::string m_lkhPath;

    std::string m_workingDir;

    std::string writeParamFile(const std::string& tspFile, const std::string& solFile, const std::string& paramFile);

    bool runLKH(const std::string& paramFile);

    std::shared_ptr<ISolution> readSolution(const std::string& solFile, std::shared_ptr<IProblem> problem);

};