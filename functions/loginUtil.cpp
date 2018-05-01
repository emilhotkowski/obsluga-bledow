#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "loginUtil.h"
#include "../tcpUtil/tcpUtil.h"
#include "../dbUtil/dbUtil.h"
#include "../logging/logger.h"

#define MAX_BUFFER     128

loginUtil::loginUtil(int connectionFd, tcpUtil* tcp) {
    this->connectionFd = connectionFd;
    this->tcp = tcp;
}   

void loginUtil::loginClient() {
    
    //Wyslij informacje ze czekasz na dane
    tcp->sendPositiveMessage();

    char login[MAX_BUFFER];
    char password[MAX_BUFFER];

    if(tcp->readBytes(login) <= 0) {
        tcp->sendNegativeMessage();
        logger::logError("loginClient", "Niepoprawne wczytanie loginu");
        return;
    } else {
        tcp->sendPositiveMessage();
        logger::logInfo("loginClient", "Login odczytano poprawnie");
    }

    if(tcp->readBytes(password) <= 0) {
        logger::logError("loginClient", "Niepoprawne wczytanie hasla");
        tcp->sendNegativeMessage();
        return;
    } else {
        logger::logInfo("loginClient", "Haslo odczytano poprawnie");
        tcp->sendPositiveMessage();
    }

    dbUtil db;

    if(db.logUser(login, password) >= 0) {
        logger::logInfo("loginClient", "Zalogowano uzytkownika");
        tcp->sendPositiveMessage();
    } else {
        logger::logInfo("loginClient", "Niepoprawne dane logowania!!! Brak dostepu");
        tcp->sendNegativeMessage();
    }
}