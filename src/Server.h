/***************************************
Server.h

Class for running the game server-side

Written by:
Lage Ragnarsson
Isak Wiberg
Erik Sköld
***************************************/

#ifndef _SERVER_
#define _SERVER_

#include "./Game.h"
#include "./ResourcePath.h"
#include "./Player.h"
#include "./GameState.h"
#include "./Controller.h"
#include "./Team.h"
#include "./Weapon.h"
#include "./NetworkHandler.h"

#include <stdio.h>

class Server: public Game{
public:
    Server() = default;
    ~Server() noexcept {};

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    void networkFunction();
    void run() override;
    void readFromNetwork() override;
    void writeToNetwork() override;
    void handleGameLogic() override;

    void acceptConnections();   // Loops until user presses enter
    void initRemotePlayers();

private:
    NetworkHandler nh_;
    GameState gameState_;

    void roundRestart();
    void handleShot(AddShot*);
    void updatePlayer(PlayerUpdate*);
};

#endif // _SERVER_
