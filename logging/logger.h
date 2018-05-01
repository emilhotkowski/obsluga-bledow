#ifndef LOGGER_H
#define LOGGER_H

#include <cstdlib>
#include <iostream>
#include <string>
 
using namespace std;

class logger {
    private:
        
    public:
        logger();
        static void logInfo(string name, string message);
        static void logError(string name, string message);
};

#endif