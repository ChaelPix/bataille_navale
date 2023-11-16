#include <SFML/Graphics.hpp>
#include <iostream>
#include "Localization.h"
#include "CoreGame.h"

#define espace "\t\t\t\t\t\t"

int main()
{

    //Localization l("fr");
    //std::cout << l.getString("titre du jeu") << std::endl;
    //Localization l2("eng");
    //std::cout << l2.getString("titre du jeu") << std::endl;

    CoreGame jeu; // Cr\202ation d'une instance de CoreGame
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
    jeu.jouer(); // Lancer le jeu
    
    if (jeu.partiePerdu()) {
        std::cout << espace << "Vous avez perdu la partie." << std::endl;
    }
    else {
        std::cout << espace << "F\202licitations ! Vous avez gagn\202 !" << std::endl;
    }

    return 0;
}