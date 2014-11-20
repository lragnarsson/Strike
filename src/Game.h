//
//  Game.h
//  Strike
//
//  Created by Isak Wiberg on 2014-11-20.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#ifndef __Strike__Game__
#define __Strike__Game__

#include <stdio.h>
#include "ResourcePath.hpp"
#include "Player.h"
#include "GameState.h"
#include "Controller.h"
#include "Team.h"
#include "Weapon.h"


/*  Game är en abstrakt klass som innehåller en run-funktion för att starta,
 *  ett GameState-objekt för att hålla reda på spelets tillstånd och ett 
 *  NetworkHandler-objekt för att kommunicera med nätverket.
 */

class Game{
public:
    virtual ~Game() = default;
    
    // NetworkHandler NetworkHandler; lägg till detta när NetworkHandler är implementerad.
    GameState GameState;
    
    virtual void run() = 0;                 // gameloopen för server och klient.
    virtual void readNetwork() = 0;         // ta emot data från nätverket och behandla den.
    virtual void writeNetwork() = 0;        // skicka data på nätverket.
    virtual void logic() = 0;               // sköter logiken hos klient resp. server. 
    
protected:
    Game() = default;
    Game(const Game&) = delete;             // borttagen kopieringskonstruktor
    Game& operator=(const Game&) = delete;  // borttagen kopieringstilldelning
    
};

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
    void readNetwork() override;
    void writeNetwork() override;
    void logic() override;

    
    int clientID_;                          // detta fås av servern vid init.
    std::string clientName_;                // detta borde man få välja själv vid start
    sf::View view_;                         // en instans av en view som ska användas av Controller.
    sf::RenderWindow renderWindow;          // en instans av ett fönster. Här ritas allt ut.
    Controller controller;                  // en instans av en controller som används för att styra spelarkaraktären.
    
    
};



/*  Ärver från Game och skapas för att starta en server som klienter kan ansluta
 *  till. Server skiljer sig från Client då den till exempel inte behöver rita 
 *  någon spelgrafik. Interaktionen med NetworkHandler-objektet kommer också att 
 *  vara lite annolunda.
 */

class Server: public Game{
public:
    Server() = default;
    ~Server();
    
    Server(const Server&) = delete;         // borttagen kopieringskonstruktor
    Server& operator=(const Server&) = delete; // borttagen kopieringstilldelning
    
    void run() override;
    void readNetwork() override;
    void writeNetwork() override;
    void logic() override;
};


#endif /* defined(__Strike__Game__) */
