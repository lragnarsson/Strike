//  Client.cpp
//  Strike

#include "Client.h"

Client::Client() : Game(), renderWindow_(sf::VideoMode(1280, 720), "Strike: Local Defensive") {
    renderWindow_.setFramerateLimit(120);
    renderWindow_.setMouseCursorVisible(false);
    Player* player = new Player(1);
    gameState_.addPlayer(player);
    controller_.bindPlayer(player);
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
    gameState_.addUnhandledShots(controller_.playerFire());  // adds the shots that were created by player (if there were any).
}

void Client::draw() {
    renderWindow_.clear();
    controller_.updateView();
    renderWindow_.setView(*controller_.getView());
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

void Client::collideMoveVector(sf::Vector2f position,
                         sf::Vector2f& moveVector,
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
}
