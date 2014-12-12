//
//  Shot.h
//  Strike
//
//  Created by Rasmus Vilhelmsson on 2014-11-20.
//  Copycopy (c) 2014 Rasmus Vilhelmsson. Alla rätter serverade.
//

#ifndef SHOT_H
#define SHOT_H

#include <SFML/Graphics.hpp>
#include "./GeomUtils.h"


class Shot: public sf::Drawable {
public:
    // Konstruktorer
    Shot() = default;
    Shot(int clientID, sf::Vector2f origin, sf::Vector2f direction, sf::Vector2f endPoint, int damage);
    Shot(int clientID, Ray ray_, sf::Vector2f endPoint, int damage);
    Shot(const Shot& shot) = default;
    virtual ~Shot() = default;

    // Funktioner

    void setEndPoint(sf::Vector2f);
    sf::Vector2f getEndPoint();
    void setTimestamp(sf::Time);
    sf::Time getTimestamp() const;
    sf::Vector2f getOrigin() const;
    sf::Vector2f getDirection() const;
    Ray getRay() const;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    // Datamedlemmar
    int timestamp_;  // in milliseconds
    int clientID_;
    sf::Vector2f origin_;
    sf::Vector2f direction_;
    sf::Vector2f endPoint_;
    int damage_;
};

#endif // SHOT_H
