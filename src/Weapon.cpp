//
//  Weapon.cpp
//  Strike
//
//  Created by Filip Östman on 2014-11-19.
//  Copyright (c) 2014 Filip Östman. All rights reserved.
//

#include "Weapon.h"
#include "Player.h"
#include <Transformable.hpp>

Weapon::Weapon(unsigned int newAmmo, unsigned int newAdditionalAmmo, unsigned int newMagazineSize, int newFireRate, int newReloadTime, int newDamage)
:ammo_(newAmmo), additionalAmmo_(newAdditionalAmmo), magazineSize_(newMagazineSize), fireRate_(newFireRate), reloadTime_(newReloadTime), damage_(newDamage) {}

Weapon::Weapon(const Weapon& weapon){
    ammo_ = weapon.ammo;
    additionalAmmo_ = weapon.additionalAmmo;
    magazineSize_ = weapon.magazineSize;
    fireRate_ = weapon.fireRate;
    reloadTime_ = weapon.reloadTime;
    damage_ = weapon.damage;
}

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
std::vector<Shot*> Weapon::fire(int clientID, sf::Vector2f& pos, sf::Vector2f& dir){
	std::vector<Shot*> shotVector;
	if(ammo_ > 0){
		ammo_ -= 1;
		std::cout << "Ammo: " << ammo_ << " AdditionalAmmo: " << additionalAmmo_ << endl;
		shotVector.push_back(Shot(clientID, pos, dir, pos + dir, damage_));
		return shotVector;
	}
	else{
		return shotVector;
	}

}