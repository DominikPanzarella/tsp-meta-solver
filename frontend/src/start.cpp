#include "start.h"
#include "utils/initializer.h"

void Start::start(int argc, char *argv[]){
    std::string path;
    std::string results_path;
    std::string format;
    if(argc > 3){
        path = argv[1];
        results_path = argv[2];
        format = argv[3];
    }        
    else                throw std::runtime_error("Resources/Results directory must be provided");

    Initializer init(path, results_path, format);

    Initializer::init(argc, argv);
}