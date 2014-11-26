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
    sf::Texture weaponTexture;
    if (!texture_.loadFromFile(resourcePath("res/images/") + "cage.png"))
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

std::vector<Shot*> Player::fire(){
    return weapon_.fire(player->clientID_, player->getPosition(), window.mapPixelToCoords(mouse) - view_->getCenter());
}

int Player::getClientID() const{
    return clientID_;
}

float Player::getSpeed() const{
    return speed_;
}
