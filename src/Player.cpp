//
//  Player.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "ResourcePath.h"
#include "Player.h"
#include "Weapon.h"
#include <math.h>

Player::Player(int ClientID): clientID_(ClientID){
    if (!texture_.loadFromFile(resourcePath("res/images/") + "cage.png"))
        throw std::exception();

    // texture for playerSprite
    texture_.setSmooth(true);
    setTexture(texture_);
    setScale(sf::Vector2f(0.1f, 0.1f));
    setOrigin(177.f, 245.f);
}

void Player::setWeapon(Weapon* newWeapon){
    weapon_ = newWeapon;
}

std::vector<Shot*> Player::fire(){
    sf::Vector2f dir{cosf(getRotation()),-sinf(getRotation())}; // unit vector with direction
    return weapon_->fire(clientID_, getPosition(), dir);
}

int Player::getClientID() const{
    return clientID_;
}

void Player::setMoveVector(const sf::Vector2f& moveVector, float elapsedSeconds) {
    moveVector_ = moveVector * elapsedSeconds * speed_;
}

void Player::handleRotation(const sf::Vector2i& aimDelta) {
    
    rotate(aimDelta.x);
}

void Player::move(const sf::Vector2f& offset) {
    Sprite::move(moveVector_);
}
