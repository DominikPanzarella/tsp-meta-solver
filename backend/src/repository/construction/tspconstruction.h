#pragma once

#include "repository/construction/instanceconstruction.h"

class TspConstruction : public InstanceConstruction{

public:
    ~TspConstruction() = default;

    static const std::shared_ptr<TspConstruction>& getInstance();

    virtual void construct(std::string path, const std::string& filename, const std::vector<std::vector<int>>& adjMatrix) const override;

private:

    TspConstruction() =default;
};