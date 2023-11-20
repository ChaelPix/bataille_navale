#include "BsBDD.h"

BsBDD::BsBDD() : userId("") {
    connectToDB("tcp://10.187.52.4:3306", "batailleNavale", "batailleNavale");
}

BsBDD::~BsBDD() {
    delete res;
    delete pstmt;
    delete con;
}

void BsBDD::Connexion() {
    std::string idUser, password;
    char choice;

    std::cout << "Bienvenue dans le jeu de bataille navale!\n";
    std::cout << "Voulez-vous (C)onnexion ou (I)nscription? [C/I]: ";
    std::cin >> choice;

    if (choice == 'C' || choice == 'c') {
        std::cout << "Entrez votre identifiant utilisateur: ";
        std::cin >> idUser;
        std::cout << "Entrez votre mot de passe: ";
        std::cin >> password;

        std::cout << "Utilisateur connect� : " << userId << std::endl;
        if (login(idUser, password)) {
            std::cout << "Connexion r�ussie!\n";
            loadPlayerData();
        }
        else {
            std::cout << "Identifiant ou mot de passe incorrect.\n";
        }
    }
    else if (choice == 'I' || choice == 'i') {
        std::cout << "Choisissez un identifiant utilisateur: ";
        std::cin >> idUser;
        std::cout << "Choisissez un mot de passe: ";
        std::cin >> password;

        if (registerUser(idUser, password)) {
            std::cout << "Inscription r�ussie! Vous �tes maintenant connect�.\n";
            loadPlayerData();
        }
        else {
            std::cout << "Erreur lors de l'inscription ou l'identifiant existe d�j�.\n";
        }
    }
}

void BsBDD::connectToDB(const std::string& dbURI, const std::string& userName, const std::string& password) {
    driver = get_driver_instance();
    con = driver->connect(dbURI, userName, password);
    con->setSchema("batailleNavale_b");
}

bool BsBDD::login(const std::string& idUser, const std::string& password) {
    try {
        pstmt = con->prepareStatement("SELECT idPlayers FROM player WHERE idPlayers = ? AND mdp = ?");
        pstmt->setString(1, idUser);
        pstmt->setString(2, password);
        res = pstmt->executeQuery();

        if (res->next()) {
            this->userId = idUser; // D�finir l'userId pour l'utilisateur connect�
            loadPlayerData();
            return true;
        }
        else {
            return false;
        }
    }
    catch (sql::SQLException& e) {
        // G�rer l'exception
    }
}


bool BsBDD::registerUser(const std::string& idUser, const std::string& password) {
    try {
        pstmt = con->prepareStatement("SELECT idPlayers FROM player WHERE idPlayers = ?");
        pstmt->setString(1, idUser);
        res = pstmt->executeQuery();

        if (res->next()) {
            return false; // L'identifiant utilisateur existe d�j�
        }

        pstmt = con->prepareStatement("INSERT INTO player (idPlayers, mdp) VALUES (?, ?)");
        pstmt->setString(1, idUser);
        pstmt->setString(2, password);
        pstmt->executeUpdate();

        // Pas besoin de r�cup�rer l'ID du nouvel utilisateur car il est d�j� connu (idUser)
        //userId = idUser;

        pstmt = con->prepareStatement("INSERT INTO playersData (score, nbGames, nbLostGames, nbWonGames, idPlayers) VALUES (0, 0, 0, 0, ?)");
        pstmt->setString(1, idUser);
        pstmt->executeUpdate();

        loadPlayerData();
        return true;
    }
    catch (sql::SQLException& e) {
        // G�rer l'exception
    }
    return false;
}

void BsBDD::loadPlayerData() {
    // Charger les donn�es du joueur depuis la base de donn�es
}

void BsBDD::savePlayerData() {
    // Sauvegarder les donn�es du joueur dans la base de donn�es
}

void BsBDD::BonusWin() {
    std::cout << "Utilisateur connect� : " << this->userId << std::endl;

    if (userId.empty()) {
        std::cout << "Aucun utilisateur connect�." << std::endl;
        return;
    }

    try {
        // Mise � jour du score dans la table 'playersData'
        pstmt = con->prepareStatement("UPDATE playersData SET score = score + 100 WHERE idPlayers = ?");
        pstmt->setString(1, userId);
        pstmt->executeUpdate();

        std::cout << "Bonus appliqu� avec succ�s pour l'utilisateur " << userId << "." << std::endl;
    }
    catch (sql::SQLException& e) {
        std::cerr << "Erreur lors de la mise � jour du score: " << e.what() << std::endl;
    }
}
