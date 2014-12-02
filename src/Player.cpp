//
//  Player.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "./Player.h"

Player::Player(int ClientID): clientID_(ClientID) {
  if (!texture_.loadFromFile(resourcePath("res/images/") + "cage.png"))
    throw std::exception();

  // texture for playerSprite
  texture_.setSmooth(true);
  setTexture(texture_);
  setScale(sf::Vector2f(0.1f, 0.1f));
  setOrigin(177.f, 245.f);
}

void Player::setWeapon(Weapon* newWeapon) {
  weapon_ = newWeapon;
}

void Player::changeSpeed(float speed) {
  if (health_ <=50) {
    speedConstant_ = 0.5f; //If the player is severe damaged he will not be able to move faster than speed_/2
  }
  else {
    speedConstant_ = speed; //Else, accept the given speed
  }
}

void Player::reloadWeapon() {
  weapon_->reloadWeapon();
}

std::vector<Shot*> Player::fire() {
  return weapon_->fire(clientID_, getPosition(), aimVector_);
}

int Player::getClientID() const {
  return clientID_;
}

void Player::setMoveVector(const sf::Vector2f& moveVector,
                           float elapsedSeconds) {
  moveVector_ = moveVector * elapsedSeconds * speed_ * speedConstant_;
}

void Player::handleRotation(const sf::Vector2f& aimVector) {
  aimVector_ = aimVector;
  float angle = (aimVector_.y > 0) ? radConversion_ * acos(aimVector_.x)
      : 360 - radConversion_ * acos(aimVector_.x);
  setRotation(angle);
}

void Player::move(const sf::Vector2f& offset) {
  Sprite::move(moveVector_);
}
