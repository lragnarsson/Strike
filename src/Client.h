//
//  Client.h
//  Strike
//
//  Created by Isak Wiberg on 2014-11-25.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#ifndef __Strike__Client__
#define __Strike__Client__

#include <stdio.h>
#include "Game.h"
#include "ResourcePath.h"
#include "Player.h"
#include "GameState.h"
#include "Controller.h"
#include "Team.h"
#include "Weapon.h"

/*  Client är en subklass till Game som skapas hos användaren när denne startar
 *  spelet. Här finns bland annat information för att unikt identifiera en klient
 *  och ett Controller-objekt som hanterar användarens input. Logik för utritning
 *  finns i Client.
 */

class Client: public Game{
public:
    Client() = default;
    ~Client();
    
    Client(const Client&) = delete;         // borttagen kopieringskonstruktor
    Client& operator=(const Client&) = delete; // borttagen kopieringstilldelning
    
    void run() override;
    
private:
    void readNetwork() override;
    void writeNetwork() override;
    void handleGameLogic() override;
    void handleInput();
    void handleCollisions() override;
    void draw();
    
    
    void handleShots(); // this should take collisionobjects when they are implemented. 
    
    
    int clientID_;                          // detta fås av servern vid init.
    std::string clientName_;                // detta borde man få välja själv vid start
    sf::View view_;                         // en instans av en view som ska användas av Controller.
    sf::RenderWindow renderWindow;          // en instans av ett fönster. Här ritas allt ut.
    Controller controller;                  // en instans av en controller som används för att styra spelarkaraktären.
    
    
};



#endif /* defined(__Strike__Client__) */
