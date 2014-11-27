#include "Controller.h"

#include <SFML/Window.hpp>
#include "Player.h"
#include <math.h>
#include <iostream>
#include <vector>

std::vector<Shot*> Controller::playerFire(){
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        return player_->fire();
    }
    else{
        std::vector<Shot*> shotVector;
        return shotVector;
    }
} 

void Controller::reloadWeapon(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        player_->reloadWeapon();
    }
}

Controller::~Controller(){
    view_ = nullptr;        // objects are destroyed by GameState
    player_ = nullptr;      // objects are destroyed by GameState
}

void Controller::updatePlayerMoveVector()
{

    moveVector_.x = 0;
    moveVector_.y = 0;

    sf::Time elapsed {clock_.getElapsedTime()};
    
    clock_.restart();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        moveVector_.y += -1;
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        moveVector_.y += 1;
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
      moveVector_.x += -1;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        moveVector_.x += 1;

    if (moveVector_.x != 0 && moveVector_.y != 0)
        moveVector_ /= sqrt2;
    
    player_->setMoveVector(moveVector_, elapsed.asSeconds());
    player_->move(sf::Vector2f{});

}

void Controller::playerRotate(const sf::RenderWindow& window)
{
    sf::Vector2i deltaMousePosition = lastMousePosition_ - sf::Mouse::getPosition(window); // The change in mouse position since last tick
    lastMousePosition_ = sf::Mouse::getPosition(window);
    player_->handleRotation(deltaMousePosition);
}

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
