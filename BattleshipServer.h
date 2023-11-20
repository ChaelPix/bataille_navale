#pragma once
#include "TCPServer.h"

class BattleshipServer : public TCPServer
{

private :
     void init() override;
     void acceptClients() override;
     void gameSession(SOCKET client1, SOCKET client2) override;
     std::string processGameMessage(const std::string& message) override;
     void matchClientsForGame() override;

public :
    BattleshipServer(ushort portNum);
};

