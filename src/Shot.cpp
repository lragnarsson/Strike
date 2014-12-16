/***************************************
Shot.cpp

Class for representing shots.

Written by:
Filip Östman
Rasmus Vilhelmsson
***************************************/

#include "Shot.h"

Shot::Shot(int newClientID, sf::Vector2f newOrigin, sf::Vector2f newDirection,
           sf::Vector2f newEnd, int newDamage, sf::SoundBuffer* soundBuffer)
    : sf::Sound(*soundBuffer), clientID_(newClientID), origin_(newOrigin),
      direction_(newDirection), endPoint_(newEnd), damage_(newDamage) {}

Shot::Shot(int newClientID, sf::Vector2f newOrigin, sf::Vector2f newDirection,
           sf::Vector2f newEnd, int newDamage)
    : sf::Sound(), clientID_(newClientID), origin_(newOrigin),
      direction_(newDirection), endPoint_(newEnd), damage_(newDamage) {}

void Shot::setEndPoint(sf::Vector2f newEndPoint) {
    endPoint_ = newEndPoint;
}

sf::Vector2f Shot::getEndPoint() {
    return endPoint_;
}
sf::Vector2f Shot::getOrigin() const {
    return origin_;
}
sf::Vector2f Shot::getDirection() const {
    return direction_;
}

Ray Shot::getRay() const {
    return Ray {origin_,direction_};
}

int Shot::getDamage() {
    return damage_;
}

void Shot::setTimestamp(sf::Time newTimeStamp) {
    timestamp_ = newTimeStamp.asMilliseconds();
}

sf::Time Shot::getTimestamp() const {
    return sf::Time {sf::milliseconds(timestamp_)};
}

int Shot::getTargetID() {
    return targetID_;
}

int Shot::getClientID() const {
    return clientID_;
}

void Shot::setTargetID(int id) {
    targetID_ = id;
}

void Shot::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Vertex line[] =
    {
        sf::Vertex(origin_),
        sf::Vertex(endPoint_)
    };

    line[0].color = sf::Color::Green;
    line[1].color = sf::Color::Green;
    target.draw(line, 2, sf::Lines);
}

void Shot::play() {
    soundHasPlayed_ = true;
    Sound::play();
}

bool Shot::getSoundstatus() const {
    return soundHasPlayed_;
}

void Shot::setSoundstatus(bool status) {
    soundHasPlayed_ = status;
}
