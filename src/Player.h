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
<<<<<<< HEAD
#include "./Team.h"

class Player: public sf::Sprite, public PhysicalCircle {
public:
    Player(int ClientID); // Server only!
    explicit Player(int ClientID, Team* team, sf::Texture* spriteSheet);
=======
#include "./GameObject.h"

class Player: public sf::Sprite, public PhysicalCircle {
public:
    explicit Player(int ClientID, sf::Texture* spriteSheet);
>>>>>>> Started work on an inventory system, game objects and grenades.
    Player() = delete;
    ~Player() noexcept {};

    int getClientID() const;
<<<<<<< HEAD
    Team* getTeam() const;
    void setTeam(Team* team);
    std::string getClientName() const;
    void setClientName(std::string newName);
    void setWeapon(Weapon* weapon);
=======
    void addEquipment(GameObject* equipment);
>>>>>>> Started work on an inventory system, game objects and grenades.
    std::vector<Shot*> fire();
    sf::Vector2f& getMoveVector();
    void decreaseHealth(int amount);
    void setHealth(int health);
    void calculateMoveVector(const sf::Vector2f& moveVector,
                             float elapsedSeconds);
    void handleRotation(const sf::Vector2f& aimVector);
    void move();
    void reloadWeapon();
    void setSpeedMultiplier(float speed);
    void hasNotFired();

    void lastSeenNow();
    int getLastSeen();

    bool isDead();

    sf::CircleShape* getCrosshair();
    void animate();
    int getHealth(); //För testning!

<<<<<<< HEAD
=======
    bool holdingFirearm();
    bool holdingGrenade();
    GameObject* throwEquipped();
    GameObject* throwGrenade();
    bool emptyInventory();
    void equipAt(unsigned int index);
    void equipNext();
    void equipPrevious();

>>>>>>> Started work on an inventory system, game objects and grenades.
private:
    int health_ = 100;
    sf::Texture texture_;
    int clientID_;
    Team* team_;
    std::string clientName_;
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
