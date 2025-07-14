#pragma once

#include "repository/construction/instanceconstruction.h"
#include "service/iconstructionrepository.h"


class ConstructionRepository : public IConstructionRepository {
public:

    virtual ~ConstructionRepository() = default;

    ConstructionRepository();

    virtual void construct(std::string path, const std::string& filename, const std::vector<std::vector<int>>& adjMatrix) const override;

private:
    std::shared_ptr<InstanceConstruction> m_ic;

};