#pragma once

#include "controller/itspservice.h"
#include "service/itsprepositoy.h"

class TspService : public ITspService {
public:

    ~TspService() = default;

    static const std::shared_ptr<TspService>& getInstance();

    virtual std::shared_ptr<IProblem> read(const std::string& file_path) override;

    virtual bool write(std::string file_path, std::string extension, const std::shared_ptr<ISolutionCollector>& solutionCollector) override;

private:
    std::unique_ptr<ITspRepository> repositoryLayer;

    TspService();

};
