#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include "GameSessionState.h"
#include <map>
#include <mutex>
#include <memory>
#include <utility>
#include <winsock.h>

class SessionManager {
public:
    void createSession(SOCKET client1, SOCKET client2);
    std::shared_ptr<GameSessionState> getSessionState(SOCKET client1, SOCKET client2);
    void endSession(SOCKET client1, SOCKET client2);

private:
    std::map<std::pair<SOCKET, SOCKET>, std::shared_ptr<GameSessionState>> sessions;
    std::mutex mtx;
};

#endif
