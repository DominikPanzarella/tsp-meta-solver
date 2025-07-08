#include "start.h"
#include "utils/initializer.h"

void Start::start(int argc, char *argv[]){
    std::string path;
    if(argc > 1)        path = argv[1];
    else                throw std::runtime_error("Resources directory must be provided");

    Initializer init(path);

    Initializer::init(argc, argv);
}