#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include "GameSessionState.h"
#include <map>
#include <mutex>
#include <memory>
#include <utility>
#include <sys/types.h>
#include <sys/socket.h> // socket, recv, send
#include <netinet/in.h> // sockaddr_in, htonl
#include <arpa/inet.h>  // inet_addr
#include <unistd.h>     // close
#include <cstring> 

class SessionManager {
public:
    void createSession(int client1, int client2);
    std::shared_ptr<GameSessionState> getSessionState(int client1, int client2);
    void endSession(int client1, int client2);

private:
    std::map<std::pair<int, int>, std::shared_ptr<GameSessionState>> sessions;
    std::mutex mtx;
};

#endif
