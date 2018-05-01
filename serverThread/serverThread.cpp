#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "serverThread.h"
#include "../tcpUtil/tcpUtil.h"
#include "../functions/loginUtil.h"
#include "../logging/logger.h"

#define MAX_BACKLOG		5
#define MAX_BUFFER      128

using namespace std;

serverThread::serverThread(string name, int serverFd) {
    this->name = name;
    this->serverFd = serverFd;
    
    listenForRequests();
}

void serverThread::listenForRequests() {
    char * buffer = new char[MAX_BUFFER];

    listen(serverFd, MAX_BACKLOG);

    while(1) {
        int connectionFd = accept(serverFd,
                              (struct sockaddr *)NULL, NULL);
        tcpUtil tcp(connectionFd);

        logger::logInfo("listenForRequests", "Nowe polaczanie od klienta");

        ///Musimy otrzymac 8 cyfrowa liczba identyfikujaca funkcje do wywolania
        if(tcp.readBytes(buffer) != 8) {
            logger::logError("listenForRequests", "Otrzymano niepoprawne dane dotyczace wywolania operacji na serwerze");
            return;
        }

        delegateProperFunctionalityForClient(buffer, connectionFd, &tcp);
    }
}

void serverThread::delegateProperFunctionalityForClient(char* buffer, int connectionFd, tcpUtil* tcp) {

    if(strcmp(buffer, "12345678") == 0) {
        logger::logInfo("delegateProperFunctionalityForClient", "Wywolanie funkcji logowania");
        loginUtil login(connectionFd, tcp);
        login.loginClient();
    } else {
        logger::logError("delegateProperFunctionalityForClient", "Proba wywolania niezidentyfikowanej funkcji!!!");
    }
}

serverThread::~serverThread() {
    
}