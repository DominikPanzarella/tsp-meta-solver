#pragma once



//////////////
// #INCLUDE //
//////////////

#include "service/problem/iproblem.h"

#include <string>


//interface
class Reader{
public:
    
    virtual std::shared_ptr<IProblem> read(const std::string& file_path) =0 ;

protected:
    virtual std::shared_ptr<IProblem> readInternal(std::istream& input) =0;
};