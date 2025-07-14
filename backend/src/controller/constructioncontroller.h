#pragma once

#include "controller/iconstructionservice.h"
#include "service/generator/shortestPath/ishortestpath.h"
#include "controller/igeneratorservice.h"

class ConstructionController{
public:
    ~ConstructionController() = default;

    static const std::shared_ptr<ConstructionController>& getInstance();

    void construct(std::string path, const std::string& filename, const std::vector<std::vector<int>>& adjMatrix) const;

    std::vector<std::vector<int>> generateNI(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const;

    std::vector<std::vector<int>> generateNN(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const;

    std::vector<std::vector<int>> generateFI(int n,const std::shared_ptr<IShortestPath>& shortestPathSolver) const;

 private:
    std::shared_ptr<IConstructionService> serviceLayer;

    std::shared_ptr<IGeneratorService> ni_service;

    std::shared_ptr<IGeneratorService> fi_service;

    std::shared_ptr<IGeneratorService> nn_service;

    ConstructionController();

};

