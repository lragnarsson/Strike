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
	if(additionalAmmo_ > 0){
		unsigned int allAmmo_ = ammo_ + additionalAmmo_;
		if(allAmmo_ >= magazineSize_)
		{
			ammo_ = magazineSize_;
			additionalAmmo_ = allAmmo_ - magazineSize_;
		}
		else
		{
			ammo_ = allAmmo_;
			additionalAmmo_ = 0;
		}
	}
}
std::vector<Shot*> Weapon::fire(int clientID, const sf::Vector2f& pos, const sf::Vector2f& dir){
	std::vector<Shot*> shotVector;
	if(ammo_ > 0){
		ammo_ -= 1;
        std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << std::endl;
        shotVector.push_back(new Shot{clientID, pos, dir, pos + dir, damage_});
		return shotVector;
	}
	else{
		return shotVector;
	}

}