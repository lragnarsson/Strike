//
//  Player.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "./Player.h"
#include <math.h>

int sgn(float x) {
    return (x > 0) - (x < 0);
}

Player::Player(int ClientID): PhysicalCircle(getPosition(), 32.0f),  clientID_(ClientID) {
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

void Player::setSpeedMultiplier(float speed) {
  if (health_ <=50) {
    speedMultiplier_ = 0.5f;  // If the player is severe damaged he will not be able to move faster than speed_/2
  }
  else {
    speedMultiplier_ = speed; //Else, accept the given speed
  }
}

void Player::setHealth(unsigned int amount) {
  if (amount >= health_) {
    health_ = 0;
  }
  else {
    health_ -= amount;
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

sf::Vector2f& Player::getMoveVector() {
  return moveVector_;
}

void Player::calculateMoveVector(const sf::Vector2f& inputVector,
                                 float elapsedSeconds) {
    sf::Vector2f targetSpeed = inputVector * maxSpeed_ * speedMultiplier_;
    sf::Vector2f direction {static_cast<float>(sgn(targetSpeed.x - curSpeed_.x)), static_cast<float>(sgn(targetSpeed.y - curSpeed_.y))};

    curSpeed_ += acceleration_ * direction * elapsedSeconds;

    if (sgn(targetSpeed.x - curSpeed_.x) != direction.x) // is the speed higher than allowed
        curSpeed_.x = targetSpeed.x;
    if (sgn(targetSpeed.y - curSpeed_.y) != direction.y)
        curSpeed_.y = targetSpeed.y;
    moveVector_ = curSpeed_ * elapsedSeconds;
}

void Player::handleRotation(const sf::Vector2f& aimVector) {
  aimVector_ = aimVector;
  float angle = (aimVector_.y > 0) ? radConversion_ * acos(aimVector_.x)
      : 360 - radConversion_ * acos(aimVector_.x);
  setRotation(angle);
}

void Player::move() {
    Sprite::move(moveVector_);
    // PhysicalCircle::setCenter(getPosition());
}

