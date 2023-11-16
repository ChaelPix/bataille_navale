#include "Localization.h"

Localization::Localization(const std::string& language = "")
{
    if (language != "")
        init(language);
}

void Localization::init(const std::string& language)
{
    loadLanguageFile(language);
}

void Localization::loadLanguageFile(const std::string& language) {
    std::ifstream file("localization/" + language + ".json");
    nlohmann::json j;
    file >> j;

    for (auto& element : j.items()) {
        translations[element.key()] = element.value();
    }

}

std::string Localization::getString(const std::string& key) {
    auto it = translations.find(key);

    if (it != translations.end()) 
        return it->second;
    else 
        return "Invalid Key: " + key;
    
}