#include "SaveData.h"

void SaveData::saveDataIntoFile(std::vector<std::string>& VData){
    // Donn�es � sauvegarder
    std::string data = "Score: 100\nPlayerName: Player1";

    // Cr�ation d'un objet ofstream pour �crire dans un fichier
    std::ofstream file("savefile.txt");

    // V�rifier si le fichier est ouvert correctement
    if (file.is_open()) {
        // �criture des donn�es dans le fichier
        file << data;

        // Fermeture du fichier
        file.close();
    }
    else {
        std::cerr << "Impossible d'ouvrir le fichier pour l'�criture." << std::endl;
    }
}
