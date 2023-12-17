#include "SaveData.h"

void SaveData::saveDataToFile(const std::vector<std::string>& dataVector, bool flag) {

    if (flag) {
        std::vector<std::string> adjustedDataVector = dataVector;
        if (adjustedDataVector.size() > 2) {
            adjustedDataVector.pop_back();
        }
    }

    std::ofstream file("data.txt");
    if (file.is_open()) {
        for (const auto& data : dataVector) {
            file << data; // �crit chaque �l�ment dans le fichier avec un saut de ligne
        }
        file.close();
    }
    else {
        // Gestion de l'erreur si le fichier ne peut pas �tre ouvert
    }
}


std::vector<std::string> SaveData::loadDataFromFile() {
    std::ifstream file("data.txt");
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
        loginsAndPasswordsAndIdPicture.assign(3, ""); // Remplit avec trois cha�nes vides
    }

    return loginsAndPasswordsAndIdPicture;
}