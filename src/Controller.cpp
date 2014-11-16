#include "Controller.hpp"

#include <SFML/Window.hpp>
#include "Player.h"

void Controller::movePlayer()
{
    moveVector_.x = 0;
    moveVector_.y = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        moveVector_.y = player_->getSpeed();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        moveVector_.y = -(player_->getSpeed());

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        moveVector_.x = -(player_->getSpeed());

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        moveVector_.x = -(player_->getSpeed());

    player_->move(moveVector_);
}

void Controller::bindPlayer(Player* p)
{
    player_ = p;
}
