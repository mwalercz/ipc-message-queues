//
// Created by maciek on 06/06/16.
//
#include <iostream>
#include "Server.hpp"
#include "../constants.hpp"

int main() {
    std::cout << "Server\n";
    Server server(keysFileName);
    server.serve();
}
