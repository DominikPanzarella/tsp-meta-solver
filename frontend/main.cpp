#include <iostream>

#include "controller/tspcontroller.h"

int main(int argc, char *argv[])
{
    const std::shared_ptr<TspController>& controller = TspController::getInstance();
    
    std::cout << "Funziona" << std::endl;

    return 0;
}