#include <SFML/Graphics.hpp>
#include <iostream>
#include "TCPClient.h"
#include "TCPServer.h"

#include <Windows.h>
int main()
{
    TCPServer serveur(55555);
    TCPClient client("10.187.52.31", 55555);

    client.sendMessage("Bonjour");
    Sleep(5000);
    std::cout << client.receiveMessage();

    serveur.closeSocket();

    return 0;
}