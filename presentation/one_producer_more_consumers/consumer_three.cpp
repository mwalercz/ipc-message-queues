//
// Created by maciek on 08/06/16.
//
#include <iostream>
#include "LindaClient.hpp"
#include "../constants.hpp"

int main() {
    std::cout << "Consumer\n";
    LindaClient client(keysFileName);

    std::string query = "integer:=1, float:>4, string:=*";
    std::cout << "Expecting read: " << query << "\n";
    std::string tuple = client.read(query, getTimeval());
    std::cout << "Received read: " << tuple << "\n";

}
