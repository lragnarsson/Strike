//
//  Weapon.cpp
//  Strike
//
//  Created by Filip Östman on 2014-11-19.
//  Copyright (c) 2014 Filip Östman. All rights reserved.
//

#include "Weapon.h"

Weapon::Weapon(unsigned int newAmmo, unsigned int newAdditionalAmmo, unsigned int newMagazineSize, int newFireRate, int newReloadTime)
:ammo(newAmmo), additionalAmmo(newAdditionalAmmo), magazineSize(newMagazineSize), fireRate(newFireRate), reloadTime(newReloadTime) {}

Weapon::Weapon(const Weapon& weapon){
    this->ammo = weapon.ammo;
    this->additionalAmmo = weapon.additionalAmmo;
    this->magazineSize = weapon.magazineSize;
    this->fireRate = weapon.fireRate;
    this->reloadTime = weapon.reloadTime;
}

//At the moment reloadWeapon does not handle time
void Weapon::reloadWeapon(){
	if(this->additionalAmmo > 0){
		unsigned int allAmmo = this->ammo + this->additionalAmmo;
		if(allAmmo >= this->magazineSize)
		{
			this->ammo = this->magazineSize;
			this->additionalAmmo = allAmmo - this->magazineSize;
		}
		else
		{
			this->ammo = allAmmo;
			this->additionalAmmo = 0;
		}
	}
}