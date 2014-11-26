//
//  Shot.h
//  Strike
//
//  Created by Rasmus Vilhelmsson on 2014-11-20.
//  Copycopy (c) 2014 Rasmus Vilhelmsson. Alla rätter serverade.
//

#include "Shot.h"

Shot::Shot(int newTimestamp, int newClientID, sf::Vector2f newOrigin, sf::Vector2f newDirection, sf::Vector2f newEnd, float newDamage):timestamp_(newTimestamp), clientID_(newClientID), origin_(newOrigin), direction_(newDirection), endPoint_(newEnd), damage_(newDamage) {}


