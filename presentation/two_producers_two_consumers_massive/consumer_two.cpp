//
// Created by maciek on 08/06/16.
//

#include <iostream>
#include "../constants.hpp"
#include "LindaClient.hpp"
int main() {
    std::cout << "Consumer\n";

    LindaClient client(keysFileName);

    for(int i = 0; i < 100; i++) {
        std::string query = "string:=*, float:*., integer:*";
        std::cout << "Expecting: " << query << "\n";
        std::string tuple = client.input(query, getTimeval());
        std::cout << "Received: " << tuple << "\n";
    }
}