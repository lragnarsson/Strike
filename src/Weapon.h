//
//  Weapon.h
//  Strike
//
//  Created by Filip Östman on 2014-11-19.
//  Copyright (c) 2014 Filip Östman. All rights reserved.
//

#ifndef __Strike__Weapon__
#define __Strike__Weapon__

#include <stdio.h>
#include "Shot.h"
//Borde inte fire ta ett timestamp från clients lokala tid?
class Weapon{
public:
    Weapon() = default; // Add appropriate values later
    ~Weapon() = default;
    Weapon(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize, int fireRate, int reloadTime, int Damage);
    Weapon(const Weapon& weapon) = default;
    void reloadWeapon();
    std::vector<Shot*> fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir);
private:
    unsigned int ammo_;
    unsigned int additionalAmmo_;
    unsigned int magazineSize_;
    int fireRate_;
    int lastFired_;
    int damage_;
    //int lastReloaded; // Added a variable for controlling the reload process.
    int reloadTime_;
    bool isReloading_;
    sf::Clock clock_;
};

#endif
