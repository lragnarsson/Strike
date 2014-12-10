//
//  Player.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "./Player.h"
#include <math.h>
#include <vector>

Player::Player(int ClientID, sf::Texture* spriteSheet)
    : PhysicalCircle(getPosition(), 64.0f), clientID_(ClientID), crosshair_(5.f) {

    initCrosshair();
    initAnimation(spriteSheet);
}

void Player::initCrosshair() {
    crosshair_.setFillColor(sf::Color::White);
    crosshair_.setOrigin(sf::Vector2f(3.f, 3.f));
    crosshair_.setOutlineThickness(2.f);
    crosshair_.setOutlineColor(sf::Color::Black);
    setPosition(600, 450);
}

void Player::initAnimation(sf::Texture* spriteSheet) {
    frameRect_ = sf::IntRect(0, 0, frameWidth_, frameHeight_);
    
    texture_.setSmooth(true);
    setTexture(*spriteSheet);
    setTextureRect(frameRect_);
    setScale(sf::Vector2f(0.8f, 0.8f));
    setOrigin(80.f, 80.f);
}

void Player::setWeapon(Weapon* newWeapon) {
    weapon_ = newWeapon;
}

void Player::setSpeedMultiplier(float speed) {
    if (health_ <=50)
        speedMultiplier_ = 0.5f;
    else
        speedMultiplier_ = speed;
}

void Player::setHealth(unsigned int amount) {
    if (amount >= health_)
        health_ = 0;
    else
        health_ -= amount;
}

void Player::hasNotFired() {
    weapon_->hasNotFired();
}

void Player::reloadWeapon() {
    weapon_->reloadWeapon();
}

void Player::lastSeenNow() {
    lastSeen.restart();
}

int Player::getLastSeen() {
   return lastSeen.getElapsedTime().asMilliseconds();
}

std::vector<Shot*> Player::fire() {
  if(speedMultiplier_ <= 1.0f) {
    return weapon_->fire(clientID_,
                       getPosition() + aimVector_ * (PhysicalCircle::getRadius() + 1.f),
                       aimVector_);
  }
  else {
    std::vector<Shot*> shotVector;
    return shotVector;
  }
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
    sf::Vector2f direction {static_cast<float>(sgn(targetSpeed.x - curSpeed_.x)),
                            static_cast<float>(sgn(targetSpeed.y - curSpeed_.y))};

    curSpeed_ += acceleration_ * direction * elapsedSeconds;

    if (sgn(targetSpeed.x - curSpeed_.x) != direction.x)  // is the speed higher than allowed
        curSpeed_.x = targetSpeed.x;
    if (sgn(targetSpeed.y - curSpeed_.y) != direction.y)
        curSpeed_.y = targetSpeed.y;
    moveVector_ = curSpeed_ * elapsedSeconds;
}

void Player::handleRotation(const sf::Vector2f& aimVector) {
    aimVector_ = aimVector;
    float angle = (aimVector_.y > 0) ? radConversion_ * acosf(aimVector_.x)
          : 360 - radConversion_ * acosf(aimVector_.x);
    setRotation(angle);
    crosshair_.setPosition(getPosition() + aimVector_ * weapon_->getCHDistance());
}

void Player::move() {
    Sprite::move(moveVector_);
    PhysicalCircle::setCenter(getPosition());
}

sf::CircleShape* Player::getCrosshair() {
    return &crosshair_;
}

void Player::animate() {
      if (animClock_.getElapsedTime().asMilliseconds() >= frameTime_) {
        if (length(curSpeed_) > 400)
          currentRow_ = 4;
        else if (length(curSpeed_) > 0)
          currentRow_ = 2;
        else
          currentRow_ = 0;
        if (false)
          currentRow_++;
        setTextureRect(sf::IntRect(frameWidth_ * (currentFrame_ % columns_),
                                 frameHeight_ * currentRow_,
                                 frameWidth_, frameHeight_));
        if (currentFrame_ == 59)
          currentFrame_ = 0;
        else
          currentFrame_++;
        animClock_.restart();
      }
}
