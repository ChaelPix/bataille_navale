#include "BattleshipServer.h"

BattleshipServer::BattleshipServer(ushort serverPORT) : TCPServer(serverPORT) {}

void BattleshipServer::gameSession(SOCKET client1, SOCKET client2, bool isFirstPlayerToPlay)
{
    //first message
    std::string message = "";
    isFirstPlayerToPlay ? message = "GStart" : message = "GWait";
    std::cout << "Sent to " << client2 << " " << message << std::endl;
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

    //closing
    std::cout << "Closing a Room" << std::endl;
    std::chrono::milliseconds dt1(100);
    std::this_thread::sleep_for(dt1);
    closeClientSocket(client1);
    closeClientSocket(client2);
}


std::string BattleshipServer::processGameMessage(const std::string& message)
{
    return message; 
}