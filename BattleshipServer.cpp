#include "BattleshipServer.h"

BattleshipServer::BattleshipServer(ushort serverPORT) : TCPServer(serverPORT) {}

void BattleshipServer::gameSession(SOCKET client1, SOCKET client2)
{
    const std::string message = "Adversaire trouvé Socket client 1 : " + std::to_string(client1) + " client 2 : " + std::to_string(client2);
    send(client2, message.c_str(), message.length(), 0);

    try {
        while (isServerOn) {
            std::string messageFromClient1 = receiveMessageFromClient(client1);

            // Vérifier si le client1 s'est déconnecté
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

    std::chrono::milliseconds dt1(1000);
    std::this_thread::sleep_for(dt1);
    closeClientSocket(client1);
    closeClientSocket(client2);
}


std::string BattleshipServer::processGameMessage(const std::string& message)
{
    return message; 
}