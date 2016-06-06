//
// Created by maciek on 06/06/16.
//

#include "LindaClient.hpp"

int main() {
    LindaClient client("/tmp/queues_keys");
    client.output("1, 3.1, \"linda\"");
}