#include <iostream>
#include <stdexcept>

#include "Server.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2){
        std::cout << "Usage: ./server filepath" << std::endl;
        exit(-1);
    }
    std::string filepath = argv[1];
    std::cout << "Starting server..." << std::endl;
    try {
        Server server(filepath);
        server.serve();
    } catch(std::exception& e) {
        std::cout << "abort: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

