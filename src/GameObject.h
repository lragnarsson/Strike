#ifndef __Strike__GameObject__
#define __Strike__GameObject__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "./PhysicalObject.h"
#include "./Shot.h"

class GameObject : public sf::Sprite, public PhysicalCircle {
public:
  GameObject(sf::Texture* texture, sf::SoundBuffer* soundBuffer,
             sf::Vector2f position,float radius, float CHDistance);
    ~GameObject() noexcept {}

    void equip(int clientID);
    virtual void unEquip(sf::Vector2f position, sf::Vector2f velocity);
    void calculateMoveVector(float elpased);
    sf::Vector2f& getMoveVector();
    void move();
    virtual bool isStationary();
    bool isEquipped();
    float getCHDistance();
    void markForRemoval();
    bool isMarkedForRemoval();
    
protected:
    bool equipped_{false};
    int clientID_;
    sf::Vector2f moveVector_;
    sf::Vector2f currentVelocity_;
    float deceleration_{0.02f};
    float CHDistance_;
    bool markedForRemoval_{false};
    sf::SoundBuffer* soundBuffer_;
};

class Grenade : public GameObject {
public:
    Grenade(sf::Texture* texture, sf::SoundBuffer* soundBuffer,
            sf::Vector2f position, float radius, float CHDistance);
    ~Grenade() noexcept {}

    bool isStationary() override;
    std::vector<Shot*> explode();
    void unEquip(sf::Vector2f position, sf::Vector2f velocity) override;
    bool endOfFuse();

protected:
    sf::Clock fuse_;
    int fuseTime_{1000};
    bool triggered_;
    int shrapnelCount_{20};
    int shrapnelDamage_{50};
    float shrapnelDistance_{300.f};
    bool exploaded_{false};
};

#endif
