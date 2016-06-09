//
// Created by maciek on 08/06/16.
//
#include <iostream>
#include "LindaClient.hpp"
#include "../constants.hpp"

int main() {
    std::cout << "Consumer\n";

    LindaClient client("/tmp/queues_keys");
    std::string query = "string:>\"th\", string:=\"hana\", integer:*, float:*";
    std::cout << "Expecting: " << query << "\n";
    std::string tuple = client.input(query, getTimeval());
    std::cout << "Received: " << tuple << "\n";
}
