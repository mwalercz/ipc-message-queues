//
// Created by maciek on 06/06/16.
//

#include <iostream>
#include "LindaClient.hpp"

int main() {
    std::cout << "Producer\n";
    LindaClient client("/tmp/queues_keys");

    std::string tuple_one = "1, 3.1, \"linda\"";
    client.output(tuple_one);
    std::cout << "Sent tuple: " << tuple_one << "\n";

    std::string tuple_two = "1, 5, \"two\"";
    client.output(tuple_two);
    std::cout << "Sent tuple: " << tuple_two << "\n";

    std::string tuple_three = "\"three\", \"hana\", 1, 5.1";
    client.output(tuple_three);
    std::cout << "Sent tuple: " << tuple_three << "\n";

}