#include "Controller.h"

#include <SFML/Window.hpp>
#include "Player.h"
#include <math.h>
#include <iostream>

void Controller::movePlayer(const sf::RenderWindow& window)
{
    sf::Vector2i mouse {sf::Mouse::getPosition(window)}; // this gives the mouse pos relative to the window
    sf::Vector2f aim {window.mapPixelToCoords(mouse) - view_->getCenter()};
    if (aim.x != 0 || aim.y != 0) // normalize the aimvector, don't rotate if strange length.
    {
        // debug
        std::cout<< "(x, y, aimx, aimy): ("<< player_->getPosition().x << ", " << player_->getPosition().y << ", " << aim.x << ", " << aim.y << ")" << std::endl;
        aim = aim / sqrtf(powf(aim.x, 2) + powf(aim.y, 2));
        float newAngle = (aim.y > 0) ? 57.3f * acos(aim.x) : 360 - 57.3f * acos(aim.x);
        player_->setRotation(newAngle);
        
        
        
    }
    moveVector_.x = 0;
    moveVector_.y = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        moveVector_ = aim;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        moveVector_ = -aim;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        moveVector_.x = aim.y;
        moveVector_.y = -aim.x;

    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        moveVector_.x = -aim.y;
        moveVector_.y = aim.x;
    }
    if (moveVector_.x != 0 || moveVector_.y != 0)
    {
        moveVector_ = moveVector_ / sqrtf(powf(moveVector_.x, 2) + powf(moveVector_.y, 2));
        player_->move(moveVector_ * player_->getSpeed());
    }
}
/*
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
    
}*/

void Controller::updateView()
{
    view_->setCenter(player_->getPosition());
    
}


void Controller::bindPlayer(Player* p)
{
    player_ = p;
}

void Controller::bindView(sf::View* v)
{
    view_ = v;
}
