/***************************************
Game.h

Abstract base class for Client and Server.

Written by:
nobody knows
***************************************/

#ifndef _GAME_
#define _GAME_

#include "./ResourcePath.h"
#include "./Player.h"
#include "./GameState.h"
#include "./Controller.h"
#include "./Team.h"
#include "./Weapon.h"

#include <stdio.h>

class Game{
public:
    virtual ~Game() = default;
    //GameState gameState_;

    virtual void run() = 0;

protected:
    virtual void readFromNetwork() = 0;
    virtual void writeToNetwork() = 0;
    virtual void handleGameLogic() = 0;

    Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};

#endif // _GAME_
