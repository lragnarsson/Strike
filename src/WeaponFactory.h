
#include <SFML/Graphics.hpp>
#include "./Weapon.h"
#include "./GameObject.h"
#include "./Client.h"

class WeaponFactory {
public:
    WeaponFactory() { Client::loadTextures(); }
    ~WeaponFactory() = default;

    Weapon* createAK47(sf::Vector2f position) {
        return new Weapon(30, 60, 30, 100, 5000, 40, 500.f,
                      Client::textures_["ak47_placeholder.png"],
                      position, 20.f);
    }

    Weapon* createGlock(sf::Vector2f position) {
        return new Weapon(20, 40, 20, 300, 3000, 20, 300.f,
                      Client::textures_["glock_placeholder.png"],
                      position, 10.f);
    }

    Grenade* createFrag(sf::Vector2f position) {
        return new Grenade(Client::textures_["grenade.gif"],
                           position, 10.f, 200.f);
    }
};
