#pragma once

#include <string>
#include <vector>

class InstanceConstruction {
public:

    ~InstanceConstruction() = default;

    virtual void construct(std::string path, const std::string& filename, const std::vector<std::vector<int>>& adjMatrix) const =0;
};