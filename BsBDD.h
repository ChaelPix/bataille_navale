#pragma once
#include <utility>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
#include "CoreGame.h"
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>

class BsBDD {

private:
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;
    std::string userId; 

public:
    BsBDD();
    ~BsBDD();

    void Connexion();
    void connectToDB(const std::string& dbURI, const std::string& userName, const std::string& password);
    bool login(const std::string& idPlayer, const std::string& password);
    bool registerUser(const std::string& idUser, const std::string& password);
    void loadPlayerData();
    void savePlayerData();
    void BonusWin();
};