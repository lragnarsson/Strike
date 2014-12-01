//
//  Client.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-25.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "Client.h"

/* Implementation av Client
 */
void Client::Client() {
    sf::RenderWindow renderWindow_(sf::VideoMode(1280, 720), "SFML-Playground");
    view_(sf::FloatRect(0, 0, 500, 300));

    renderWindow_.setFramerateLimit(120);
    window.setView(view);
    renderWindow_.setMouseCursorVisible(false);

    Team blueTeam_;
    Team redTeam_;

    Weapon weapon1{5,30,10,1000,5000,10};

    Player player1{1};

    gameState_.addPlayer(&player1);
    blueTeam.addPlayer(&player1);

    player1.setWeapon(&weapon1);

    controller_.bindPlayer(&player1);
    controller_.bindView(&view_);
}

void Client::run() {
    readNetwork();
    handleInput();
    handleCollisions();
    handleGameLogic();
    writeNetwork();
    draw();
}

void Client::readNetwork() {
    return;
}

void Client::writeNetwork() {
    return;
}

void Client::handleCollisions() {
    calculateMoveVector(player_-> getMoveVector());
    controller.playerMove();
    handleShots();
}

void Client::handleGameLogic() {
    return;
}


void Client::handleInput() {
    controller.handleKeyEvents(renderWindow);
    controller.handlePlayerActions();
    controller.setPlayerInputVector();
    controller.setplayerRotation(renderWindow);
    gameState_.addUnhandledShots(controller.playerFire());  // adds the shots that were created by player (if there were any).
}

void Client::draw() {
    renderWindow_.clear();
    controller.updateView();
    renderWindow_.setView(view_);
    gameState_.draw(renderWindow_);
    renderWindow_.display();
}


void Client::handleShots() {
    std::vector<Shot*> shots {gameState_.takeUnhandledShots()};
    if (!shots.empty()) {
      for (std::vector<Shot*>::iterator it = shots.begin(); it != shots.end(); ++it) {
      // Calculate newEndPoint with proper collision later
      sf::Vector2f newEndPoint {(*it)->getOrigin() + 100.0f * (*it)->getDirection()};
      // --- finished :D
      (*it)->setEndPoint(newEndPoint);
    }
  }
  gameState_.addHandledShots(shots);
}

void calculateMoveVector(sf::Vector2f position,
                         sf::Veector2f& moveVector,
                         float radius) {
  sf::Vector2f collisionPoint = position + moveVector;
  float maxDistance = length(moveVector);
  LineSegment ls = LineSegment(position, collisionPoint);
  for (auto physObj : gameState_.getPhysicalObjects())
    if (physObj->intersectCircle(radius, ls, collisionPoint)) {
      if (length(collisionPoint - position) < maxDistance) {
        moveVector = position + collisionPoint;
        maxDistance = length(moveVector);
      }
}
