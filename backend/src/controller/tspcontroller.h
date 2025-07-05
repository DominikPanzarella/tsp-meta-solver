#pragma once

#include "controller/itspservice.h"

class TspController {
public:

    ~TspController() = default;

    static const std::shared_ptr<TspController>& getInstance();

    std::shared_ptr<IProblem> read(const std::string& file_path);

    bool write(std::string file_path, std::string extension, const std::shared_ptr<ISolutionCollector>& solutionCollector);

private:
    std::shared_ptr<ITspService> serviceLayer;

    TspController();


};