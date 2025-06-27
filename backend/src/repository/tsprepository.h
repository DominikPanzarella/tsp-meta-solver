
#include "service/itsprepositoy.h"
#include "reader/tspreader.h"

class TspRepository : public ITspRepository{
public:

    TspRepository();

    virtual std::shared_ptr<IProblem> read(const std::string& file_path) override;

    //TODO: to implement export (need a solution object)
    virtual bool write(const std::string& file_path) override;


protected:

private:
    std::shared_ptr<TspReader> reader;

};