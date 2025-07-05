#pragma once

#include "service/itsprepositoy.h"
#include "repository/reader/reader.h"
#include "repository/writer/writer.h"


class TspRepository : public ITspRepository{
public:

    TspRepository();

    virtual std::shared_ptr<IProblem> read(const std::string& file_path) override;

    virtual bool write(std::string file_path, std::string extension, const std::shared_ptr<ISolutionCollector>& solutionCollector) override;

protected:

private:
    std::shared_ptr<Reader> reader;

    std::shared_ptr<Writer> writer;

};