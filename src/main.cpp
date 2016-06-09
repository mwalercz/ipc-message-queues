#include <iostream>
#include <vector>
#include "unistd.h"

#include "Server.hpp"
#include "LindaClient.hpp"

static const int n = 100;


void autoconsumer() {
    sleep(5);
    LindaClient client("/tmp/queues_keys");
    timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    while(1) {
        client.output(std::to_string(getpid()));
        client.read("integer:="+std::to_string(getpid()), tv);
        client.input("integer:="+std::to_string(getpid()), tv);
    }
}

int main() {
    std::vector<int> pids;
    std::cout << "Preparing processes:\n\t";
    for(int i=0; i < n; ++i) {
        int pid;
        if ((pid=fork()) == 0) {
            autoconsumer();
            return 0;
        }
        pids.push_back(pid);
        std::cout << i << " started.\r\t";
    }
    std::cout << "\nStarting server... ";
    try {
        Server server("/tmp/queues_keys");
        std::cout << "done. Starting processes. Serving." << std::endl;
        server.serve();
    } catch(std::exception& e) {
        std::cout << "abort: " << e.what() << std::endl;
        std::cout << "kill -9";
        for(int i : pids) {
            std::cout << " " << i;
        }
        std::cout << std::endl;
        return 1;
    }


    return 0;
}
