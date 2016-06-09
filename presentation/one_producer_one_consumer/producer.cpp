//
// Created by maciek on 06/06/16.
//

#include <iostream>
#include "LindaClient.hpp"
#include "../constants.hpp"

int main() {
    std::cout << "Producer\n";
    LindaClient client(keysFileName);

    std::string tupleExpected = "1, 3.1, \"linda\"";
    client.output(tupleExpected);
    std::cout << "Sent tuple: " << tupleExpected + "\n";
}