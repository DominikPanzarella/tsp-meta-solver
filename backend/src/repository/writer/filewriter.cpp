#include "filewriter.h"


void FileWriter::setSuccessor(std::shared_ptr<FileWriter> next){
    successor = std::move(next);
}

std::shared_ptr<FileWriter> FileWriter::getSuccessors() {
    return successor;
}

bool FileWriter::write(std::string file_path, std::string extension, const std::shared_ptr<ISolutionCollector>& solutionCollector,const std::shared_ptr<IConfigProvider>& configProvider ) const {
    std::string contentType = extension;

    if(canHandle(contentType)){
        return writeFile(file_path, solutionCollector, configProvider);
    }else if(successor){
        return successor->write(file_path, extension, solutionCollector, configProvider);
    }
    else {
        std::cerr << "[FileWriter] Nessun writer compatibile trovato per: " << file_path << std::endl;
        return false;
    }
}