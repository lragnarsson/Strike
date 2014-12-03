#include "./Controller.h"

Controller::Controller() {
  view_ = new sf::View(sf::FloatRect(0, 0, 500, 300));
}

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

Controller::~Controller() {
    delete view_;
    view_ = nullptr;        // objects are destroyed by GameState
    player_ = nullptr;      // objects are destroyed by GameState
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

}
void Controller::setPlayerInputVector() {
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

    player_->setMoveVector(inputVector_, elapsed.asSeconds());
}

void Controller::playerMove() {
    player_->move();
}

void Controller::setPlayerRotation(const sf::RenderWindow& window) {
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
