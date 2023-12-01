#include <SFML/Graphics.hpp>
#include <iostream>
#include "Localization.h"
#include "CoreGame.h"
#include "BsBDD.h"
#include "TCPClient.h"

int main()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));                                               // R�initialiser le g�n�rateur de nombres al�atoires (a garder dans le main, car si le programme est ex�cut� plusieurs fois en peu de temps, std::time(nullptr) pourrait retourner la m�me valeur, ce qui entra�ne la cr�ation des m�mes s�quences de nombres al�atoires et donc des m�mes positions de bateaux.
    TCPClient client("10.187.52.32", 12345);
    CoreGame jeu; 
    jeu.jouer(); //boucle du jeu

    return 0;
}







































//Localization l("fr");
//std::cout << l.getString("titre du jeu") << std::endl;
//Localization l2("eng");
//std::cout << l2.getString("titre du jeu") << std::endl;