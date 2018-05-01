#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <cstdlib>
#include <iostream>
#include <string>

#include "../tcpUtil/tcpUtil.h"
 
using namespace std;

class serverThread {
    private:
        string name;
        int serverFd;
        void listenForRequests();
        void delegateProperFunctionalityForClient(char* buffer, int connectionFd, tcpUtil* tcp);
    public:
        serverThread(string name, int serverFd);
        ~serverThread();
};

#endif