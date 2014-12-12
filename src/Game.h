//
//  Game.h
//  Strike
//

#ifndef __Strike__Game__
#define __Strike__Game__

#include <stdio.h>
#include "ResourcePath.h"
#include "Player.h"
#include "GameState.h"
#include "Controller.h"
#include "Team.h"
#include "Weapon.h"

class Game {
public:
    virtual ~Game() = default;
    // NetworkHandler NetworkHandler; lägg till detta när NetworkHandler är implementerad.
    GameState gameState_;

    virtual void run() = 0;

protected:
    virtual void readNetwork() = 0;
    virtual void writeNetwork() = 0;
    virtual void handleGameLogic() = 0;
    virtual void handleCollisions() = 0;
    Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};

#endif /* defined(__Strike__Game__) */
