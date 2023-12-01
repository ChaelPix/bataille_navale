#include <SFML/Graphics.hpp>
#include <iostream>
#include "Localization.h"
#include "CoreGame.h"
#include "BsBDD.h"
#include "TCPClient.h"

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));                                               // Réinitialiser le générateur de nombres aléatoires (a garder dans le main, car si le programme est exécuté plusieurs fois en peu de temps, std::time(nullptr) pourrait retourner la même valeur, ce qui entraîne la création des mêmes séquences de nombres aléatoires et donc des mêmes positions de bateaux.
    TCPClient client("10.187.52.32", 12345);
    CoreGame jeu; 
    jeu.jouer(); //boucle du jeu

    return 0;
}







































//Localization l("fr");
//std::cout << l.getString("titre du jeu") << std::endl;
//Localization l2("eng");
//std::cout << l2.getString("titre du jeu") << std::endl;