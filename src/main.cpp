#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "Server.hpp"
#include "LindaClient.hpp"

static const int n = 10;


void autoconsumer() {
    sleep(1);
    LindaClient client("/tmp/queues_keys");
    while(1) {
        int dt = rand() % 3;
        sleep(dt);
        client.output(std::to_string(getpid()));
        client.read("integer:="+std::to_string(getpid()), 0);
        client.input("integer:="+std::to_string(getpid()), 0);
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
        std::cout << i+1 << " started.\r\t";
    }
    std::cout << "\nStarting server... ";
    try {
        Server server("/tmp/queues_keys");
        std::cout << "done. Starting processes. Serving." << std::endl;
        server.serve();
    } catch(std::exception& e) {
        std::cout << "abort: " << e.what() << std::endl;
        // prints a command to be copied and executed if user wish
        for(pid_t i : pids) {
            std::cout << " " << i;
            kill(i, SIGKILL);
            int status;
            wait(&status);
        }
        std::cout << std::endl;
        return 1;
    }


    return 0;
}
