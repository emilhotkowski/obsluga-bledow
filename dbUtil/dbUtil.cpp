#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>

#include <mysql/mysql.h>

#include "dbUtil.h"
#include "../logging/logger.h"

using namespace std;

dbUtil::dbUtil() {
    mysql_init(&mysql);
    mysql_real_connect(&mysql, "127.0.0.1", "root", "root", "projekt_wit", 0, NULL, 0);
}

dbUtil::~dbUtil() {
    mysql_close(&mysql);
}

int dbUtil::logUser(char* login, char* password) {
    logger::logInfo("logUser", "Logowanie uzytkownika do systemu");
    MYSQL_RES *idZapytania;
    MYSQL_ROW  wiersz;
    
    mysql_select_db(&mysql, "projekt_wit");

    stringstream strstr;
    strstr << "SELECT id FROM app_user WHERE user_name ='" << login << "' AND password = '" << password <<"'";

    mysql_query(&mysql, strstr.str().c_str() );
    idZapytania = mysql_store_result(&mysql);
    
    int ans = -1;
    while((wiersz = mysql_fetch_row(idZapytania)) != NULL)
    {
        for(int i = 0;i < mysql_num_fields(idZapytania); i++)
            ans = atoi(wiersz[i]);
    }

    logger::logInfo("logUser", "Wynik logowania " + to_string(ans));
    return ans;
}