//
// Created by maciek on 06/06/16.
//
#include <iostream>
#include "LindaClient.hpp"
#include "../constants.hpp"

int main() {
    std::cout << "Consumer\n";

    LindaClient client(keysFileName);

    for(int i = 0; i < 100; i++) {
        std::string query = "integer:=*, float:*., string:*";
        std::cout << "Expecting: " << query << "\n";
        std::string tuple = client.input(query, getTimeval());
        std::cout << "Received: " << tuple << "\n";
    }
}
