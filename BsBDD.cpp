#include "BsBDD.h"

BsBDD::BsBDD() : userId("") {
    //connectToDB("tcp://10.187.52.4:3306", "batailleNavale", "batailleNavale");
    this->userId = "Guest";
    this->score = "0";
    this->nbGames = "0";
    this->nbLostGames = "0";
    this->nbWonGames = "0";
    this->idPlayers = "898989";
    this->idPicture = 32;
}

BsBDD::~BsBDD() {
    delete res;
    delete pstmt;
    delete con;
}

void BsBDD::Connexion() {
    std::string idUser, password;
    char choice;
    SautaLaLigne SautaLaLigne
    std::cout << espace<< "Bienvenue dans le jeu de bataille navale!\n";
    std::cout << espace << "Voulez-vous (C)onnexion ou (I)nscription? [C/I]: ";
    std::cin >> choice;

    if (choice == 'C' || choice == 'c') {
        std::cout << espace << "Entrez votre identifiant utilisateur: ";
        std::cin >> idUser;
        std::cout << espace << "Entrez votre mot de passe: ";
        std::cin >> password;

        if (login(idUser, password)) {
            std::cout << espace << "Connexion r\202ussie!\n";
            setPseudo(idUser);
        }
        else {
            std::cout << espace << "Identifiant ou mot de passe incorrect.\n";
        }
    }
    else if (choice == 'I' || choice == 'i') {
        std::cout << espace << "Choisissez un identifiant utilisateur: ";
        std::cin >> idUser;
        std::cout << espace << "Choisissez un mot de passe: ";
        std::cin >> password;

        if (registerUser(idUser, password)) {
            std::cout << espace << "Inscription r\202ussie! Vous êtes maintenant connect\202.\n";
        }
        else {
            std::cout << espace << "Erreur lors de l'inscription ou l'identifiant existe d\202jà.\n";
        }
    }
}

void BsBDD::setPseudo(std::string name) {
    this->userId = name;
}

#include <thread>
#include <future>

bool BsBDD::connectToDB(const std::string& dbURI, const std::string& userName, const std::string& password) {
    std::promise<bool> connectPromise;
    auto connectFuture = connectPromise.get_future();

    std::thread connectThread([&]() {
        try {
            driver = get_driver_instance();
            con = driver->connect(dbURI, userName, password);
            con->setSchema("batailleNavale_b");
            connectPromise.set_value(true);
        }
        catch (sql::SQLException& e) {
            std::cerr << "Can't connect to bdd : " << e.what() << std::endl;
            connectPromise.set_value(false);
        }
    });

    if (connectFuture.wait_for(std::chrono::seconds(2)) == std::future_status::timeout) {
        connectThread.detach(); 
        return false;
    }

    connectThread.join(); 
    return connectFuture.get();
}



bool BsBDD::login(const std::string& idUser, const std::string& password) {
    try {
        pstmt = con->prepareStatement("SELECT mdp FROM player WHERE idPlayers = ? AND mdp = ?");
        pstmt->setString(1, idUser);
        pstmt->setString(2, password);
        res = pstmt->executeQuery();

        if (res->next()) {
            this->mdp = res->getString("mdp");
            std::cout << "IIIIIIIII " << mdp << " IIIIIIIII ";

            // Plus besoin de vérifier à nouveau avec res->next()

            this->userId = idUser; // Définir l'userId pour l'utilisateur connecté

            pstmt = con->prepareStatement("SELECT * FROM playersData WHERE idPlayers = ?");
            pstmt->setString(1, userId);
            res = pstmt->executeQuery();

            if (res->next()) {
                // Mise à jour des attributs
                this->id = std::to_string(res->getInt("id"));
                this->score = std::to_string(res->getInt("score"));
                this->nbGames = std::to_string(res->getInt("nbGames"));
                this->nbLostGames = std::to_string(res->getInt("nbLostGames"));
                this->nbWonGames = std::to_string(res->getInt("nbWonGames"));
                // this->idPlayers = std::to_string(res->getInt("idPlayers")); // Supprimé car idPlayers est une chaîne, pas un entier
                setAllData();
            }
            return true;
        }
        else {
            return false;
        }
    }
    catch (sql::SQLException& e) {
        // Gérer l'exception
    }
}

bool BsBDD::isUserExistsButWrongPassword(const std::string& idUser, const std::string& password) {

    pstmt = con->prepareStatement("SELECT mdp FROM player WHERE idPlayers = ?");
    pstmt->setString(1, idUser);
    res = pstmt->executeQuery();

    if (res->next()) {
        std::string dbPassword = res->getString("mdp");
        return dbPassword != password;
    }
    return false; 
}

bool BsBDD::isUserDoesNotExist(const std::string& idUser) {

    pstmt = con->prepareStatement("SELECT mdp FROM player WHERE idPlayers = ?");
    pstmt->setString(1, idUser);
    res = pstmt->executeQuery();

    return !res->next(); 
}


bool BsBDD::registerUser(const std::string& idUser, const std::string& password) {
    std::cout << espace << "debug" << std::endl;
    try {
        std::cout << espace << "debug2" << std::endl;

        pstmt = con->prepareStatement("SELECT idPlayers FROM player WHERE idPlayers = ?");
        pstmt->setString(1, idUser);
        res = pstmt->executeQuery();

        if (res->next()) {
            return false; // L'identifiant utilisateur existe déjà
        }

        pstmt = con->prepareStatement("INSERT INTO player (idPlayers, mdp) VALUES (?, ?)");
        pstmt->setString(1, idUser);
        pstmt->setString(2, password);
        pstmt->executeUpdate();

        // Pas besoin de récupérer l'ID du nouvel utilisateur car il est déjà connu (idUser)
        //userId = idUser;

        pstmt = con->prepareStatement("INSERT INTO playersData (score, nbGames, nbLostGames, nbWonGames, idPlayers) VALUES (0, 0, 0, 0, ?)");
        pstmt->setString(1, idUser);
        pstmt->executeUpdate();
        this->userId = idUser; // Définir l'userId pour l'utilisateur connecté
        std::cout << espace << "debug3" << std::endl;

        return true;
    }
    catch (sql::SQLException& e) {
        // Gérer l'exception
    }
    return false;
}

void BsBDD::BonusWin(int nbPoints) {

    if (!isConnected) {
        std::cout << espace << "Aucun utilisateur connect\202." << std::endl;
        return;
    }

    try {
        pstmt = con->prepareStatement("UPDATE playersData SET score = score + " + std::to_string(nbPoints) + " WHERE idPlayers = ? ");
        pstmt->setString(1, userId);
        pstmt->executeUpdate();

        std::cout << espace << "Bonus appliqu\202 avec succ\202s pour l'utilisateur " << userId << "." << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << espace << "Erreur lors de la mise à jour du score: " << e.what() << std::endl;
    }
}


void BsBDD::incrementNbGames() {
    if (!isConnected) {
        std::cout << espace << "Aucun utilisateur connect\202." << std::endl;
        return;
    }

    try {
        pstmt = con->prepareStatement("UPDATE playersData SET nbGames = nbGames + 1 WHERE idPlayers = ?");
        pstmt->setString(1, userId);
        pstmt->executeUpdate();

        std::cout << espace << "Nombre de jeux jou\202s mis à jour pour l'utilisateur " << userId << "." << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << espace << "Erreur lors de la mise à jour du nombre de jeux jou\202s: " << e.what() << std::endl;
    }
}

void BsBDD::incrementNbLostGames() {
    if (!isConnected) {
        std::cout << espace << "Aucun utilisateur connect\202." << std::endl;
        return;
    }

    try {
        pstmt = con->prepareStatement("UPDATE playersData SET nbLostGames = nbLostGames + 1 WHERE idPlayers = ?");
        pstmt->setString(1, userId);
        pstmt->executeUpdate();

        std::cout << espace << "Nombre de parties perdues mis à jour pour l'utilisateur " << userId << "." << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << espace << "Erreur lors de la mise à jour du nombre de parties perdues: " << e.what() << std::endl;
    }
}

void BsBDD::incrementNbWonGames() {
    if (!isConnected) {
        std::cout << espace << "Aucun utilisateur connect\202." << std::endl;
        return;
    }

    try {
        pstmt = con->prepareStatement("UPDATE playersData SET nbWonGames = nbWonGames + 1 WHERE idPlayers = ?");
        pstmt->setString(1, userId);
        pstmt->executeUpdate();

        std::cout << espace << "Nombre de parties gagn\202es mis à jour pour l'utilisateur " << userId << "." << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << espace << "Erreur lors de la mise à jour du nombre de parties gagn\202es: " << e.what() << std::endl;
    }
}

void BsBDD::displayPlayerInfo() {

    if (!isConnected) {
        std::cout << espace << "Aucun utilisateur connecté." << std::endl;
        return;
    }

    try {
        // Requête pour récupérer les données de l'utilisateur
        pstmt = con->prepareStatement("SELECT * FROM playersData WHERE idPlayers = ?");
        pstmt->setString(1, userId);
        res = pstmt->executeQuery();

        if (res->next()) {
            std::cout << espace << "Informations de l'utilisateur " << userId << ":" << std::endl;
            std::cout << espace << "Score: " << res->getInt("score") << std::endl;
            std::cout << espace << "Nombre de jeux jou\202s: " << res->getInt("nbGames") << std::endl;
            std::cout << espace << "Nombre de jeux perdus: " << res->getInt("nbLostGames") << std::endl;
            std::cout << espace << "Nombre de jeux gagn\202s: " << res->getInt("nbWonGames") << std::endl;
            // Mise à jour des attributs
            this->id = std::to_string(res->getInt("id"));
            this->score = std::to_string(res->getInt("score"));
            this->nbGames = std::to_string(res->getInt("nbGames"));
            this->nbLostGames = std::to_string(res->getInt("nbLostGames"));
            this->nbWonGames = std::to_string(res->getInt("nbWonGames"));
            this->idPlayers = std::to_string(res->getInt("idPlayers"));
        }
        else {
            std::cout << espace << "Aucune information trouv\202e pour l'utilisateur " << userId << "." << std::endl;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << espace << "Erreur lors de la r\202cup\202ration des informations de l'utilisateur: " << e.what() << std::endl;
    }
}

bool BsBDD::isConnect() {

    if (this->userId.empty()) {
        std::cout << espace << "Aucun utilisateur connect\202. r\202essayez" << std::endl;
        return false;
    }
    return true;
}

void BsBDD::setAllData(){
    vcase.push_back(this->id);   
    vcase.push_back(this->score);
    vcase.push_back(this->nbGames);
    vcase.push_back(this->nbLostGames);
    vcase.push_back(this->nbWonGames);
    vcase.push_back(this->idPlayers);
    vcase.push_back(std::to_string(this->idPicture));
}

void BsBDD::getAllData(std::vector<std::string>& Vector){
    
    Vector.clear();
    Vector.push_back(this->userId + "$");
    Vector.push_back(this->mdp + "$");
    Vector.push_back(std::to_string(this->idPicture));

    //for (int i = 0; i < vcase.size(); i++){ //incrémenter toute les valeurs
    //    Vector.push_back(this->vcase.at(i) + "$");
    //}
}

void BsBDD::saveToText() {
    std::vector<std::string> vectorData;
    getAllData(vectorData);
    objDataSave.saveDataToFile(vectorData, "Data.txt", true);

}

std::string BsBDD::getStatsInfo()
{

    float Win = std::stoi(nbWonGames);
    float loss = std::stoi(nbLostGames);

    double kdRatio = Win / loss;
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << kdRatio;
    std::string kdRatioString = stream.str();

    std::string statInfo = "";
    //statInfo += "Welcome " + userId + "\n";

    statInfo += "Victories: " + nbWonGames + "\n";
    statInfo += "Defeat: " + nbLostGames + "\n";
    if (loss > 0) {
        statInfo += "K/D: " + kdRatioString + "\n";
    }
    return statInfo;
}

#pragma region Getter/Setter
std::string BsBDD::getId() const {
    return id;
}

std::string BsBDD::getScore() const {
    return score;
}

std::string BsBDD::getNbGames() const {
    return nbGames;
}

std::string BsBDD::getNbLostGames() const {
    return nbLostGames;
}

std::string BsBDD::getNbWonGames() const {
    return nbWonGames;
}

std::string BsBDD::getIdPlayers() const {
    return userId;
}

std::string BsBDD::getmdp() const {
    return mdp;
}

std::string BsBDD::getRatio() {
    float win = std::stoi(nbWonGames);
    float defeats = std::stoi(nbLostGames);

    float kdRatio = win;
    if(defeats != 0)
        kdRatio = win / defeats;

    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << kdRatio;
    std::string kdRatioString = stream.str();

    std::string statInfo = "";

    return kdRatioString;
}

bool BsBDD::getIsConnected()
{
    return isConnected;
}

void BsBDD::setIsConnected(bool action)
{
    isConnected = action;
}
int BsBDD::getIdPicture() {
    return this->idPicture;
}

//setteur
void BsBDD::setIdPicture(int id) {
    this->idPicture = id;
}
void BsBDD::setId(const std::string& newId) {
    this->id = newId;
}
void BsBDD::setScore(const std::string& newScore) {
    this->score = newScore;
}
void BsBDD::setNbGames(const std::string& newNbGames) {
    this->nbGames = newNbGames;
}
void BsBDD::setNbLostGames(const std::string& newNbLostGames) {
    this->nbLostGames = newNbLostGames;
}
void BsBDD::setNbWonGames(const std::string& newNbWonGames) {
    this->nbWonGames = newNbWonGames;
}
void BsBDD::setIdPlayers(const std::string& newIdPlayers) {
    this->userId = newIdPlayers;
}
void BsBDD::setMdp(const std::string& newMdp) {
    this->mdp = newMdp;
}

#pragma endregion