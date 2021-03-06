/***************************************
Client.h

Class for running the game client-side

Written by:
Lage Ragnarsson
Isak Wiberg
Jesper Otterholm
Filip �stman
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
    ~Client() noexcept;

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    bool connectToServer(std::string name, int team, sf::IpAddress ip);
    void networkFunction();
    void run() override;
    static void loadTextures();
    static void loadSoundBuffers();
    static std::map<std::string, sf::Texture*> textures_;
    static std::map<std::string, sf::SoundBuffer*> soundBuffers_;

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
    void handleVision();
    void createDecals();
    void roundRestart();
    void handleSounds();
    void handleGameObjects();

    int clientID_ = 1337; // this changes after you connect to a server and recieve a new one.
    
    sf::Clock roundRestartClock_;
    sf::Time freezeTime_ {sf::seconds(3.0f)};
    NetworkHandler nh_;
    GameState gameState_;
    HUD hud_;
    std::string clientName_;
    sf::RenderWindow renderWindow_;
    Controller controller_;
    sf::SoundBuffer soundBuffer;
    sf::Sound shotSound_;
    sf::Clock clock_;
};

#endif // _CLIENT_
