//
//  Shot.h
//  Strike
//
//  Created by Rasmus Vilhelmsson on 2014-11-20.
//  Copycopy (c) 2014 Rasmus Vilhelmsson. Alla rätter serverade.
//

#include "Shot.h"

Shot::Shot(int newClientID, sf::Vector2f newOrigin, sf::Vector2f newDirection,
           sf::Vector2f newEnd, int newDamage)
    : clientID_(newClientID), origin_(newOrigin), direction_(newDirection),
      endPoint_(newEnd), damage_(newDamage), ray_(Ray(newOrigin, newDirection)) {}

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
    return ray_;
}

void Shot::setTimestamp(sf::Time newTimeStamp) {
    timestamp_ = newTimeStamp.asMilliseconds();
}

sf::Time Shot::getTimestamp() const {
    return sf::Time {sf::milliseconds(timestamp_)};
}

void Shot::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Vertex line[] =
    {
        sf::Vertex(origin_),
        sf::Vertex(endPoint_)
    };

    target.draw(line, 2, sf::Lines); // makes use of the alternative draw function in RenderTarget
}
