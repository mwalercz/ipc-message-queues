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
    for(int i = 0; i < 100; i++) {
        std::string query = "integer:=*, float:*., string:*";
        std::cout << "Expecting: " << query << "\n";
        std::string tuple = client.input(query, tv);
        std::cout << "Received: " << tuple << "\n";
    }
}
