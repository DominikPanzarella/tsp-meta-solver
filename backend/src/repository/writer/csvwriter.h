#pragma once

#include "filewriter.h"
#include <functional>
#include <vector>
#include "service/algorithm/isolution.h"
#include <unordered_map>

class CsvWriter : public FileWriter {
public:
    CsvWriter();

    ~CsvWriter() = default;


protected:

    virtual bool canHandle(const std::string& content) const override;

    virtual bool writeFile(std::string file_path, const std::shared_ptr<ISolutionCollector>& solutionCollector) const override;


    void registerWriteFuncs();

    using WriteFunc = std::function<void(const std::string&, const std::vector<std::shared_ptr<ISolution>>&)>;

    std::unordered_map<std::string, WriteFunc> algoWriters;

};