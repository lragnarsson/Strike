
#include <SFML/Graphics.hpp>
#include "./Weapon.h"
#include "./Client.h"

class WeaponFactory {
public:
    WeaponFactory() { Client::loadTextures(); }
    ~WeaponFactory() = default;

    Weapon* createAK47() {
        return new Weapon(30, 60, 30, 100, 5000, 40, 500.f,
                        Client::getTexturePtr("ak47_placeholder.png"),
                        sf::Vector2f(), 20.f);
    }
    Weapon* createGlock() {
        return new Weapon(20, 40, 20, 300, 3000, 20, 300.f,
                        Client::getTexturePtr("glock_placeholder.png"),
                        sf::Vector2f(), 10.f);
    }
};
