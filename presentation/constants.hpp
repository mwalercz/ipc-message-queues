//
// Created by maciek on 09/06/16.
//
#include <time.h>
#include <string>
static timeval getTimeval(){
    timeval tv;
    tv.tv_sec = 99999;
    tv.tv_usec = 99999;
    return tv;
}

static std::string keysFileName = "/tmp/queues_keys";


