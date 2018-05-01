/**
 *  @file    serwerTCP.cpp
 *  @author  Emil Hotkowski
 *  @date    30/04/2018
 *  @version 1.0
 *
 *  @brief Serwer aplikacji do zgałaszania bugow.
 *
 *  @section DESCRIPTION
 *
 *  Serwer aplikacji do zgałaszania bugow.
 *  Plik glowny zajmuje sie odpaleniem watkow serwera aby rozlozyc prace.
 *
 */

#include <string>
#include <iostream>
#include <thread>

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "serverThread/serverThread.h"

#include "logging/logger.h"

using namespace std;

#define MAX_BUFFER		128
#define DEFAULT_THREAD  4

void runServerThread(string threadName, int serverFd)
{
    logger::logInfo("runServerThread", "Odpalanie watka " + threadName);
    serverThread st1(threadName, serverFd);
}

thread * threads; 

int main ( int argc, char *argv[]) {
    int port, threadCount = 0;
    logger log();

    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Usage: %s <Server Port> <optional: Number of threads>\n", argv[0]);
        exit(1);
    }
    if ((port = atoi(argv[1])) == 0) {
        perror("Spodziewana liczba");
        return -1;
    };

    if (argc == 3 && (threadCount = atoi(argv[2])) == 0) {
        perror("Spodziewana liczba");
        return -1;
    }

    if(argc == 2) {
        threadCount = DEFAULT_THREAD;
    }

    //utworz polaczenie
    int serverFd;
    struct sockaddr_in servaddr;;

    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverFd < 0) {
        logger::logError("main", "Nie mozna otworzyc socketa!!!");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    int bindAns = bind(serverFd, (struct sockaddr *)&servaddr,
         sizeof(servaddr));

    if(bindAns < 0) {
         logger::logError("main", "Nie mozna zbiondowac!!!");
         exit(1);
    }

    //Odaplenie watkow do rozmawiania z klientem i czekanie na ich zakonczenie
    threads = new thread[threadCount];

    for(int i = 0; i < threadCount; i++ ) {
        threads[i] = thread(runServerThread, "thread (" + to_string(i) + ")", serverFd);
    }

    for(int i = 0; i < threadCount; i++ ) {
        threads[i].join();
    }
}

