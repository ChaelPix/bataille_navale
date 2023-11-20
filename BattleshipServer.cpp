#include "BattleshipServer.h"

BattleshipServer::BattleshipServer(ushort portNum) : TCPServer(serverPORT)
{ 
	init();
}


void BattleshipServer::init()
{
	bindAndListen();
	isServerOn = true;
	listenerThread = std::thread(&BattleshipServer::acceptClients, this);
	matchThread = std::thread(&BattleshipServer::matchClientsForGame, this);
}

void BattleshipServer::acceptClients()
{
    while (isServerOn) {
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(idSocket, &readfds);
        timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        if (select(idSocket + 1, &readfds, nullptr, nullptr, &timeout) > 0)
        {
            addr_len = sizeof(adr_client);
            SOCKET clientSocket = accept(idSocket, (struct sockaddr*)&adr_client, &addr_len);

            if (clientSocket != INVALID_SOCKET) {
                idsClients.push_back(clientSocket);
                {
                    std::lock_guard<std::mutex> lock(matchmakingMutex);
                    matchmakingQueue.push(clientSocket);
                }
                cvMatchmaking.notify_one();
            }
        }
    }
}

void BattleshipServer::matchClientsForGame()
{
	while (isServerOn) {
		std::unique_lock<std::mutex> lock(matchmakingMutex);
		cvMatchmaking.wait(lock, [this] { return matchmakingQueue.size() >= 2 || !isServerOn; });

		if (!isServerOn) break;

		SOCKET client1 = matchmakingQueue.front(); matchmakingQueue.pop();
		SOCKET client2 = matchmakingQueue.front(); matchmakingQueue.pop();

		gameThreads[client1] = std::thread(&BattleshipServer::gameSession, this, client1, client2);
		gameThreads[client2] = std::thread(&BattleshipServer::gameSession, this, client2, client1);
	}
}


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

            //Machine State
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
	//Traitement grille, etc..

	return message;
}



