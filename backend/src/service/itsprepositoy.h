

#include "repository/problem/iproblem.h"

class ITspRepository{
public:

    virtual std::shared_ptr<IProblem> read(const std::string& file_path) =0;

    //TODO: to implement export (need a solution object)
    virtual bool write(const std::string& file_path) = 0;
};