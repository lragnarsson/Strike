//
//  Player.h
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#ifndef __Strike__Player__
#define __Strike__Player__

#include <stdio.h>
#include "Weapon.h"
#include <SFML/Graphics.hpp>



class Player: public sf::Sprite //PhysicalCircle, this will handle collissions.
{
public:
    Player(int ClientID);
    Player() = delete;
    ~Player() = default;

    //float getRotateSpeed() const;
    //void setHealth(float amount);
    int getClientID() const;
    void setWeapon(Weapon* weapon);
    std::vector<Shot*> fire();
    void setMoveVector(const sf::Vector2f& moveVector, float elapsedSeconds);
    void handleRotation(const sf::Vector2i& aimDelta);
    void move(const sf::Vector2f& offset);
private:
    //virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Texture texture_;
    int clientID_;
    float speed_ = 100.0f; // pixels per second
    Weapon* weapon_;
    sf::Vector2f moveVector_;
    
};


#endif /* defined(__Strike__Player__) */
