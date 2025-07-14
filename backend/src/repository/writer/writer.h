#pragma once

#include <string>

#include  "service/algorithm/isolutioncollector.h"
#include "repository/configuration2/iconfigprovider.h"

class Writer {
    
public:

    virtual bool write(std::string file_path, std::string extension, const std::shared_ptr<ISolutionCollector>& solutionCollector, const std::shared_ptr<IConfigProvider>& configProvider ) const =0;

};