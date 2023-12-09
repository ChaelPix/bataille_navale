#ifndef GAME_SESSION_STATE_H
#define GAME_SESSION_STATE_H

#include <mutex>

class GameSessionState {
public:
    GameSessionState() : isClient1Connected(true), isClient2Connected(true), isSessionActive(true) {}

    void disconnectClient(bool isFirstClient);
    bool isActive();

private:
    std::mutex mtx;
    bool isClient1Connected;
    bool isClient2Connected;
    bool isSessionActive;
};

#endif 
