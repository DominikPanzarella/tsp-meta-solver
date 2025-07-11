#pragma once

#include "service/algorithm/ialgorithm.h"
#include "repository/configuration2/config/lkh3generalsetting.h"
#include "repository/configuration2/config/iinstancesetting.h"

/*
    C++ wrapper for LKH3 algorithm (version 3.0.13) downloaded at http://akira.ruc.dk/~keld/research/LKH-3/
*/
class LKH3Solver : public IAlgorithm{
public:

    explicit LKH3Solver(const std::string& lkhPath,  const std::string& resourcesPath, std::shared_ptr<LKH3GeneralSetting> lkh3Setting);

    virtual std::shared_ptr<ISolution> execute(std::shared_ptr<IProblem> problem,std::shared_ptr<IInstanceSetting> instanceSettings) override;

    virtual std::string name() const override;

private:

    std::string m_lkhPath;

    std::string m_workingDir;

    std::string m_resourcesPath;

    std::shared_ptr<LKH3GeneralSetting> m_config;


    std::string writeParamFile(const std::string& paramFile,std::shared_ptr<IInstanceSetting> instanceSettings);

    bool runLKH(const std::string& paramFile);

    std::shared_ptr<ISolution> readSolution(std::shared_ptr<IProblem> problem, std::shared_ptr<IInstanceSetting> instanceSettings);

};

