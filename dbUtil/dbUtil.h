#ifndef DB_UTIL_H
#define DB_UTIL_H

#include <cstdlib>
#include <iostream>
#include <string>

#include <mysql/mysql.h>

using namespace std;

class dbUtil {
    private:
        MYSQL mysql;
    public:
        dbUtil();
        ~dbUtil();
        int logUser(char* login, char* password);
};

#endif