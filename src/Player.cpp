//
//  Player.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "ResourcePath.hpp"
#include "Player.h"
#include <math.h>

Player::Player(int ClientID): clientID_(ClientID){
    sf::Texture weaponTexture;
    if (!texture_.loadFromFile(resourcePath("res/img/") + "cage.png"))
        throw std::exception();

    // texture for self
    texture_.setSmooth(true);
    setTexture(texture_);
    setScale(sf::Vector2f(0.1f, 0.1f));
    setOrigin(177.f, 245.f);

}
void Player::setWeapon(Weapon* newWeapon){
    weapon_ = newWeapon;
}

int Player::getClientID() const{
    return clientID_;
}

float Player::getSpeed() const{
    return speed_;
}
