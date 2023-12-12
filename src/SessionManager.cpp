#include "SessionManager.h"

void SessionManager::createSession(int client1, int client2) {
    std::lock_guard<std::mutex> lock(mtx);
    sessions[std::make_pair(client1, client2)] = std::make_shared<GameSessionState>();
}

std::shared_ptr<GameSessionState> SessionManager::getSessionState(int client1, int client2) {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = sessions.find(std::make_pair(client1, client2));
    if (it != sessions.end()) {
        return it->second;
    }
    return nullptr;
}

void SessionManager::endSession(int client1, int client2) {
    std::lock_guard<std::mutex> lock(mtx);
    sessions.erase(std::make_pair(client1, client2));
}
