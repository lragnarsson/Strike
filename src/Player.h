//
//  Player.h
//  Strike
//

#ifndef __Strike__Player__
#define __Strike__Player__

#include <math.h>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <vector>
#include <iostream>
#include "./Weapon.h"
#include "./ResourcePath.h"
#include "./PhysicalObject.h"
#include "./GameObject.h"

class Player: public sf::Sprite, public PhysicalCircle {
public:
    explicit Player(int ClientID, sf::Texture* spriteSheet);
    Player() = delete;
    ~Player() noexcept {};

    int getClientID() const;
    void addEquipment(GameObject* equipment);
    std::vector<Shot*> fire();
    sf::Vector2f& getMoveVector();
    void setHealth(int amount);
    void calculateMoveVector(const sf::Vector2f& moveVector,
                             float elapsedSeconds);
    void handleRotation(const sf::Vector2f& aimVector);
    void move();
    void reloadWeapon();
    void setSpeedMultiplier(float speed);
    void hasNotFired();

    void lastSeenNow();
    int getLastSeen();

    sf::CircleShape* getCrosshair();
    void animate();
    int getHealth(); //För testning!

    bool holdingFirearm();
    bool holdingGrenade();
    GameObject* throwEquipped();
    GameObject* throwGrenade();
    bool emptyInventory();
    void equipAt(unsigned int index);
    void equipNext();
    void equipPrevious();

private:
    int health_ = 100;
    sf::Texture texture_;
    int clientID_;
    float speedMultiplier_ = 1.0f;
    float maxSpeed_ = 400.0f;  // pixels per second
    float acceleration_ = 3000.0f;  // pixels per second^2
    sf::Clock lastSeen;

    std::vector<GameObject*> inventory_;
    int equippedIndex_{0};
    int inventorySize_{5};

    sf::Vector2f moveVector_;
    sf::Vector2f curSpeed_;
    sf::Vector2f aimVector_;
    float radConversion_ = 57.2957795f;
    sf::CircleShape crosshair_;

    unsigned int frameTime_{10};
    unsigned int currentFrame_{0};
    unsigned int currentRow_{0};
    unsigned int frameWidth_{160};
    unsigned int frameHeight_{160};
    unsigned int columns_{10};
    sf::IntRect frameRect_;
    sf::Clock animClock_;
    sf::Texture spriteSheet_;
    float CHDistance_;

    bool inFireAnimation();
    void initCrosshair();
    void initAnimation(sf::Texture* texture);
};

#endif /* defined(__Strike__Player__) */
