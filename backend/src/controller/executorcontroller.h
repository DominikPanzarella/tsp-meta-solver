#pragma once

#include "controller/iexecutorservice.h"
#include <memory>
#include "service/algorithm/ialgorithm.h"
#include "service/problem/iproblem.h"
#include "repository/configuration2/config/iinstancesetting.h"
#include "service/algorithm/isolutioncollector.h"


class ExecutorController {
public:
    ~ExecutorController() = default;

    static const std::shared_ptr<ExecutorController>& getInstance();


    void add(const std::shared_ptr<IAlgorithm>& algo, const std::shared_ptr<IProblem>& problem, const std::shared_ptr<IInstanceSetting>& setting);

    void run() const;

    void clear();

    const std::shared_ptr<ISolutionCollector>& getSolutionCollector() const;


private:

    std::shared_ptr<IExecutorService> serviceLayer;

    ExecutorController();

};