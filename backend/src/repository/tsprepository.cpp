
#include "tsprepository.h"

#include "reader/attreader.h"
#include "reader/ceil2dreader.h"
#include "reader/euc2dreader.h"
#include "reader/georeader.h"
#include "reader/matrixreader.h"

TspRepository::TspRepository(){

    auto euc2DReader = std::make_shared<Euc2DReader>();
    auto ceil2dReader = std::make_shared<Ceil2dReader>();
    auto matrixReader = std::make_shared<MatrixReader>();
    auto geoReader = std::make_shared<GeoReader>();
    auto attReader = std::make_shared<AttReader>();

    // Setup chain of responsibility
    euc2DReader->set_successor(ceil2dReader);
    ceil2dReader->set_successor(matrixReader);
    matrixReader->set_successor(geoReader);
    geoReader->set_successor(attReader);

    this->reader = euc2DReader;     //First reader in the chain

}

std::shared_ptr<IProblem> TspRepository::read(const std::string& file_path){
    return reader->read(file_path);
}

//TODO: to implement export (need a solution object)
bool TspRepository::write(const std::string& file_path){
    //Empty for now
}
