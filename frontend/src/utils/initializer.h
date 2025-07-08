#pragma once

#include "service/problem/iproblem.h"
#include "service/algorithm/ialgorithm.h"

#include <string>

class Initializer {
public:

    Initializer(const std::string resourcesPath);

    static void init(int argc, char *argv[]);

private:

    static std::vector<std::string> collectTspInstances(const std::string& dir);

    static std::vector<std::shared_ptr<IAlgorithm>> algoToTest();

    static std::vector<std::shared_ptr<IProblem>> problems;

    static std::string m_resourcesPath;
};