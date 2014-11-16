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

Player::Player(){
    if (!texture_.loadFromFile(resourcePath("res/img/") + "cage.png"))
        throw std::exception();
    sprite_.setTexture(texture_);
    sprite_.setScale(sf::Vector2f(0.1f, 0.1f));
    sprite_.setOrigin(177.f, 245.f);
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(sprite_, states);
    
}

float Player::getSpeed() const{
    return speed_;
}