#include "./Controller.h"
#include <iostream>
std::vector<Shot*> Controller::playerFire() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        return player_->fire();
    } else {
        std::vector<Shot*> shotVector;
        return shotVector;
    }
} 

void Controller::reloadWeapon() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        player_->reloadWeapon();
    }
}

void Controller::isSprinting() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        player_->setSpeedMultiplier(2.0f);
    }
    else {
        player_->setSpeedMultiplier(1.0f);
    }
}

Controller::~Controller() {
    view_ = nullptr;        // objects are destroyed by GameState
    player_ = nullptr;      // objects are destroyed by GameState
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
    //std::cout << "elapsed time: " << elapsed.asSeconds() << std::endl;
    player_->calculateMoveVector(inputVector_, elapsed.asSeconds());
    player_->move(sf::Vector2f {});
}

void Controller::playerRotate(const sf::RenderWindow& window) {
  auto aimVector = window.mapPixelToCoords(sf::Mouse::getPosition()) -
      player_->getPosition();
  aimVector /= (sqrtf(pow(aimVector.x, 2) + pow(aimVector.y, 2)));
  player_->handleRotation(aimVector);
  auto mousePos = window.mapCoordsToPixel(aimVector * 50.f +
                                          player_->getPosition());
  sf::Mouse::setPosition(mousePos);
}

void Controller::updateView() {
    view_->setCenter(player_->getPosition());
}

void Controller::bindPlayer(Player* p) {
    player_ = p;
}

void Controller::bindView(sf::View* v) {
    view_ = v;
}
