#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
#include "./Player.h"
#include "./Shot.h"

class Controller{
public:
    Controller();
    ~Controller();
    void handleKeyEvents(sf::RenderWindow*);
    void handlePlayerActions();
    void setPlayerInputVector();
    void playerMove();
    void setPlayerRotation(const sf::RenderWindow&);
    void bindPlayer(Player*);
    Player* getPlayer();
    sf::View* getView();
    void bindView(sf::View*);
    void updateView();
    std::vector<Shot*> playerFire();
    void reloadWeapon();
protected:

private:
    sf::Vector2f inputVector_;
    Player* player_;
    sf::View* view_;
    sf::Clock clock_;
    float sqrt2{1.4142135};

};

#endif // CONTROLLER_H
