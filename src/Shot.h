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


class Shot {
public:
    // Konstruktorer
    Shot() = default;
    Shot(int clientID, sf::Vector2f origin, sf::Vector2f direction, sf::Vector2f endPoint, int damage);
    Shot(const Shot& shot) = default;
    virtual ~Shot() = default;

    // Funktioner
    void draw() const;
    
protected:
private:
    // Datamedlemmar
    int timestamp_;
    int clientID_;
    sf::Vector2f origin_;
    sf::Vector2f direction_;
    sf::Vector2f endPoint_;
    int damage_;
};

#endif // SHOT_H
