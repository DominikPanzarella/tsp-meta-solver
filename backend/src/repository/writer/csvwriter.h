#pragma once

#include "filewriter.h"

class CsvWriter : public FileWriter {
public:
    CsvWriter() = default;

    ~CsvWriter() = default;

protected:

    virtual bool canHandle(const std::string& content) const override;

    virtual bool writeFile(const std::shared_ptr<ISolutionCollector>& solutionCollector) const override;


};