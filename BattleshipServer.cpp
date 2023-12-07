#include "BattleshipServer.h"

BattleshipServer::BattleshipServer(ushort serverPORT) : TCPServer(serverPORT) {}

void BattleshipServer::gameSession(SOCKET client1, SOCKET client2, bool isFirstPlayerToPlay)
{
    //first message
    std::string message = "";
    isFirstPlayerToPlay ? message = "GStart" : message = "GWait";
    send(client2, message.c_str(), message.length(), 0);
    //GameLoop
    try {

        while (isServerOn) {
            std::string messageFromClient1 = receiveMessageFromClient(client1);

            // if client quit
            if (messageFromClient1.empty()) {

                closeClientSocket(client1);
                sendMessage(client2, "fin");
                break;
            }

            std::string response = processGameMessage(messageFromClient1);
            send(client2, response.c_str(), response.length(), 0);
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception dans gameSession: " << e.what() << std::endl;
    }

    //closing
    std::chrono::milliseconds dt1(1000);
    std::this_thread::sleep_for(dt1);
    closeClientSocket(client1);
    closeClientSocket(client2);
}


std::string BattleshipServer::processGameMessage(const std::string& message)
{
    return message; 
}