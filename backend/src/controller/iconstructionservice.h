#pragma once

#include <string>
#include <vector>

class IConstructionService{

public:
    virtual ~IConstructionService() =default;

    virtual void construct(std::string path, const std::string& filename, const std::vector<std::vector<int>>& adjMatrix) const =0;

};