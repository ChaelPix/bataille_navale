#pragma once

#include <SFML/Graphics.hpp>
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <unordered_map>

class Localization {

private:
    /**
     * @brief Contient les traductions de textes chargées à partir des fichiers JSON.
     * La clé représente l'identifiant du texte et la valeur est le texte traduit.
     */
    std::unordered_map<std::string, std::string> translations;

public:
    /**
     * @brief Constructeur de la classe Localization.
     * Initialise la map de traductions en chargeant les données depuis un fichier JSON spécifique à la langue.
     *
     * @param language La langue pour laquelle charger les traductions (ex: "fr", "en").
     */
    Localization(const std::string& language);

    /**
     * @brief Récupère une chaîne de caractères traduite correspondant à la clé donnée.
     *
     * @param key La clé identifiant le texte à récupérer.
     * @return std::string Le texte traduit si la clé est trouvée, sinon un message d'erreur.
     */
    std::string getString(const std::string& key);

private:

    /**
     * @brief Charge les données de traduction à partir d'un fichier JSON.
     * Lit le fichier JSON correspondant à la langue spécifiée et remplit la map 'translations'.
     *
     * @param language La langue pour laquelle le fichier JSON doit être chargé.
     */
    void loadLanguageFile(const std::string& language);

};
