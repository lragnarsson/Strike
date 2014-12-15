/***************************************
Client.h

Class for running the game client-side

Written by:
Lage Ragnarsson
Isak Wiberg
Jesper Otterholm
Filip Östman
***************************************/

#ifndef _CLIENT_
#define _CLIENT_

#include "./Game.h"
#include "./ResourcePath.h"
#include "./Player.h"
#include "./GameState.h"
#include "./Controller.h"
#include "./Team.h"
#include "./Weapon.h"
#include "./NetworkHandler.h"
#include "./HUD.h"


#include <stdio.h>
#include <string>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Client: public Game {
public:
    Client();
    ~Client();

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    bool connectToServer(std::string name, int team, sf::IpAddress ip);
    void networkFunction();
    void run() override;

private:
    void readFromNetwork() override;
    void writeToNetwork() override;
    void handleGameLogic() override;
    void handleInput();
    void handleCollisions();
    void draw();
    void collideMoveVector(sf::Vector2f position,
                           sf::Vector2f& moveVector,
                           float radius);
    void handleShots();
    void loadTextures();
    void handleVision();
    void createDecals();
    void roundRestart();
    void handleSounds();

    int clientID_ = 1337;
    NetworkHandler nh_;
    GameState gameState_;
    HUD hud_;
    std::string clientName_;
    sf::RenderWindow renderWindow_;
    Controller controller_;
    std::map<std::string, sf::Texture*> textures_;
    sf::SoundBuffer buffer;
    sf::Sound shotSound_;
};

#endif // _CLIENT_
