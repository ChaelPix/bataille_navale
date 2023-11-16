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

    CoreGame jeu; // Création d'une instance de CoreGame
    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
    jeu.jouer(); // Lancer le jeu
    
    if (jeu.partiePerdu()) {
        std::cout << espace << "Vous avez perdu la partie." << std::endl;
    }
    else {
        std::cout << espace << "Félicitations ! Vous avez gagné !" << std::endl;
    }

    return 0;
}