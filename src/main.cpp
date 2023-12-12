#include <iostream>
#include "BattleshipServer.h"

void ServerMod()
{
    ushort port = 12345;

    BattleshipServer server(port);
    std::cout << "Started Server on port: " << port << ". Type the password (1234) to stop the server..." << std::endl;

    std::string s  = "";

    while (s != "1234")
        std::cin >> s;

    server.closeSocket();
}

int main() {
    ServerMod();
    return 0;
}