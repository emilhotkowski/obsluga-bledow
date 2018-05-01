#ifndef TCP_UTIL_H
#define TCP_UTIL_H

#include <cstdlib>
#include <iostream>
#include <string>
 
using namespace std;

class tcpUtil {
    private:
        int connectionFd;
    public:
        tcpUtil(int connectionFd);

        int readBytes(char* buffer);
        void sendData(char* buffer);
        void sendPositiveMessage();
        void sendNegativeMessage();
        void simpleSendData(char* buffer);
};

#endif