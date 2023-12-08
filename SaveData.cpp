#include "SaveData.h"

void SaveData::saveDataToFile(const std::vector<std::string>& dataVector, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& data : dataVector) {
            file << data; // Écrit chaque élément dans le fichier avec un saut de ligne
        }
        file.close();
    }
    else {
        // Gestion de l'erreur si le fichier ne peut pas être ouvert
        std::cerr << "Impossible d'ouvrir le fichier pour l'écriture." << std::endl;
    }
}


std::vector<std::string> SaveData::loadDataFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> loginsAndPasswords;
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::size_t separatorPos = line.find('$');
            std::string login = line.substr(0, separatorPos);
            std::string password = (separatorPos != std::string::npos && separatorPos + 1 < line.size()) ? line.substr(separatorPos + 1) : "Pas de mot de passe";
            loginsAndPasswords.push_back(login);
            loginsAndPasswords.push_back(password);
        }
        file.close();
    }
    else {
        // Gestion de l'erreur si le fichier ne peut pas être ouvert
        std::cerr << "Impossible d'ouvrir le fichier pour la lecture." << std::endl;
    }

    return loginsAndPasswords;
}