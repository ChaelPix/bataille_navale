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
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>
#include <iomanip>


class BsBDD {

private:
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;
    std::string userId; 

    std::string id;
    std::string score;
    std::string nbGames;
    std::string nbLostGames;
    std::string nbWonGames;
    std::string idPlayers;

public:
    BsBDD();
    ~BsBDD();

    void Connexion();
    void setPseudo(std::string name);
    void connectToDB(const std::string& dbURI, const std::string& userName, const std::string& password);
    bool login(const std::string& idPlayer, const std::string& password);
    bool registerUser(const std::string& idUser, const std::string& password);
    void BonusWin();
    void incrementNbGames();
    void incrementNbLostGames();
    void incrementNbWonGames();
    void displayPlayerInfo();
    bool isConnect();
    void getPlayerData();
    std::string getStatsInfo();

    // Déclarations des méthodes getteurs
    std::string getId() const;
    std::string getScore() const;
    std::string getNbGames() const;
    std::string getNbLostGames() const;
    std::string getNbWonGames() const;
    std::string getIdPlayers() const;
};