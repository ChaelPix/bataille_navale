#include <SFML/Graphics.hpp>
#include <iostream>


#include "BattleshipServer.h"

void ServerMod()
{
    ushort port = 12345;

    BattleshipServer server(port);
    std::cout << "Server started on Port: " << port << ". Type 'STOP' to close the server..." << std::endl;

    std::string s  = "";

    while (s != "stop" || s != "STOP")
        std::cin >> s;

    server.closeSocket();
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    ServerMod();
    return 0;
}


