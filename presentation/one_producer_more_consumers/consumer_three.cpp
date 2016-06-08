//
// Created by maciek on 08/06/16.
//
#include <iostream>
#include "LindaClient.hpp"
int main() {
    std::cout << "Consumer\n";

    LindaClient client("/tmp/queues_keys");
    timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;

    std::string query = "integer:=1, float:>4, string:=*";
    std::cout << "Expecting read: " << query << "\n";
    std::string tuple = client.read(query, tv);
    std::cout << "Received read: " << tuple << "\n";

    std::cout << "Expecting input: " << query << "\n";
    std::string tuple_two = client.input(query, tv);
    std::cout << "Received input: " << tuple_two << "\n";

    //should be timed out
    std::cout << "Expecting input: " << query << "\n";
    std::string tuple_three = client.input(query, tv);
    std::cout << "Received input: " << tuple_three << "\n";
}
