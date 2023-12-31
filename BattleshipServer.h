#include "TCPServer.h"



class BattleshipServer : public TCPServer {
public:
    BattleshipServer(ushort serverPORT);

protected:
    void gameSession(SOCKET client1, SOCKET client2, bool isFirstPlayerToPlay) override;
    std::string processGameMessage(const std::string& message) override;

};


