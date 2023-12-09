#include "TCPServer.h"

TCPServer::TCPServer(ushort serverPORT) : TCPWinsocksMaster(serverPORT)
{
    init();
}

void TCPServer::init()
{
    bindAndListen();
    isServerOn = true;
    listenerThread = std::thread(&TCPServer::acceptClients, this);
    matchThread = std::thread(&TCPServer::matchClientsForGame, this);
}

void TCPServer::setupAddress()
{
    memset(&adr_server, 0, sizeof(adr_server));

    adr_server.sin_family = AF_INET;
    adr_server.sin_port = htons(serverPORT);
    adr_server.sin_addr.s_addr = htonl(INADDR_ANY);
}

void TCPServer::bindAndListen()
{
    setupAddress();

    if (bind(idSocket, (struct sockaddr*)&adr_server, sizeof(adr_server)) == SOCKET_ERROR) {
        throw std::runtime_error("Bind Failed");
    }

    if (listen(idSocket, 1) == SOCKET_ERROR) {
        throw std::runtime_error("Listen Failed");
    }
}

void TCPServer::acceptClients()
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
                    std::cout << "a Client is connected : " << clientSocket << std::endl;
                    std::lock_guard<std::mutex> lock(matchmakingMutex);
                    matchmakingQueue.push(clientSocket);
                }
                cvMatchmaking.notify_one();
            }
        }
    }
}

void TCPServer::matchClientsForGame()
{
    while (isServerOn) {
        std::unique_lock<std::mutex> lock(matchmakingMutex);
        cvMatchmaking.wait(lock, [this] { return matchmakingQueue.size() >= 2 || !isServerOn; });

        if (!isServerOn) break;


        SOCKET client1 = matchmakingQueue.front(); matchmakingQueue.pop();
        if (!isClientConnected(client1)) continue; 

        SOCKET client2 = matchmakingQueue.front(); matchmakingQueue.pop();
        if (!isClientConnected(client2)) {
            matchmakingQueue.push(client1);
            continue;
        }

        std::cout << "Matchmaking made between : " << client1 << " and " << client2 << std::endl;
        sessionManager.createSession(client1, client2);
        gameThreads[client1] = std::thread(&TCPServer::gameSession, this, client1, client2, false);
        gameThreads[client2] = std::thread(&TCPServer::gameSession, this, client2, client1, true);
    }
}

void TCPServer::gameSession(SOCKET client1, SOCKET client2, bool isFirstPlayerToPlay)
{
    std::string message = "";
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


void TCPServer::closeClientSocket(SOCKET clientSocket)
{
    closesocket(clientSocket);
}


std::string TCPServer::receiveMessageFromClient(SOCKET clientId)
{
    uint trameLenght = recv(clientId, trame_lect, DIMMAX, 0);

    if (trameLenght > 0 && trameLenght < DIMMAX) {
        trame_lect[trameLenght] = '\0';
        return std::string(trame_lect);
    }
    else {
        return std::string();
    }
}

void TCPServer::closeSocket()
{
    isServerOn = false;
    cvMatchmaking.notify_all();

    if (listenerThread.joinable()) {
        listenerThread.join();
    }
    if (matchThread.joinable()) {
        matchThread.join();
    }

    closesocket(idSocket);

    for (auto& pair : gameThreads) {
        if (pair.second.joinable()) {
            pair.second.join();
        }
    }
}


std::string TCPServer::processGameMessage(const std::string& message)
{
    return message; 
}

bool TCPServer::isSocketActive(SOCKET clientSocket) {
    char buffer;
    int result = recv(clientSocket, &buffer, 1, MSG_PEEK);
    if (result <= 0) return false; 
    return true; 
}

bool TCPServer::isClientConnected(SOCKET clientSocket)
{
    sendMessage(clientSocket, "matchmaking");
    std::string s = receiveMessageFromClient(clientSocket);
    std::cout << "CheckClient connected : " << s << std::endl;

    return s != "";
}

