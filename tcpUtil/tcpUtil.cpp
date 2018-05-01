#include <cstdlib>
#include <iostream>
#include <string>

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "tcpUtil.h"
#include "../logging/logger.h"

#define MAX_BACKLOG		5
#define MAX_BUFFER      128
using namespace std;

tcpUtil::tcpUtil(int connectionFd) {
    this->connectionFd = connectionFd;
}

int  tcpUtil::readBytes(char* buffer) {
    //wczytaj rozmiar danych
    int received_size = 0;

    int return_status = read(connectionFd, &received_size, sizeof(received_size));
    if (return_status > 0) {
        logger::logInfo("readBytes", "wielkosc kolejnych danych to " + to_string(ntohl(received_size)));
        
        received_size = ntohl(received_size);
    }
    else {
        // Handling erros here
        logger::logError("readBytes", "Nie mozna odczytac wielkosci nadchodzacych danych!");
    }

    int in;
    while ( (in = read(connectionFd,
                       buffer, received_size)) > 0) {
        buffer[in] = 0;
        break;
    }

    logger::logInfo("readBytes", "Poprawnie odczytano dane");
    return strlen(buffer);
}

void tcpUtil::sendData(char* buffer) {
    int number_to_send = strlen(buffer); // Put your value
    int converted_number = htonl(number_to_send);

    // Write the number to the opened socket
    write(connectionFd, &converted_number, sizeof(converted_number));

    write(connectionFd, buffer, number_to_send);
}

void tcpUtil::simpleSendData(char* buffer) {
    write(connectionFd, buffer, strlen(buffer));
}

void tcpUtil::sendPositiveMessage() {
    char *p = "1";
    simpleSendData(p);
    
    logger::logInfo("sendPositiveMessage", "wyslano odpowiedz pozytywna");
}

void tcpUtil::sendNegativeMessage() {
    char *p = "";
    simpleSendData(p);
    
    logger::logInfo("sendNegativeMessage", "wyslano odpowiedz neatywna");
}