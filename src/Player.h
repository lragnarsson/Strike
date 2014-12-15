/***************************************
Player.h

Class for representing a player.

Written by:
Lage Ragnarsson
Jesper Otterholm
Filip Östman
***************************************/

#ifndef _PLAYER_
#define _PLAYER_

#include "./Weapon.h"
#include "./ResourcePath.h"
#include "./PhysicalObject.h"
#include "./Team.h"

#include <math.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>

class Player: public sf::Sprite, public PhysicalCircle {
public:
    Player(int ClientID, Team* team); // Server only!
    explicit Player(int ClientID, Team* team, sf::Texture* spriteSheet);
    Player() = delete;
    ~Player() noexcept {};

    int getClientID() const;
    void setClientID(int newClientID);
    Team* getTeam() const;
    void setTeam(Team* team);
    std::string getClientName() const;
    void setClientName(std::string newName);
    void setWeapon(Weapon* weapon);
    std::vector<Shot*> fire();
    sf::Vector2f& getMoveVector();
    void decreaseHealth(int amount);
    void setHealth(int health);
    void calculateMoveVector(const sf::Vector2f& moveVector,
                             float elapsedSeconds);
    void handleRotation(const sf::Vector2f& aimVector);
    void move();
    void reloadWeapon();
    void setSpeedMultiplier(float speed);
    void hasNotFired();

    void lastSeenNow();
    int getLastSeen();

    bool isDead();

    sf::CircleShape* getCrosshair();
    void animate();
    int getHealth();

private:
    int health_ = 100;
    sf::Texture texture_;
    int clientID_;
    Team* team_;
    std::string clientName_;
    float speedMultiplier_ = 1.0f;
    float maxSpeed_ = 400.0f;  // pixels per second
    float acceleration_ = 3000.0f;  // pixels per second^2
    sf::Clock lastSeen;

    Weapon* weapon_;
    sf::Vector2f moveVector_;
    sf::Vector2f curSpeed_;
    sf::Vector2f aimVector_;
    float radConversion_ = 57.29577951308232f;
    sf::CircleShape crosshair_;

    unsigned int frameTime_{10};
    unsigned int currentFrame_{0};
    unsigned int currentRow_{0};
    unsigned int frameWidth_{160};
    unsigned int frameHeight_{160};
    unsigned int columns_{10};
    sf::IntRect frameRect_;
    sf::Clock animClock_;
    sf::Texture spriteSheet_;

    void initCrosshair();
    void initAnimation(sf::Texture* texture);
};

#endif // _PLAYER_
