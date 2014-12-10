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
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include "./Game.h"
#include "./ResourcePath.h"
#include "./Player.h"
#include "./GameState.h"
#include "./Controller.h"
#include "./Team.h"
#include "./Weapon.h"

/*  Client är en subklass till Game som skapas hos användaren när denne startar
 *  spelet. Här finns bland annat information för att unikt identifiera en klient
 *  och ett Controller-objekt som hanterar användarens input. Logik för utritning
 *  finns i Client.
 */

class Client: public Game {
public:
    Client();
    ~Client() {}

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    bool connectToServer(std::string name, unsigned int team, sf::IpAddress ip);
    void run() override;

private:
    void readNetwork() override;
    void writeNetwork() override;
    void handleGameLogic() override;
    void handleInput();
    void handleCollisions() override;
    void draw();
    void collideMoveVector(sf::Vector2f position,
                           sf::Vector2f& moveVector,
                           float radius);
    void handleShots();
    void loadTextures();

    int clientID_{1337};
    std::string clientName_;
    sf::RenderWindow renderWindow_;
    Controller controller_;
    std::map<std::string, sf::Texture*> textures_;
};

#endif /* defined(__Strike__Client__) */
