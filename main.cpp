#include <SFML/Graphics.hpp>
#include <iostream>
#include "TCPClient.h"
#include "TCPServer.h"


int main()
{
   
    TCPServer tcpServeur(55555);
    
    std::string fin;

    std::cout << "Finir serveur ?";
    std::cin >> fin;

    tcpServeur.closeSocket();

    return 0;
}