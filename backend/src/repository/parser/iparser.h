#pragma once

#include <string>
#include "repository/parser/jsonnode.h"

class IParser {
public: 
    virtual JSON read(const std::string& file_path) =0 ;
};