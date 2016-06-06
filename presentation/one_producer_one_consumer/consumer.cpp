//
// Created by maciek on 06/06/16.
//
#include "LindaClient.hpp"
int main() {
    LindaClient client("/tmp/queues_keys");
    client.input("int:=1, float:>3, string:=\"linda\"");
}
