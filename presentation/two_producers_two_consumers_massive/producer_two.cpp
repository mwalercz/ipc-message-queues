//
// Created by maciek on 08/06/16.
//

#include <iostream>
#include "LindaClient.hpp"
#include "../constants.hpp"

int main() {
    std::cout << "Producer\n";
    LindaClient client(keysFileName);

    for (int i = 0; i < 100; ++i) {
        std::string tuple = "\"Ala ma kota.\", 5., 8";
        client.output(tuple);
        std::cout << "Sent tuple: " << tuple+ "\n";
    }

}