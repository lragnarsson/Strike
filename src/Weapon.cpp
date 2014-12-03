//
//  Weapon.cpp
//  Strike
//
//  Created by Filip Östman on 2014-11-19.
//  Copyright (c) 2014 Filip Östman. All rights reserved.
//

#include "Weapon.h"
#include <iostream>

Weapon::Weapon(unsigned int newAmmo, unsigned int newAdditionalAmmo, unsigned int newMagazineSize, int newFireRate, int newReloadTime, int newDamage)
:ammo_(newAmmo), additionalAmmo_(newAdditionalAmmo), magazineSize_(newMagazineSize), fireRate_(newFireRate), reloadTime_(newReloadTime), damage_(newDamage) {}


//At the moment reloadWeapon does not handle time
void Weapon::reloadWeapon(){
	if(ammo_ != magazineSize_)
	{
		if(additionalAmmo_ > 0){
				unsigned int allAmmo_ = ammo_ + additionalAmmo_;
				isReloading_ = true;
				clock_.restart();
			if(allAmmo_ >= magazineSize_)
			{
				ammo_ = magazineSize_;
				additionalAmmo_ = allAmmo_ - magazineSize_;
				std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << std::endl;
			}
			else
			{
				ammo_ = allAmmo_;
				additionalAmmo_ = 0;
				std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << std::endl;
			}
		}
	}
}

std::vector<Shot*> Weapon::fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir){
	std::vector<Shot*> shotVector;
	if(isReloading_){
		if(clock_.getElapsedTime().asMilliseconds() >= reloadTime_){
			isReloading_ = false;
		}
		else {
			return shotVector;
		}
	}
	if(ammo_ > 0 && clock_.getElapsedTime().asMilliseconds() >= fireRate_){
		ammo_ -= 1;
		clock_.restart();
		hasFired_ = true;
        std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << std::endl;
        shotVector.push_back(new Shot{clientID, pos, dir, pos + dir, damage_});
		return shotVector;
	}
	else{
		return shotVector;
	}

}

void Weapon::hasNotFired() {
	hasFired_ = false;
}

SemiAutomaticWeapon::SemiAutomaticWeapon(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize, int fireRate, int reloadTime, int Damage)
	: Weapon{ammo, additionalAmmo, magazineSize, fireRate, reloadTime, Damage} {}

std::vector<Shot*> SemiAutomaticWeapon::fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir) {
	std::vector<Shot*> shotVector;
	if(isReloading_){
		if(clock_.getElapsedTime().asMilliseconds() >= reloadTime_){
			isReloading_ = false;
		}
		else{
			return shotVector;
		}
	}
	if(ammo_ > 0 && clock_.getElapsedTime().asMilliseconds() >= fireRate_ && hasFired_ == false){
		ammo_ -= 1;
		clock_.restart();
		hasFired_ = true;
        std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << std::endl;
        shotVector.push_back(new Shot{clientID, pos, dir, pos + dir, damage_});
		return shotVector;
	}
	else{
		return shotVector;
	}
}

Shotgun::Shotgun(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize, int fireRate, int reloadTime, int Damage, int numberOfBullets)
	: SemiAutomaticWeapon{ammo, additionalAmmo, magazineSize, fireRate, reloadTime, Damage}, numberOfBullets_{numberOfBullets} {}

std::vector<Shot*> Shotgun::fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir) {
	std::vector<Shot*> shotVector;
	if(isReloading_){
		if(clock_.getElapsedTime().asMilliseconds() >= reloadTime_){
			isReloading_ = false;
		}
		else{
			return shotVector;
		}
	}
	if(ammo_ > 0 && clock_.getElapsedTime().asMilliseconds() >= fireRate_ && hasFired_ == false){
		ammo_ -= 1;
		clock_.restart();
		hasFired_ = true;
        std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << std::endl;
        for(int i=1; i<=numberOfBullets_; i++) {
        	sf::Vector2f randomVector;
        	randomVector.x = -20 + (std::rand() % 41) + dir.x*100;
        	randomVector.y = -20 + (std::rand() % 41) + dir.y*100;

        	shotVector.push_back(new Shot{clientID, pos, randomVector, pos + randomVector, damage_});
	     
        }
 		return shotVector;          

	}
	else{
		return shotVector;
	}
}