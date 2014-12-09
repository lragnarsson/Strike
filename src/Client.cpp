//  Client.cpp
//  Strike

#include "./Client.h"
#include <string>
#include "./GeomUtils.h"

Client::Client() : renderWindow_(sf::VideoMode(1280, 720), "Strike") {
    renderWindow_.setFramerateLimit(120);
    renderWindow_.setMouseCursorVisible(false);
    Player* player = new Player(clientID_);
    player->setWeapon(new Weapon(30, 180, 30, 50, 500, 70, 100.f));
    gameState_.addPlayer(player);
    gameState_.addHUDElement(player->getCrosshair());
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
    // check player visibility
    for (auto player : gameState_.getPlayers()) {
        if (player == controller_.getPlayer())
            player->lastSeenNow();
        else
            for (auto obj : gameState_.getPhysicalObjects()) {
                if ( !obj->intersectLineSegment( LineSegment(controller_.getPlayer()->getPosition(), player->getPosition()) ) ) {
                    player->lastSeenNow();
                }
            }
    }
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
            sf::Vector2f centerAfterCollision = {shot->getEndPoint()};
            for (auto physObj : gameState_.getPhysicalObjects()) {
                if (physObj->intersectRay(shot->getRay(), centerAfterCollision))
                    if (length(centerAfterCollision - shot->getOrigin()) < maxDistance) {
                        shot->setEndPoint(centerAfterCollision);
                        maxDistance = length(centerAfterCollision - shot->getOrigin());
                    }
                }
            for (auto player : gameState_.getPlayers()) {
                if (player->getClientID() != clientID_ && player->intersectRay(shot->getRay(), centerAfterCollision))
                    if (length(centerAfterCollision - shot->getOrigin()) < maxDistance) {
                        shot->setEndPoint(centerAfterCollision);
                        maxDistance = length(centerAfterCollision - shot->getOrigin());
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
    sf::Vector2f centerAfterCollision = position + moveVector;
    sf::Vector2f intersectionNormal, tangentMoveVector, dummy;
    float maxDistance = length(moveVector);
    LineSegment ls = LineSegment(position, centerAfterCollision);
    for (auto player : gameState_.getPlayers()) {
        if (player->intersectCircle(radius, ls, centerAfterCollision, dummy, intersectionNormal))
            if (length(centerAfterCollision - position) < maxDistance) {
                dummy = position + moveVector - centerAfterCollision;
                tangentMoveVector = dummy - dot(dummy, intersectionNormal) * intersectionNormal;
                moveVector = centerAfterCollision - position;// + tangentMoveVector;
                maxDistance = length(moveVector);
            }
    }
    for (auto physObj : gameState_.getPhysicalObjects()) {
        if (physObj->intersectCircle(radius, ls, centerAfterCollision, dummy, intersectionNormal))
            if (length(centerAfterCollision - position) < maxDistance) {
                dummy = position + moveVector - centerAfterCollision;
                tangentMoveVector = dummy - dot(dummy, intersectionNormal) * intersectionNormal;
                moveVector = centerAfterCollision - position;// + tangentMoveVector;
                maxDistance = length(moveVector);
            }
    }

    ls = LineSegment(centerAfterCollision, centerAfterCollision + tangentMoveVector);
    maxDistance = length(tangentMoveVector);
    for (auto player : gameState_.getPlayers()) {
        if (player->intersectCircle(radius, ls, centerAfterCollision, dummy, intersectionNormal))
            if (length(centerAfterCollision - ls.start) < maxDistance) {
                tangentMoveVector = centerAfterCollision - ls.start;
                maxDistance = length(tangentMoveVector);
            }
    }
    for (auto physObj : gameState_.getPhysicalObjects()) {
        if (physObj->intersectCircle(radius, ls, centerAfterCollision, dummy, intersectionNormal))
            if (length(centerAfterCollision - ls.start) < maxDistance) {
                tangentMoveVector = centerAfterCollision - ls.start;
                maxDistance = length(tangentMoveVector);
            }
    }

    moveVector += tangentMoveVector;
}
