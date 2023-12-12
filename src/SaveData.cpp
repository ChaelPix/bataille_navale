#include "SaveData.h"

void SaveData::saveDataToFile(const std::vector<std::string>& dataVector, const std::string& filename, bool flag) {
    
    if (flag) {
        std::vector<std::string> adjustedDataVector = dataVector;
        if (adjustedDataVector.size() > 2) {
            adjustedDataVector.pop_back();
        }
    }

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
    std::vector<std::string> loginsAndPasswordsAndIdPicture;
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::size_t firstSeparatorPos = line.find('$');
            std::size_t secondSeparatorPos = line.rfind('$');

            std::string login = line.substr(0, firstSeparatorPos);
            std::string password = line.substr(firstSeparatorPos + 1, secondSeparatorPos - firstSeparatorPos - 1);
            std::string idPicture = line.substr(secondSeparatorPos + 1);

            loginsAndPasswordsAndIdPicture.push_back(login);
            loginsAndPasswordsAndIdPicture.push_back(password);
            loginsAndPasswordsAndIdPicture.push_back(idPicture);
        }
        file.close();
    }
    else {
        std::cerr << "Impossible d'ouvrir le fichier pour la lecture." << std::endl;
        loginsAndPasswordsAndIdPicture.assign(3, ""); // Remplit avec trois chaînes vides
    }

    return loginsAndPasswordsAndIdPicture;
}
