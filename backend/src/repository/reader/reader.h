#pragma once


#include <string>

//////////////
// #INCLUDE //
//////////////

//interface
class Reader{
protected:
    std::shared_ptr<Reader> successor;

public:
    
    void set_successor(std::shared_ptr<Reader> next){
        successor = std::move(next);
    }

    virtual void read(const std::string& file_path) =0 ;

private:

};