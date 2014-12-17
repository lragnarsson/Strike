/***************************************
Weapon.cpp

Polymorph class structure representing different weapons and types.

Written by:
Filip Östman
Lage Ragnarsson
***************************************/

#include "./Weapon.h"
#include <iostream>

Weapon::Weapon(unsigned int newAmmo, unsigned int newAdditionalAmmo,
               unsigned int newMagazineSize, int newFireRate,
               int newReloadTime, int newDamage, float newCHDistance,
               sf::Texture* texture, sf::SoundBuffer* soundBuffer,
               sf::Vector2f position, float radius, std::string name,
               float viewDistanceMultiplier)
    : GameObject(texture, soundBuffer, position, radius, newCHDistance, name,
                 viewDistanceMultiplier), ammo_(newAmmo),
      additionalAmmo_(newAdditionalAmmo), magazineSize_(newMagazineSize),
      fireRate_(newFireRate), reloadTime_(newReloadTime), damage_(newDamage) {}

void Weapon::reloadWeapon() {
    if (ammo_ != magazineSize_) {
        if (additionalAmmo_ > 0) {
            unsigned int allAmmo_ = ammo_ + additionalAmmo_;
            isReloading_ = true;
            clock_.restart();
            if (allAmmo_ >= magazineSize_) {
                ammo_ = magazineSize_;
                additionalAmmo_ = allAmmo_ - magazineSize_;
            }
            else {
              ammo_ = allAmmo_;
              additionalAmmo_ = 0;
            }
        }
    }
}
/*
std::string Weapon::getName() override {
    return weaponName_;
}
*/
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
        if (clock_.getElapsedTime().asMilliseconds() >= 2 * fireRate_)
          sprayMultiplier_ = 0.0f;
        else
            sprayMultiplier_ = ((float)fireRate_ / (float)clock_.getElapsedTime().asMilliseconds()) * sprayMultiplier_ * 1000.0f;

        clock_.restart();
        animTimer_.restart();
        hasFired_ = true;
        sf::Vector2f randomVector;
        randomVector.x = (-20 + (std::rand() % 41) + dir.x*100) * sprayMultiplier_;
        randomVector.y = (-20 + (std::rand() % 41) + dir.y*100) * sprayMultiplier_;
        shotVector.push_back(new Shot{clientID, pos, dir + randomVector,
                                      pos + dir * 1000.f + randomVector, damage_, soundBuffer_});
        sprayMultiplier_ += 20.0f;
        return shotVector;
    } else {
        return shotVector;
    }
}


void Weapon::hasNotFired() {
    hasFired_ = false;
}

float Weapon::getCHDistance() const {
    return CHDistance_;
}

int Weapon::getMagazineAmmo() const {
    return ammo_;
}

int Weapon::getAdditionalAmmo() const {
    return additionalAmmo_;
}

bool Weapon::isAnimating() {
  return animTimer_.getElapsedTime().asMilliseconds() < fireAnimationTime_;
}

SemiAutomaticWeapon::SemiAutomaticWeapon(unsigned int ammo, unsigned int additionalAmmo,
                                         unsigned int magazineSize, int fireRate,
                                         int reloadTime, int Damage, float CHDistance,
                                         sf::Texture* texture, sf::SoundBuffer* soundBuffer,
                                         sf::Vector2f position, float radius, std::string name,
                                         float viewDistanceMultiplier)
    : Weapon(ammo, additionalAmmo, magazineSize, fireRate, reloadTime,
             Damage, CHDistance, texture, soundBuffer, position, radius, name,
             viewDistanceMultiplier) {}

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
        if (clock_.getElapsedTime().asMilliseconds() >= 2 * fireRate_)
          sprayMultiplier_ = 0.0f;
        else
            sprayMultiplier_ = ((float)fireRate_ / (float)clock_.getElapsedTime().asMilliseconds()) * sprayMultiplier_;

        ammo_ -= 1;
        clock_.restart();
        hasFired_ = true;
        sf::Vector2f randomVector;
        randomVector.x = (-20 + (std::rand() % 41) + dir.x*100) * sprayMultiplier_;
        randomVector.y = (-20 + (std::rand() % 41) + dir.y*100) * sprayMultiplier_;
        shotVector.push_back(new Shot{clientID, pos, dir + randomVector, pos + 1000.f * dir + randomVector,
                                      damage_, soundBuffer_});
        sprayMultiplier_ += 20.0f;
        return shotVector;
    } else {
        return shotVector;
    }
}

Shotgun::Shotgun(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize,
                 int fireRate, int reloadTime, int Damage, int numberOfBullets, float CHDistance,
                 sf::Texture* texture, sf::SoundBuffer* soundBuffer,
                 sf::Vector2f position, float radius, std::string name,
                 float viewDistanceMultiplier)
    : SemiAutomaticWeapon(ammo, additionalAmmo, magazineSize, fireRate, reloadTime,
                          Damage, CHDistance, texture, soundBuffer, position, radius, name,
                          viewDistanceMultiplier),
      numberOfBullets_{numberOfBullets} {}

std::vector<Shot*> Shotgun::fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir) {
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
        for (int i=1; i<=numberOfBullets_; i++) {
            sf::Vector2f randomVector;
            randomVector.x = -20 + (std::rand() % 41) + dir.x*100;
            randomVector.y = -20 + (std::rand() % 41) + dir.y*100;

            shotVector.push_back(new Shot{clientID, pos, randomVector,
                                          pos + randomVector * 10000.0f, damage_, soundBuffer_});
        }
        return shotVector;
    } else {
      return shotVector;
    }
}
