//
//  Player.h
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
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

class Player: public sf::Sprite {
 public:
  explicit Player(int ClientID);
  Player() = delete;
  ~Player() = default;

  // float getRotateSpeed() const;
  // void setHealth(float amount);
  int getClientID() const;
  void setWeapon(Weapon* weapon);
  std::vector<Shot*> fire();
    void setMoveVector(const sf::Vector2f& moveVector, float elapsedSeconds);
    void handleRotation(const sf::Vector2f& aimVector);
    void move(const sf::Vector2f& offset);
    void reloadWeapon();

 private:
    // virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Texture texture_;
    int clientID_;
    float speed_ = 100.0f;  // pixels per second
    Weapon* weapon_;
    sf::Vector2f moveVector_;
    sf::Vector2f aimVector_;
    float radConversion_ = 57.295779f;
};


#endif /* defined(__Strike__Player__) */
