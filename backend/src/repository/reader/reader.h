#pragma once


#include <string>

//////////////
// #INCLUDE //
//////////////

//interface
class Reader{
public:
    
    virtual void read(const std::string& file_path) =0 ;
};