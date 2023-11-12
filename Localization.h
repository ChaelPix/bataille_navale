#pragma once

#include <SFML/Graphics.hpp>
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>
#include <unordered_map>

class Localization {

private:
    /**
     * @brief Contient les traductions de textes charg�es � partir des fichiers JSON.
     * La cl� repr�sente l'identifiant du texte et la valeur est le texte traduit.
     */
    std::unordered_map<std::string, std::string> translations;

public:
    /**
     * @brief Constructeur de la classe Localization.
     * Initialise la map de traductions en chargeant les donn�es depuis un fichier JSON sp�cifique � la langue.
     *
     * @param language La langue pour laquelle charger les traductions (ex: "fr", "en").
     */
    Localization(const std::string& language);

    /**
     * @brief R�cup�re une cha�ne de caract�res traduite correspondant � la cl� donn�e.
     *
     * @param key La cl� identifiant le texte � r�cup�rer.
     * @return std::string Le texte traduit si la cl� est trouv�e, sinon un message d'erreur.
     */
    std::string getString(const std::string& key);

private:

    /**
     * @brief Charge les donn�es de traduction � partir d'un fichier JSON.
     * Lit le fichier JSON correspondant � la langue sp�cifi�e et remplit la map 'translations'.
     *
     * @param language La langue pour laquelle le fichier JSON doit �tre charg�.
     */
    void loadLanguageFile(const std::string& language);

};
