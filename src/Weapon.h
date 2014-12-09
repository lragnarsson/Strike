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
class Weapon{ //Automatic weapon
public:
    Weapon() = default;
    virtual ~Weapon() = default;
    Weapon(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize, int fireRate, int reloadTime, int Damage, float CHDistance);
    Weapon(const Weapon& weapon) = default;
    void reloadWeapon();
    virtual std::vector<Shot*> fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir);
    void hasNotFired();
    float getCHDistance();
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
    float CHDistance_;
    friend class SemiAutomaticWeapon;
    friend class Shotgun;
};

class SemiAutomaticWeapon : public Weapon {
public:
    SemiAutomaticWeapon() = default;
    ~SemiAutomaticWeapon() noexcept {}
    SemiAutomaticWeapon(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize, int fireRate, int reloadTime, int Damage, float CHDistance);
    virtual std::vector<Shot*> fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir) override;
private:
    friend class Shotgun;
};

class Shotgun : public SemiAutomaticWeapon {
public:
    Shotgun() = default;
    ~Shotgun() noexcept {};
    Shotgun(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize, int fireRate, int reloadTime, int Damage, int numberOfBullets, float CHDistance);
    std::vector<Shot*> fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir) override;
private:
    int numberOfBullets_;
};

#endif
