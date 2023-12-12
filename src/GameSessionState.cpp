#include "GameSessionState.h"

void GameSessionState::disconnectClient(bool isFirstClient) {
    std::lock_guard<std::mutex> lock(mtx);
    if (isFirstClient) {
        isClient1Connected = false;
    }
    else {
        isClient2Connected = false;
    }
    if (!isClient1Connected && !isClient2Connected) {
        isSessionActive = false;
    }
}

bool GameSessionState::isActive() {
    std::lock_guard<std::mutex> lock(mtx);
    return isSessionActive;
}
