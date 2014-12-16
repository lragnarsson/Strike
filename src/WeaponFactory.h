#ifndef _WEAPON_FACTORY_
#define _WEAPON_FACTORY_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "./Weapon.h"
#include "./GameObject.h"
#include "./Client.h"

class WeaponFactory {
public:
     WeaponFactory() {};
    ~WeaponFactory() = default;

    Weapon* createAK47(sf::Vector2f position) {
        return new Weapon(30, 60, 30, 120, 3000, 40, 600.f,
                          Client::textures_["ak47_placeholder.png"],
                          Client::soundBuffers_["ak47.wav"],
                          position, 20.f);
    }
    Weapon* createM4(sf::Vector2f position) {
        return new Weapon(30, 60, 30, 90, 3000, 30, 600.f,
                          Client::textures_["ak47_placeholder.png"],
                          Client::soundBuffers_["m4.wav"],
                          position, 20.f);
    }

    Weapon* createPPK(sf::Vector2f position) {
        return new SemiAutomaticWeapon(8, 24, 8, 150, 2000, 20, 200.f,
                          Client::textures_["glock_placeholder.png"],
                          Client::soundBuffers_["ppk.wav"],
                          position, 10.f);
    }

    Weapon* createNova(sf::Vector2f position) {
        return new Shotgun(6, 18, 6, 1800, 3000, 10, 8, 300.f,
                          Client::textures_["ak47_placeholder.png"],
                          Client::soundBuffers_["nova.wav"],
                          position, 20.f);
    }

    Grenade* createFrag(sf::Vector2f position) {
        return new Grenade(Client::textures_["grenade.gif"],
                           Client::soundBuffers_["grenade.wav"],
                           position, 10.f, 300.f);
    }
};

#endif // _WEAPON_FACTORY_
