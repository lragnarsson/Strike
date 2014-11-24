//
//  Shot.h
//  Strike
//
//  Created by Rasmus Vilhelmsson on 2014-11-20.
//  Copycopy (c) 2014 Rasmus Vilhelmsson. Alla rätter serverade.
//

#ifndef SHOT_H
#define SHOT_H

#define <Vector2.hpp>
#define <SFML/Graphics.hpp>

class Shot
{
    public:
        // Konstruktorer
        Shot() = default;
        Shot(int timestamp, int clientID, sf::vector2f origin, sf::vector2f direction, sf::vector2f endPoint, float damage);
        Shot(const Shot& shot);
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
        float damage_;
};

#endif // SHOT_H
