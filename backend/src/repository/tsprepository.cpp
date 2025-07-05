
#include "tsprepository.h"

// ----- Including reader files
#include "repository/reader/attreader.h"
#include "repository/reader/ceil2dreader.h"
#include "repository/reader/euc2dreader.h"
#include "repository/reader/georeader.h"
#include "repository/reader/matrixreader.h"

// ----- Including writer files
#include "repository/writer/csvwriter.h"

TspRepository::TspRepository(){

    auto euc2DReader = std::make_shared<Euc2DReader>();
    auto ceil2dReader = std::make_shared<Ceil2dReader>();
    auto matrixReader = std::make_shared<MatrixReader>();
    auto geoReader = std::make_shared<GeoReader>();
    auto attReader = std::make_shared<AttReader>();

    // ---- Setup chain of responsibility (Reader)
    euc2DReader->set_successor(ceil2dReader);
    ceil2dReader->set_successor(matrixReader);
    matrixReader->set_successor(geoReader);
    geoReader->set_successor(attReader);

    this->reader = euc2DReader;     //First reader in the chain

    // ---- Setup chain of responsibility (Writer)
    auto csvWriter = std::make_shared<CsvWriter>();

    this->writer = csvWriter;       // First writer in the chain

}

std::shared_ptr<IProblem> TspRepository::read(const std::string& file_path){
    return reader->read(file_path);
}


bool TspRepository::write(std::string file_path, std::string extension, const std::shared_ptr<ISolutionCollector>& solutionCollector){
    return writer->write(file_path, extension, solutionCollector);
}
