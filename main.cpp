#include <SFML/Graphics.hpp>
#include <iostream>
#include "Localization.h"
#include "CoreGame.h"

int main()
{
    //Localization l("fr");
    //std::cout << l.getString("titre du jeu") << std::endl;
    //Localization l2("eng");
    //std::cout << l2.getString("titre du jeu") << std::endl;
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Réinitialiser le générateur de nombres aléatoires (a garder dans le main, car si le programme est exécuté plusieurs fois en peu de temps, std::time(nullptr) pourrait retourner la même valeur, ce qui entraîne la création des mêmes séquences de nombres aléatoires et donc des mêmes positions de bateaux.
    SautaLaLigne
    CoreGame jeu; 
    jeu.jouer(); //boucle du jeu

    if (jeu.partiePerdu()) {
        std::cout << espace << "Vous avez perdu la partie." << std::endl;
    }
    else {
        std::cout << espace << "F\202licitations ! Vous avez gagn\202 !" << std::endl;
    }

    return 0;
}

