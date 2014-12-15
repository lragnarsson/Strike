/***************************************
Controller.cpp

Controls the local player

Written by:
Lage Ragnarsson
Isak Wiberg
***************************************/

#include "./Controller.h"

#include <iostream>
#include <vector>

Controller::Controller() {
  view_ = new sf::View(sf::FloatRect(0, 0, 2560, 1440));
}

std::vector<Shot*> Controller::playerFire() {
    std::vector<Shot*> shotVector;
    if (!player_->holdingFirearm())
        return shotVector;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return player_->fire();
    player_->hasNotFired();
    return shotVector;
}

GameObject* Controller::playerThrow() {
  if (dropTimer_.getElapsedTime().asMilliseconds() > 500) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && !player_->emptyInventory()) {
          dropTimer_.restart();
          return player_->throwEquipped();
      }
      else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player_->holdingGrenade()) {
          dropTimer_.restart();
          return player_->throwGrenade();
      }
  }
  return nullptr;
}

Controller::~Controller() {
    delete view_;
    view_ = nullptr;
    player_ = nullptr;
}

void Controller::handleKeyEvents(sf::RenderWindow* window) {
    sf::Event event;
    while (window->pollEvent(event)) {
        // Close window : exit
        if (event.type == sf::Event::Closed)
            window->close();

        // Escape pressed : exit
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Escape)
            window->close();
    }
}

void Controller::handlePlayerActions() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        player_->reloadWeapon();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
        player_->setSpeedMultiplier(2.0f);
    else
        player_->setSpeedMultiplier(1.0f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
      player_->equipAt(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
      player_->equipAt(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
      player_->equipAt(2);
}

void Controller::pickupObjects(std::vector<GameObject*>* gameObjects) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
      for (auto gameObject : *gameObjects) {
          sf::Vector2f tmp = gameObject->getPosition() - player_->getPosition();
          if (dot(tmp, tmp) < 10000.f) {
              player_->pickUpObject(gameObject);
              return;
          }
      }
}

void Controller::updatePlayerInputVector() {
    inputVector_.x = 0;
    inputVector_.y = 0;

    sf::Time elapsed {clock_.getElapsedTime()};

    clock_.restart();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        inputVector_.y += -1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        inputVector_.y += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        inputVector_.x += -1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        inputVector_.x += 1;

    if (inputVector_.x != 0 && inputVector_.y != 0)
        inputVector_ /= sqrt2;

    player_->calculateMoveVector(inputVector_, elapsed.asSeconds());
}

void Controller::playerMove() {
    player_->animate();
    player_->move();
}

void Controller::setPlayerRotation(const sf::RenderWindow& window) {
    auto aimVector = window.mapPixelToCoords(sf::Mouse::getPosition()) -
                     player_->getPosition();
    aimVector = normalize(aimVector);
    player_->handleRotation(aimVector);
}

void Controller::updateView() {
    view_->setCenter(player_->getPosition());
}

sf::View* Controller::getView() {
    return view_;
}

Player* Controller::getPlayer() {
    return player_;
}
void Controller::bindPlayer(Player* p) {
    player_ = p;
}

void Controller::bindView(sf::View* v) {
    view_ = v;
}
