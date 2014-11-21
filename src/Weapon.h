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
//Borde inte fire ta ett timestamp från clients lokala tid?
class Weapon{
public:
    Weapon() = default; // Add appropriate values later
    ~Weapon() = default;
    Weapon(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize, int fireRate, int reloadTime);
    Weapon(const Weapon& weapon);
    void reloadWeapon();
private:
    unsigned int ammo;
    unsigned int additionalAmmo;
    unsigned int magazineSize;
    int fireRate;
    int lastFired;
    //int lastReloaded; // Added a variable for controlling the reload process.
    int reloadTime;
    bool isReloading;
};

#endif
