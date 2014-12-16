#include "./GameObject.h"
#include <vector>
#include "./Shot.h"
#include "./GeomUtils.h"
#include <iostream>

// GameObject
GameObject::GameObject(sf::Texture* texture, sf::SoundBuffer* soundBuffer,
                       sf::Vector2f position, float radius, float CHDistance, std::string name)
    : sf::Sprite(*texture), PhysicalCircle(position, radius),
      CHDistance_(CHDistance), soundBuffer_(soundBuffer), weaponName_(name) {
    setPosition(position);
    setOrigin(radius, radius);
}

void GameObject::equip(int clientID) {
    equipped_ = true;
    clientID_ = clientID;
}

void GameObject::unEquip(sf::Vector2f position, sf::Vector2f velocity) {
    setPosition(position);
    moveVector_ = velocity;
    markedForRemoval_ = false;
    equipped_ = false;
}

bool GameObject::isEquipped() {
    return equipped_;
}
void GameObject::markForRemoval() {
    markedForRemoval_ = true;
}

bool GameObject::isMarkedForRemoval() {
    return markedForRemoval_;
}

void GameObject::calculateMoveVector(float elapsed) {
  moveVector_ *= std::pow(deceleration_, elapsed/100);
    if (length(moveVector_) < 1)
        moveVector_ *= 0.f;
}

sf::Vector2f& GameObject::getMoveVector() {
    return moveVector_;
}

void GameObject::move() {
    Sprite::move(moveVector_);
    PhysicalCircle::setCenter(getPosition());
}

bool GameObject::isStationary() {
    return (length(moveVector_) == 0);
}

float GameObject::getCHDistance() {
    return CHDistance_;
}

// Grenade
Grenade::Grenade(sf::Texture* texture, sf::SoundBuffer* soundBuffer,
                 sf::Vector2f position, float radius, float CHDistance, std::string name)
    : GameObject(texture, soundBuffer, position, radius, CHDistance, name) {}

std::string GameObject::getName() {
    return weaponName_;
}

void Grenade::unEquip(sf::Vector2f position, sf::Vector2f velocity) {
    GameObject::unEquip(position, velocity);
    if (length(velocity) > 100.f) {
        triggered_ = true;
        fuse_.restart();
    }
}

bool Grenade::isStationary() {
  return (exploaded_ || (GameObject::isStationary() && !triggered_));
}

bool Grenade::endOfFuse() {
  return (triggered_ && fuse_.getElapsedTime().asMilliseconds() >= fuseTime_);
}

std::vector<Shot*> Grenade::explode() {
    exploaded_ = true;
    markedForRemoval_ = true;
    std::vector<Shot*> shrapnel;
    sf::Vector2f dir;
    for (int i = 0; i < shrapnelCount_; i++) {
        dir = normalize(sf::Vector2f(std::rand() % 100 - 50, std::rand() % 100 - 50));
        shrapnel.push_back(new Shot(clientID_, getPosition(), dir,
                                    getPosition() + dir * shrapnelDistance_, shrapnelDamage_,
                                    soundBuffer_));
    }
    return shrapnel;
}

