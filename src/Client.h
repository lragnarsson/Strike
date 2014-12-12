//
//  Client.h
//  Strike
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
#include "./NetworkHandler.h"

class Client: public Game {
public:
    Client();
    ~Client();

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    bool connectToServer(std::string name, int team, sf::IpAddress ip);
    void run() override;
    static sf::Texture* getTexturePtr(std::string name);
    static void loadTextures();
    static std::map<std::string, sf::Texture*> textures_;
private:
    void readFromNetwork() override;
    void writeToNetwork() override;
    void handleGameLogic() override;
    void handleInput();
    void handleCollisions() override;
    void draw();
    void collideMoveVector(sf::Vector2f position,
                           sf::Vector2f& moveVector,
                           float radius);
    void handleShots();
    void loadTextures();
    void handleVision();
    void createDecals();
    void roundRestart();
    void handleGameObjects();

    int clientID_ = 1337;
    NetworkHandler nh_;
    GameState gameState_;
    std::string clientName_;
    sf::RenderWindow renderWindow_;
    Controller controller_;
};

#endif /* defined(__Strike__Client__) */
