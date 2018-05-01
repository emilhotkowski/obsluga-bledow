#ifndef LOGIN_UTIL_H
#define LOGIN_UTIL_H

#include <cstdlib>
#include <iostream>
#include <string>

#include "../tcpUtil/tcpUtil.h"
 
using namespace std;

class loginUtil {
    private:
        int connectionFd;
        tcpUtil* tcp;
    public:
        loginUtil(int connectionFd, tcpUtil* tcp);
        void loginClient();
};

#endif