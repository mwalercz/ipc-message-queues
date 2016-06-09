//
// Created by maciek on 06/06/16.
//

#include <iostream>
#include "LindaClient.hpp"
#include "../constants.hpp"

int main() {
    std::cout << "Producer\n";
    LindaClient client(keysFileName);

    for (int i = 0; i < 100; ++i) {
        std::string tuple = "1, 3.1, \"linda\"";
        client.output(tuple);
        std::cout << "Sent tuple: " << tuple;
    }

}