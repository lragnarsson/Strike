//
//  Weapon.cpp
//  Strike
//
//  Created by Filip �stman on 2014-11-19.
//  Copyright (c) 2014 Filip �stman. All rights reserved.
//

#include "Weapon.h"
#include <iostream>

Weapon::Weapon(unsigned int newAmmo, unsigned int newAdditionalAmmo,
               unsigned int newMagazineSize, int newFireRate,
               int newReloadTime, int newDamage, float newCHDistance)
    : ammo_(newAmmo), additionalAmmo_(newAdditionalAmmo),
      magazineSize_(newMagazineSize), fireRate_(newFireRate),
      reloadTime_(newReloadTime), damage_(newDamage), CHDistance_(newCHDistance) {}

void Weapon::reloadWeapon() {
    if (ammo_ != magazineSize_) {
        if (additionalAmmo_ > 0) {
            unsigned int allAmmo_ = ammo_ + additionalAmmo_;
            isReloading_ = true;
            clock_.restart();
            if (allAmmo_ >= magazineSize_) {
                ammo_ = magazineSize_;
                additionalAmmo_ = allAmmo_ - magazineSize_;
                std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << std::endl;
            } 
            else {
              ammo_ = allAmmo_;
              additionalAmmo_ = 0;
              std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << std::endl;
            }
        }
    }
}

std::vector<Shot*> Weapon::fire(int clientID, const sf::Vector2f& pos,
                                const sf::Vector2f& dir) {
    std::vector<Shot*> shotVector;
    if (isReloading_) {
        if (clock_.getElapsedTime().asMilliseconds() >= reloadTime_)
            isReloading_ = false;
        else
            return shotVector;
    }
    if (ammo_ > 0 && clock_.getElapsedTime().asMilliseconds() >= fireRate_) {
        ammo_ -= 1;
        if(clock_.getElapsedTime().asMilliseconds() >= 100 * fireRate_) {
        	sprayMultiplier_ = 0.0f;
        }
        else {
            sprayMultiplier_ = ((float)fireRate_ / (float)clock_.getElapsedTime().asMilliseconds()) * sprayMultiplier_;
        }
        clock_.restart();
        hasFired_ = true;
        sf::Vector2f randomVector;
        randomVector.x = (-20 + (std::rand() % 41) + dir.x*100) * sprayMultiplier_;
        randomVector.y = (-20 + (std::rand() % 41) + dir.y*100) * sprayMultiplier_;
        std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << std::endl;
        shotVector.push_back(new Shot{clientID, pos, dir + randomVector, pos + dir * 10000.f + randomVector, damage_});
        sprayMultiplier_ += 20.0f;
        return shotVector;
    } else {
      return shotVector;
    }
}

void Weapon::hasNotFired() {
    hasFired_ = false;
}

float Weapon::getCHDistance() {
    return CHDistance_;
}

SemiAutomaticWeapon::SemiAutomaticWeapon(unsigned int ammo, unsigned int additionalAmmo,
                                         unsigned int magazineSize, int fireRate,
                                         int reloadTime, int Damage, float CHDistance)
    : Weapon{ammo, additionalAmmo, magazineSize, fireRate, reloadTime, Damage, CHDistance} {}

std::vector<Shot*> SemiAutomaticWeapon::fire(int clientID, const sf::Vector2f& pos,
                                             const sf::Vector2f& dir) {
    std::vector<Shot*> shotVector;
    if (isReloading_) {
        if (clock_.getElapsedTime().asMilliseconds() >= reloadTime_)
            isReloading_ = false;
        else
            return shotVector;
    }
    if (ammo_ > 0 && clock_.getElapsedTime().asMilliseconds() >= fireRate_ && hasFired_ == false) {
        ammo_ -= 1;
        clock_.restart();
        hasFired_ = true;
        std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << std::endl;
        shotVector.push_back(new Shot{clientID, pos, dir, pos + dir * 10000.f, damage_});
        return shotVector;
    } else {
        return shotVector;
    }
}

Shotgun::Shotgun(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize,
                 int fireRate, int reloadTime, int Damage, int numberOfBullets, float CHDistance)
    : SemiAutomaticWeapon{ammo, additionalAmmo, magazineSize, fireRate, reloadTime, Damage, CHDistance},numberOfBullets_{numberOfBullets} {}

std::vector<Shot*> Shotgun::fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir) {
    std::vector<Shot*> shotVector;
    if (isReloading_) {
        if (clock_.getElapsedTime().asMilliseconds() >= reloadTime_)
            isReloading_ = false;
        else
            return shotVector;
    }
    if(ammo_ > 0 && clock_.getElapsedTime().asMilliseconds() >= fireRate_ && hasFired_ == false) {
        ammo_ -= 1;
        clock_.restart();
        hasFired_ = true;
        std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << std::endl;
        for (int i=1; i<=numberOfBullets_; i++) {
            sf::Vector2f randomVector;
            randomVector.x = -20 + (std::rand() % 41) + dir.x*100;
            randomVector.y = -20 + (std::rand() % 41) + dir.y*100;

            shotVector.push_back(new Shot{clientID, pos, randomVector, pos + randomVector * 10000.f, damage_}); 
        }
        return shotVector;
    } else {
      return shotVector;
    }
}
