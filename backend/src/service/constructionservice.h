#pragma once

#include "controller/iconstructionservice.h"
#include "service/iconstructionrepository.h"
#include <memory>
#include <vector>
#include <string>


class ConstructionService : public IConstructionService{
public:

    ~ConstructionService() = default;

    static const std::shared_ptr<ConstructionService>& getInstance();

    virtual void construct(std::string path, const std::string& filename, const std::vector<std::vector<int>>& adjMatrix) const override;


private:
    ConstructionService();

    std::unique_ptr<IConstructionRepository> repositoryLayer;
};