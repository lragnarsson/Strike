//
//  Weapon.h
//  Strike
//
//  Created by Filip �stman on 2014-11-19.
//  Copyright (c) 2014 Filip �stman. All rights reserved.
//

#ifndef __Strike__Weapon__
#define __Strike__Weapon__

#include <stdio.h>
#include "Shot.h"
class Weapon{ //Automatic weapon
public:
    Weapon() = default;
    virtual ~Weapon() = default;
    Weapon(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize, int fireRate, int reloadTime, int Damage);
    Weapon(const Weapon& weapon) = default;
    void reloadWeapon();
    virtual std::vector<Shot*> fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir);
    void hasNotFired();
private:
    unsigned int ammo_;
    unsigned int additionalAmmo_;
    unsigned int magazineSize_;
    int fireRate_;
    int lastFired_;
    int damage_;
    int reloadTime_;
    bool isReloading_;
    sf::Clock clock_;
    bool hasFired_;
    friend class SemiAutomaticWeapon;
    friend class Shotgun;
};

class SemiAutomaticWeapon : public Weapon {
public:
    SemiAutomaticWeapon() = default;
    ~SemiAutomaticWeapon() = default;
    SemiAutomaticWeapon(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize, int fireRate, int reloadTime, int Damage);
    virtual std::vector<Shot*> fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir) override;
private:
    friend class Shotgun;
};

class Shotgun : public SemiAutomaticWeapon {
public:
    Shotgun() = default;
    ~Shotgun() = default;
    Shotgun(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize, int fireRate, int reloadTime, int Damage, int numberOfBullets);
    std::vector<Shot*> fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir) override;
private:
    int numberOfBullets_;
};

#endif
