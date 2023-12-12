#include <iostream>
#include <string>
#include <filesystem>
#include <regex>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem; 

int rename() {

    std::string path = "C:/Users/traia/OneDrive/Documents/GitHub/cours-bts-2nd-annee/bataillenavale/ressources/UI/Backgrounds/waterBg";
    std::regex pattern("Layer (\\d+)\\.jpg");
    std::smatch match;
    std::vector<std::pair<int, fs::path>> files;


    for (const auto& entry : fs::directory_iterator(path)) {
        const std::string filename = entry.path().filename().string();

        if (std::regex_match(filename, match, pattern)) {
            int number = std::stoi(match[1].str());
            files.emplace_back(number, entry.path());
        }
    }


    std::sort(files.begin(), files.end());


    int counter = 1;
    for (const auto& file : files) {
        std::string new_name = "water_" + std::to_string(counter++) + ".jpg";
        fs::rename(file.second, file.second.parent_path() / new_name);
    }


    return 0;
}