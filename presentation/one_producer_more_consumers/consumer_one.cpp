//
// Created by maciek on 06/06/16.
//
#include <iostream>
#include "LindaClient.hpp"
int main() {
    std::cout << "Consumer\n";

    LindaClient client("/tmp/queues_keys");
    timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    std::string query = "integer:=1, float:>3., string:=\"linda\"";
    std::cout << "Expecting: " << query << "\n";
    std::string tuple = client.input(query, tv);
    std::cout << "Received: " << tuple << "\n";
}
