#pragma once

#include "writer.h"


class FileWriter : public Writer {
public:
    //template meethod
    virtual bool write(std::string file_path, std::string extension, const std::shared_ptr<ISolutionCollector>& solutionCollector,const std::shared_ptr<IConfigProvider>& configProvider ) const override;

    void setSuccessor(std::shared_ptr<FileWriter> next);

    std::shared_ptr<FileWriter> getSuccessors();


protected:

    std::shared_ptr<FileWriter> successor;

    std::ostream* output = nullptr;

    // Fasi del Template Method (da override nelle subclassi)

    virtual bool canHandle(const std::string& content) const =0;

    virtual bool writeFile(std::string file_path, const std::shared_ptr<ISolutionCollector>& solutionCollector, const std::shared_ptr<IConfigProvider>& configProvider) const = 0;
};