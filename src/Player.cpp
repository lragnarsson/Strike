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

int sgn(float x) {
    return (x > 0) - (x < 0);
}

Player::Player(int ClientID)
    : PhysicalCircle(getPosition(), 64.0f), clientID_(ClientID), crosshair_(5.f) {
    if (!texture_.loadFromFile(resourcePath("res/images/") + "cage2.png"))
        throw std::exception();
    // texture for playerSprite
    texture_.setSmooth(true);
    setTexture(texture_);
    setScale(sf::Vector2f(0.4f, 0.4f));
    setOrigin(160.f, 160.f);
    crosshair_.setFillColor(sf::Color::White);
    crosshair_.setOrigin(sf::Vector2f(3.f, 3.f));
    crosshair_.setOutlineThickness(2.f);
    crosshair_.setOutlineColor(sf::Color::Black);
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
  return weapon_->fire(clientID_,
                       getPosition() + aimVector_ * (PhysicalCircle::getRadius() + 1.f),
                       aimVector_);
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
