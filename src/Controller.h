/***************************************
Controller.h

Controls the local player

Written by:
Lage Ragnarsson
Isak Wiberg
***************************************/

#ifndef _CONTROLLER_
#define _CONTROLLER_

#include "./Player.h"
#include "./Shot.h"

#include <math.h>
#include <vector>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Controller{
public:
    Controller();
    ~Controller();

    void handleKeyEvents(sf::RenderWindow*);
    void handlePlayerActions();
    void playerMove();
    void setPlayerRotation(const sf::RenderWindow&);
    void updatePlayerInputVector();

    void bindPlayer(Player* player);
    Player* getPlayer();
    sf::View* getView();
    void bindView(sf::View*);
    void updateView();
    std::vector<Shot*> playerFire();
    void reloadWeapon();
    void isSprinting();

private:
    sf::Vector2f inputVector_;
    Player* player_;
    sf::View* view_;
    sf::Clock clock_;
    float sqrt2 = 1.4142135;
};

#endif // _CONTROLLER_
