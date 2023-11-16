#pragma once

#include <SFML/Graphics.hpp>
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <unordered_map>

class Localization {

private:
    /**
     * @brief Contains text translations loaded from JSON files.
     * The key represents the text identifier, and the value is the translated text.
     */
    std::unordered_map<std::string, std::string> translations;

public:
    /**
     * @brief Constructor of the Localization class.
     * Initializes the translations map by loading data from a language-specific JSON file.
     *
     * @param language The language for which to load the translations (e.g., "fr", "en"). If "", then do not initialize.
     */
    Localization(const std::string& language = "");

    /**
    * Initializes translations by reading the JSON associated with the name.
    */
    void init(const std::string& language);

    /**
     * @brief Retrieves a translated string corresponding to the given key.
     *
     * @param key The key identifying the text to retrieve.
     * @return std::string The translated text if the key is found, otherwise an error message.
     */
    std::string getString(const std::string& key);

private:

    /**
     * @brief Loads translation data from a JSON file.
     * Reads the JSON file corresponding to the specified language and fills the 'translations' map.
     *
     * @param language The language for which the JSON file should be loaded.
     */
    void loadLanguageFile(const std::string& language);

};
