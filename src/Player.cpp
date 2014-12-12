//
//  Player.cpp
//  Strike

#include "./Player.h"
#include <math.h>
#include <vector>

<<<<<<< HEAD
Player::Player(int ClientID, Team* team, sf::Texture* spriteSheet)
    : PhysicalCircle(getPosition(), 40.0f), clientID_(ClientID), team_(team), crosshair_(5.f) {
=======
Player::Player(int ClientID, sf::Texture* spriteSheet)
    : PhysicalCircle(getPosition(), 64.0f), clientID_(ClientID), crosshair_(5.f), inventory_() {
>>>>>>> Started work on an inventory system, game objects and grenades.

    initCrosshair();
    initAnimation(spriteSheet);
}

Player::Player(int ClientID)
: PhysicalCircle(getPosition(), 40.0f), clientID_(ClientID), crosshair_(5.f) {

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
    setScale(sf::Vector2f(0.5f, 0.5f));
    setOrigin(80.f, 80.f);
}

void Player::addEquipment(GameObject* equipment) {
    if (inventory_.size() < inventorySize_) {
        inventory_.push_back(equipment);
        equippedIndex_ = inventory_.size() - 1;
    } else {
        throwEquipped();
        inventory_.insert(inventory_.begin() + ++equippedIndex_, equipment);
    }
    CHDistance_ = inventory_.at(equippedIndex_)->getCHDistance();
}

void Player::setSpeedMultiplier(float speed) {
    if (health_ <=50)
        speedMultiplier_ = 0.5f;
    else
        speedMultiplier_ = speed;
}

void Player::decreaseHealth(int amount) {
    if (amount >= health_)
        health_ = 0;
    else
        health_ -= amount;
}

int Player::getHealth() { //För testning!
  return health_;
}

void Player::setHealth(int health) {
    health_ = health;
}

bool Player::isDead() {
    return health_ == 0;
}

void Player::hasNotFired() {
    if (holdingFirearm())
        static_cast<Weapon*>(inventory_.at(equippedIndex_))->hasNotFired();
}

void Player::reloadWeapon() {
  if (holdingFirearm())
      static_cast<Weapon*>(inventory_.at(equippedIndex_))->reloadWeapon();
}

void Player::lastSeenNow() {
    lastSeen.restart();
}

int Player::getLastSeen() {
   return lastSeen.getElapsedTime().asMilliseconds();
}

std::vector<Shot*> Player::fire() {
    if(speedMultiplier_ <= 1.0f)
        return static_cast<Weapon*>(inventory_.at(equippedIndex_))->fire(
            clientID_, getPosition() + aimVector_ * (getRadius() + 5.f), aimVector_);
    std::vector<Shot*> shotVector;
    return shotVector;
}

int Player::getClientID() const {
    return clientID_;
}

Team* Player::getTeam() const {
    return team_;
}

void Player::setTeam(Team* team) {
    team_ = team;
}


void Player::setClientName(std::string newName) {
    clientName_ = newName;
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
    crosshair_.setPosition(getPosition() + aimVector_ * CHDistance_);
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
          if (inFireAnimation())
              currentRow_++;
          setTextureRect(sf::IntRect(frameWidth_ * currentFrame_,
                                     frameHeight_ * currentRow_,
                                     frameWidth_, frameHeight_));
          if (currentFrame_ == columns_ - 1)
              currentFrame_ = 0;
          else
              currentFrame_++;
          animClock_.restart();
      }
}

bool Player::inFireAnimation() {
  return (holdingFirearm() &&
          static_cast<Weapon*>(inventory_.at(equippedIndex_))->isAnimating());
}

void Player::equipAt(unsigned int index) {
  if (index < inventory_.size())
      equippedIndex_ = index;
  else
      equippedIndex_ = inventory_.size() - 1;
  CHDistance_ = inventory_.at(equippedIndex_)->getCHDistance();
}

void Player::equipNext() {
    equippedIndex_++;
    equippedIndex_ %= inventory_.size();
    CHDistance_ = inventory_.at(equippedIndex_)->getCHDistance();
}

void Player::equipPrevious() {
    equippedIndex_--;
    equippedIndex_ %= inventory_.size();
    CHDistance_ = inventory_.at(equippedIndex_)->getCHDistance();
}

bool Player::holdingFirearm() {
    return (dynamic_cast<Weapon*>(inventory_.at(equippedIndex_)));
}

bool Player::holdingGrenade() {
    return (dynamic_cast<Grenade*>(inventory_.at(equippedIndex_)));
}

GameObject* Player::throwEquipped() {
    inventory_.at(equippedIndex_)->unEquip(getPosition() + aimVector_ * (getRadius() + 5.f),
                                           aimVector_ * 100.f);
    auto throwed = inventory_.at(equippedIndex_);
    inventory_.erase(inventory_.begin() + equippedIndex_);
    equippedIndex_ %= inventory_.size();
    CHDistance_ = inventory_.at(equippedIndex_)->getCHDistance();
    return throwed;
}

GameObject* Player::throwGrenade() {
    inventory_.at(equippedIndex_)->unEquip(getPosition() + aimVector_ * (getRadius() + 5.f),
                                         aimVector_ * 500.f);
    auto throwed = inventory_.at(equippedIndex_);
    inventory_.erase(inventory_.begin() + equippedIndex_);
    equippedIndex_ %= inventory_.size();
    CHDistance_ = inventory_.at(equippedIndex_)->getCHDistance();
    return throwed;
}

bool Player::emptyInventory() {
  return inventory_.size();
}
