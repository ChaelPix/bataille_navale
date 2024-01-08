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
#include <thread>
#include <future>
#include "SaveData.h"

class BsBDD {

private:
    sql::Driver* driver;
    sql::Connection* con;
    sql::PreparedStatement* pstmt;
    sql::ResultSet* res;
    std::string userId; 

    std::string mdp;
    std::string id;
    std::string score;
    std::string nbGames;
    std::string nbLostGames;
    std::string nbWonGames;
    std::string idPlayers;
    int idPicture;
    std::vector<std::string> vcase;
    SaveData objDataSave;
    bool isConnected;

public:
    BsBDD();
    ~BsBDD();

    void Connexion();
    void setPseudo(std::string name);
    bool connectToDB(const std::string& dbURI, const std::string& userName, const std::string& password, const std::string& bddShema);
    bool login(const std::string& idPlayer, const std::string& password);
    bool registerUser(const std::string& idUser, const std::string& password);
    void BonusWin(int nbPoints = 100);
    void incrementNbGames();
    void incrementNbLostGames();
    void incrementNbWonGames();
    void displayPlayerInfo();
    bool isConnect();
    void getPlayerData();
    void setAllData();
    void getAllData(std::vector<std::string>&Vector);
    void saveToText();
    std::string getStatsInfo();

    bool isUserExistsButWrongPassword(const std::string& idUser, const std::string& password);
    bool isUserDoesNotExist(const std::string& idUser);

    // Déclarations des méthodes getteurs
    std::string getId() const;
    std::string getScore() const;
    std::string getNbGames() const;
    std::string getNbLostGames() const;
    std::string getNbWonGames() const;
    std::string getIdPlayers() const;
    std::string getmdp() const;
    std::string getRatio();

    bool getIsConnected();
    void setIsConnected(bool action);
    
    int getIdPicture();
    void setIdPicture(int id);

    // Setters
    void setId(const std::string& newId);
    void setScore(const std::string& newScore);
    void setNbGames(const std::string& newNbGames);
    void setNbLostGames(const std::string& newNbLostGames);
    void setNbWonGames(const std::string& newNbWonGames);
    void setIdPlayers(const std::string& newIdPlayers);
    void setMdp(const std::string& newMdp);
};