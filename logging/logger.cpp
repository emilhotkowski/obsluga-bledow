#include <cstdlib>
#include <iostream>
#include <string>

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <syslog.h>

#include "logger.h"

logger::logger() {
    openlog("projekt_wit", 0, LOG_LOCAL0);
}

void logger::logInfo(string name, string message) {
    syslog(LOG_INFO, "%s: %s", name.c_str(), message.c_str());
}

void logger::logError(string name, string message) {
    syslog(LOG_ERR, "%s: %s", name.c_str(), message.c_str());
}

