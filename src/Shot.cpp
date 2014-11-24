//
//  Shot.h
//  Strike
//
//  Created by Rasmus Vilhelmsson on 2014-11-20.
//  Copycopy (c) 2014 Rasmus Vilhelmsson. Alla rätter serverade.
//

#include "Shot.h"

Shot::Shot(int newTimestamp, int newClientID, sf::Vector2f newOrigin, sf::Vector2f newDirection, sf::Vector2f newEnd, float newDamage)
:timestamp(newTimestamp), clientID(newClientID), origin(newOrigin), direction(newDirection), endPoint(newEndPoint), damage(newDamage) {}

Shot::Shot(const Shot& shot){
    this->timestamp = shot.timestamp;
    this->clientID = shot.clientID;
    this->origin = shot.newOrigin;
    this->direction = shot.newDirection;
    this->endPoint = newEndPoint;
    this->damage = newDamage;
}
