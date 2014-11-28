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
#include <iostream>

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

void Player::reloadWeapon(){
    weapon_->reloadWeapon();
}

std::vector<Shot*> Player::fire(){
    return weapon_->fire(clientID_, getPosition(), aimVector_);
}

int Player::getClientID() const{
    return clientID_;
}

void Player::setMoveVector(const sf::Vector2f& moveVector, float elapsedSeconds) {
    moveVector_ = moveVector * elapsedSeconds * speed_;
}

sf::Vector2f Player::handleRotation(const sf::Vector2i& aimVector) {
    sf::Vector2f dir = sf::Vector2f(mousePos.x - getPosition().y, mousePos.y - getPosition().y); 
    aimVector_ = dir / (sqrtf(pow(dir.x, 2) + pow(dir.y, 2)));
    float angle = (aimVector_.y > 0) ? radConversion_ * acos(aimVector_.x) : 360 - radConversion_ * acos(aimVector_.x);
    rotate(angle);
    
    return aimVector_;
}

void Player::move(const sf::Vector2f& offset) {
    Sprite::move(moveVector_);
}
