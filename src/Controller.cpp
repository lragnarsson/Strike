#include "Controller.h"

#include <SFML/Window.hpp>
#include "Player.h"
#include <math.h>
#include <iostream>

void Controller::movePlayer()
{
    moveVector_.x = 0;
    moveVector_.y = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        moveVector_.y = -1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        moveVector_.y = 1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        moveVector_.x = -1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        moveVector_.x = 1;

    if (moveVector_.x != 0 || moveVector_.y != 0)
    {
        moveVector_ = moveVector_ / sqrtf(powf(moveVector_.x, 2) + powf(moveVector_.y, 2));
        player_->move(moveVector_ * player_->getSpeed());
    }
}

void Controller::rotatePlayer(const sf::Window& window)
{
    sf::Vector2f aim {sf::Mouse::getPosition(window)}; // this gives the mouse pos relative to the window
    aim -= player_->getPosition();
    if (aim.x != 0 || aim.y != 0) // normalize the aimvector, don't rotate if strange length.
    {
        aim = aim / sqrtf(powf(aim.x, 2) + powf(aim.y, 2));
        float newAngle = (aim.y > 0) ? 57.3f * acos(aim.x) : 360 - 57.3f * acos(aim.x);
        player_->setRotation(newAngle);
        std::cout<< "(x, y, angle, mouseAngle): ("<< player_->getPosition().x << ", " << player_->getPosition().y << ", " << player_->getRotation() << ", " << newAngle << ")" << std::endl;
        
    }
    
}


void Controller::bindPlayer(Player* p)
{
    player_ = p;
}
