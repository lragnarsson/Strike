#include "./GameObject.h"
#include <vector>
#include "./Shot.h"
#include "./GeomUtils.h"

// GameObject
GameObject::GameObject(sf::Texture* texture, sf::Vector2f position, float radius, float CHDistance)
    : sf::Sprite(*texture), PhysicalCircle(position, radius), CHDistance_(CHDistance) {
    setPosition(position);
    setOrigin(radius, radius);
}

void GameObject::equip(int clientID) {
    equipped_ = true;
    clientID_ = clientID;
}

void GameObject::unEquip(sf::Vector2f position, sf::Vector2f velocity) {
    setPosition(position);
    currentVelocity_ = velocity;
    equipped_ = false;
}

void GameObject::calculateMoveVector(const sf::Vector2f& moveVector, float elapsedSeconds) {
    currentVelocity_ *= deceleration_ * elapsedSeconds;
    if (length(currentVelocity_) < 1)
        currentVelocity_ *= 0.f;
    moveVector_ = currentVelocity_ * elapsedSeconds;
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
Grenade::Grenade(sf::Texture* texture, sf::Vector2f position, float radius, float CHDistance)
    : GameObject(texture, position, radius, CHDistance) {}

void Grenade::unEquip(sf::Vector2f position, sf::Vector2f velocity) {
    GameObject::unEquip(position, velocity);
    if (length(velocity) > 150.f) {
        triggered_ = true;
        fuse_.restart();
    }
}

bool Grenade::isStationary() {
  return (exploaded_ || GameObject::isStationary() && !triggered_);
}

bool Grenade::endOfFuse() {
  return (triggered_ && fuse_.getElapsedTime().asMilliseconds() >= fuseTime_);
}

std::vector<Shot*> Grenade::explode() {
    exploaded_ = true;
    std::vector<Shot*> shrapnel;
    sf::Vector2f dir;
    for (int i = 0; i < shrapnelCount_; i++) {
        dir = normalize(sf::Vector2f(std::rand() % 100, std::rand() % 100));
        shrapnel.push_back(new Shot(clientID_, getPosition(), dir,
                                    getPosition() + dir * shrapnelDistance_, shrapnelDamage_));
    }
    return shrapnel;
}
