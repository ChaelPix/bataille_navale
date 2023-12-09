#include "BattleshipServer.h"

BattleshipServer::BattleshipServer(ushort serverPORT) : TCPServer(serverPORT) {}

void BattleshipServer::gameSession(SOCKET client1, SOCKET client2, bool isFirstPlayerToPlay)
{
    auto sessionState = sessionManager.getSessionState(client1, client2);
    if (!sessionState) return;

    //first message
    std::string message = "";
    isFirstPlayerToPlay ? message = "GStart" : message = "GWait";
    std::cout << "Sent to " << client2 << " " << message << std::endl;
    sendMessage(client2, message);

    //GameLoop
    try {

        while (isServerOn && sessionState->isActive()) {
            std::string messageFromClient1 = receiveMessageFromClient(client1);

            // if client quit
            if (messageFromClient1.empty()) {
                std::cout << "Someone leaves" << std::endl;
                sessionState->disconnectClient(isFirstPlayerToPlay);
                sendMessage(client2, "Fin");
                break;
            }

            std::cout << "Message received from " << client1 << " send to " << client2 << " containing : \n" << messageFromClient1 << std::endl << std::endl;
            std::string response = processGameMessage(messageFromClient1);
            send(client2, response.c_str(), response.length(), 0);
            if (messageFromClient1 == "SLEAVE")
                break;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Exception dans gameSession: " << e.what() << std::endl;
    }

    if (sessionState->isActive()) {
        std::cout << "Closing a Room" << std::endl;
        sessionState->disconnectClient(isFirstPlayerToPlay);
        if (!sessionState->isActive()) {
            sessionManager.endSession(client1, client2);
            closeClientSocket(client1);
            closeClientSocket(client2);
        }
    }
}


std::string BattleshipServer::processGameMessage(const std::string& message)
{
    return message; 
}