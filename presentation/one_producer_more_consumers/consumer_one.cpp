//
// Created by maciek on 06/06/16.
//
#include <iostream>
#include "LindaClient.hpp"
#include "../constants.hpp"

int main() {
    std::cout << "Consumer\n";
    LindaClient client(keysFileName);


    std::string query = "integer:=1, float:>3., string:=\"linda\"";
    std::cout << "Expecting: " << query << "\n";
    std::string tuple = client.input(query, getTimeval());
    std::cout << "Received: " << tuple << "\n";
}
