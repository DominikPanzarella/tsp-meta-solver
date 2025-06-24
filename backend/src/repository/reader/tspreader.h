#pragma once

//////////////
// #INCLUDE //
//////////////

#include "reader.h"

class TspReader : public Reader{
public:

    virtual void read(const std::string& file_path);

};