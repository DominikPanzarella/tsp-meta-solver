#pragma once


#include <string>
#include <vector>

class IConstructionRepository {
public:

    virtual ~IConstructionRepository() =default;

    virtual void construct(std::string path, const std::string& filename, const std::vector<std::vector<int>>& adjMatrix) const =0;

};