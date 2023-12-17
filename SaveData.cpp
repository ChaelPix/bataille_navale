#include "SaveData.h"

namespace fs = std::filesystem;

void SaveData::saveDataToFile(const std::vector<std::string>& dataVector, bool flag) {
    char* userProfile = nullptr;
    size_t userProfileSize = 0;
    errno_t err = _dupenv_s(&userProfile, &userProfileSize, "USERPROFILE");

    if (err) {
        std::cerr << "Erreur en obtenant le chemin USERPROFILE" << std::endl;
        return;
    }

    fs::path documentsPath = fs::path(userProfile) / "Documents" / "Valiant";
    fs::create_directories(documentsPath); // Crée les dossiers si nécessaire
    fs::path filePath = documentsPath / "data.txt";

    free(userProfile); // Libérer la mémoire allouée par _dupenv_s

    std::ofstream file(filePath);
    if (file.is_open()) {
        for (const auto& data : dataVector) {
            file << data << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Impossible d'ouvrir le fichier pour l'écriture." << std::endl;
    }
}

std::vector<std::string> SaveData::loadDataFromFile() {
    char* userProfile = nullptr;
    size_t userProfileSize = 0;
    errno_t err = _dupenv_s(&userProfile, &userProfileSize, "USERPROFILE");

    if (err) {
        std::cerr << "Erreur en obtenant le chemin USERPROFILE" << std::endl;
        return std::vector<std::string>();
    }

    fs::path documentsPath = fs::path(userProfile) / "Documents" / "Valiant";
    fs::path filePath = documentsPath / "data.txt";

    free(userProfile); // Libérer la mémoire allouée par _dupenv_s

    std::vector<std::string> loginsAndPasswordsAndIdPicture;
    std::ifstream file(filePath);
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
        loginsAndPasswordsAndIdPicture.assign(3, "");
    }

    return loginsAndPasswordsAndIdPicture;
}
