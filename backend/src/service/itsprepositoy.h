#pragma once

#include "service/problem/iproblem.h"
#include "service/algorithm/isolutioncollector.h"

class ITspRepository{
public:

    virtual ~ITspRepository() = default;

    virtual std::shared_ptr<IProblem> read(const std::string& file_path) =0;

    virtual bool write(std::string file_path, std::string extension, const std::shared_ptr<ISolutionCollector>& solutionCollector) =0;
};