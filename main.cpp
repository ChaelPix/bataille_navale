#include <SFML/Graphics.hpp>
#include <iostream>
#include "Localization.h"
int main()
{
    Localization l("fr");
    std::cout << l.getString("titre du jeu") << std::endl;

    Localization l2("eng");
    std::cout << l2.getString("titre du jeu") << std::endl;

    return 0;
}