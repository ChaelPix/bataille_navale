#include "SaveData.h"

void SaveData::saveDataIntoFile(std::vector<std::string>& VData){
    // Données à sauvegarder
    std::string data = "Score: 100\nPlayerName: Player1";

    // Création d'un objet ofstream pour écrire dans un fichier
    std::ofstream file("savefile.txt");

    // Vérifier si le fichier est ouvert correctement
    if (file.is_open()) {
        // Écriture des données dans le fichier
        file << data;

        // Fermeture du fichier
        file.close();
    }
    else {
        std::cerr << "Impossible d'ouvrir le fichier pour l'écriture." << std::endl;
    }
}
