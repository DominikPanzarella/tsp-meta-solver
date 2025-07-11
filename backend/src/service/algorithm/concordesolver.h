#pragma once

#include "service/algorithm/ialgorithm.h"
#include "repository/configuration2/config/igeneralsetting.h"
#include "repository/configuration2/config/iinstancesetting.h"

class ConcordeSolver : public IAlgorithm{
public:

    explicit ConcordeSolver(const std::string& concordePath, const std::string& resourcesPath , std::shared_ptr<IGeneralSetting> concordeSetting);

    virtual std::shared_ptr<ISolution> execute(std::shared_ptr<IProblem> problem,std::shared_ptr<IInstanceSetting> instanceSettings) override;

    virtual std::string name() const override;

private:

    std::string m_concordePath;

    std::string m_workingDir;

    std::string m_resourcesPath;

    std::shared_ptr<IGeneralSetting> m_config;

    bool runConcorde(const std::string& tspFile, const std::string& problemName,std::shared_ptr<IInstanceSetting> instanceSettings);

    std::shared_ptr<ISolution> readSolution(std::shared_ptr<IProblem> problem);

};