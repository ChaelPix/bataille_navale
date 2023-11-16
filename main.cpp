#include <SFML/Graphics.hpp>
#include <iostream>
#include "Localization.h"
#include "CoreGame.h"

int main()
{
    Localization l("fr");
    std::cout << l.getString("titre du jeu") << std::endl;
    Localization l2("eng");
    std::cout << l2.getString("titre du jeu") << std::endl;

    CoreGame jeu; // Création d'une instance de CoreGame

    jeu.placerBateaux(); // Placer les bateaux pour le joueur et l'IA
    jeu.jouer(); // Lancer le jeu

    if (jeu.partiePerdu()) {
        std::cout << "Vous avez perdu la partie." << std::endl;
    }
    else {
        std::cout << "Félicitations ! Vous avez gagné !" << std::endl;
    }

    return 0;
}