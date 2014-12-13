//
//  Server.h
//  Strike
//
//  Created by Isak Wiberg on 2014-11-25.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#ifndef __Strike__Server__
#define __Strike__Server__

#include <stdio.h>
#include "Game.h"
#include "ResourcePath.h"
#include "Player.h"
#include "GameState.h"
#include "Controller.h"
#include "Team.h"
#include "Weapon.h"
#include "NetworkHandler.h"



/*  Ärver från Game och skapas för att starta en server som klienter kan ansluta
 *  till. Server skiljer sig från Client då den till exempel inte behöver rita
 *  någon spelgrafik. Interaktionen med NetworkHandler-objektet kommer också att
 *  vara lite annolunda.
 */

class Server: public Game{
public:
    Server() = default;
    ~Server() = default;

    Server(const Server&) = delete;         // borttagen kopieringskonstruktor
    Server& operator=(const Server&) = delete; // borttagen kopieringstilldelning

    void run() override;
    void readFromNetwork() override;
    void writeToNetwork() override;
    void handleGameLogic() override;
    void handleCollisions() override;

    void acceptConnections();

private:
    NetworkHandler nh_;
    GameState gameState_;

    void roundRestart();
    void handleShot(Message*);
    void updatePlayer(Message*);
};

#endif /* defined(__Strike__Server__) */
