//
//  Player.h
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#ifndef __Strike__Player__
#define __Strike__Player__

#include <math.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "./Weapon.h"
#include "./ResourcePath.h"
#include "./PhysicalObject.h"

class Player: public sf::Sprite, public PhysicalCircle {
public:
    explicit Player(int ClientID);
    Player() = delete;
    ~Player() noexcept {};

    int getClientID() const;
    void setWeapon(Weapon* weapon);
    std::vector<Shot*> fire();
    sf::Vector2f& getMoveVector();
    void setHealth(unsigned int amount);
    void calculateMoveVector(const sf::Vector2f& moveVector,
                             float elapsedSeconds);
    void handleRotation(const sf::Vector2f& aimVector);
    void move();
    void reloadWeapon();
    void setSpeedMultiplier(float speed);
    void hasNotFired();

    void lastSeenNow();
    int getLastSeen();

    sf::CircleShape* getCrosshair();

private:
    unsigned int health_ = 100;
    sf::Texture texture_;
    int clientID_;
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
};

#endif /* defined(__Strike__Player__) */
