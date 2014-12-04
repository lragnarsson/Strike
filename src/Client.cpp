//  Client.cpp
//  Strike

#include "./Client.h"
#include <string>
#include "./GeomUtils.h"

Client::Client() : Game(),
                   renderWindow_(sf::VideoMode(1280, 720), "Strike") {
    renderWindow_.setFramerateLimit(120);
    renderWindow_.setMouseCursorVisible(false);
    Player* player = new Player(1);
    player->setWeapon(new Weapon(30, 180, 30, 50, 500, 70));
    gameState_.addPlayer(player);
    controller_.bindPlayer(player);

    Player* p2 = new Player(2);
    p2->setPosition(sf::Vector2f(300.f, 100.f));
    p2->move();
    gameState_.addPlayer(p2);
}

void Client::run() {
    while (renderWindow_.isOpen()) {
        readNetwork();
        handleInput();
        handleCollisions();
        handleGameLogic();
        writeNetwork();
        draw();
    }
}

bool Client::connectToServer(std::string name,
                             unsigned int team,
                             sf::IpAddress ip) {
    return true;
}
void Client::readNetwork() {
    return;
}

void Client::writeNetwork() {
    return;
}

void Client::handleCollisions() {
    collideMoveVector(controller_.getPlayer()->getPosition(),
                        controller_.getPlayer()->getMoveVector(),
                        controller_.getPlayer()->getRadius());
    controller_.playerMove();
    handleShots();
}

void Client::handleGameLogic() {
    return;
}

void Client::handleInput() {
    controller_.handleKeyEvents(&renderWindow_);
    controller_.handlePlayerActions();
    controller_.updatePlayerInputVector();
    controller_.setPlayerRotation(renderWindow_);
    gameState_.addUnhandledShots(controller_.playerFire());
}

void Client::draw() {
    renderWindow_.clear();
    controller_.updateView();
    renderWindow_.setView(*controller_.getView());
    gameState_.draw(&renderWindow_);
    renderWindow_.display();
}

void Client::handleShots() {
    std::vector<Shot*> shots {gameState_.takeUnhandledShots()};
    if (!shots.empty()) {
        for (auto shot : shots) {
            float maxDistance = 100000.f;
            sf::Vector2f intersectionPoint = {shot->getEndPoint()};
            for (auto physObj : gameState_.getPhysicalObjects()) {
                if (physObj->intersectRay(shot->getRay(), intersectionPoint))
                    if (length(intersectionPoint - shot->getOrigin()) < maxDistance) {
                        shot->setEndPoint(intersectionPoint);
                        maxDistance = length(intersectionPoint - shot->getOrigin());
                    }
                }
            for (auto player : gameState_.getPlayers()) {
                if (player->intersectRay(shot->getRay(), intersectionPoint))
                    if (length(intersectionPoint - shot->getOrigin()) < maxDistance) {
                        shot->setEndPoint(intersectionPoint);
                        maxDistance = length(intersectionPoint - shot->getOrigin());
                    }
            }
        }
    }
    gameState_.removeOldShots();
    gameState_.addHandledShots(shots);
}

void Client::collideMoveVector(sf::Vector2f position,
                               sf::Vector2f& moveVector,
                               float radius) {
    sf::Vector2f intersectionPoint = position + moveVector;
    float maxDistance = length(moveVector);
    LineSegment ls = LineSegment(position, intersectionPoint);
    for (auto physObj : gameState_.getPhysicalObjects()) {
        if (physObj->intersectCircle(radius, ls, intersectionPoint))
            if (length(intersectionPoint - position) < maxDistance) {
                moveVector = intersectionPoint - position;
                maxDistance  = length(moveVector);
            }
    }
    for (auto player : gameState_.getPlayers()) {
        if (player->intersectCircle(radius, ls, intersectionPoint))
            if (length(intersectionPoint - position) < maxDistance) {
                moveVector = intersectionPoint - position;
                maxDistance  = length(moveVector);
            }
    }
}
