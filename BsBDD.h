#pragma once
#define SautaLaLigne std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
#define espace "\t\t\t\t\t"
#define espace2 "\t\t\t\t\t\t      "
#define espace3 "\t\t\t\t\t\t   "
#define espace4 "\t\t\t\t\t\t         "
#define espace5 "\t\t\t\t\t\t      "
#define effacer system("cls");
#include <utility>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
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
    void setPseudo(std::string name);
    void connectToDB(const std::string& dbURI, const std::string& userName, const std::string& password);
    bool login(const std::string& idPlayer, const std::string& password);
    bool registerUser(const std::string& idUser, const std::string& password);
    void loadPlayerData();
    void savePlayerData();
    void BonusWin();
    void incrementNbGames();
    void incrementNbLostGames();
    void incrementNbWonGames();
    void displayPlayerInfo();


};