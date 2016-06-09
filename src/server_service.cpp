#include <iostream>
#include <stdexcept>

#include "Server.hpp"

int main() {
    std::cout << "Starting server..." << std::endl;
    try {
        Server server("/tmp/queues_keys");
        server.serve();
    } catch(std::exception& e) {
        std::cout << "abort: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

