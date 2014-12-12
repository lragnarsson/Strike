//  Client.cpp
//  Strike

#include "./Client.h"
#include "./GeomUtils.h"
#include "./SysUtils.h"

Client::Client() : renderWindow_(sf::VideoMode(1280, 720), "Strike") {
    renderWindow_.setFramerateLimit(120);
    renderWindow_.setMouseCursorVisible(false);

    loadTextures();

    Player* player = new Player(clientID_, textures_["cage3.png"]);
    //player->setWeapon(new Weapon(1000, 2000, 1000, 300, 500, 10, 500.f));
    gameState_.addPlayer(player);
    gameState_.addHUDElement(player->getCrosshair());
    controller_.bindPlayer(player);
    Team blueTeam("T"); //For correct spawnpoints, initilize team with T or CT
    blueTeam.addPlayer(player);
    gameState_.addTeam(&blueTeam);
    gameState_.setplayerSpawnPoints();

    Player* p2 = new Player(2, textures_["cage3.png"]);
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
    handleGameObjects();
}

void Client::handleGameLogic() {
    // check player visibility
    for (auto player : gameState_.getPlayers()) {
        bool blocked = false;

        if (player == controller_.getPlayer())
            player->lastSeenNow();
        else
            for (auto obj : gameState_.getPhysicalObjects())
                blocked |= obj->intersectLineSegment( LineSegment(controller_.getPlayer()->getPosition(), player->getPosition()) );

        if (!blocked)
			player->lastSeenNow();
    }
}

void Client::handleInput() {
    controller_.handleKeyEvents(&renderWindow_);
    controller_.handlePlayerActions();
    controller_.updatePlayerInputVector();
    controller_.setPlayerRotation(renderWindow_);
    gameState_.addUnhandledShots(controller_.playerFire());
    gameState_.addMovingGameObject(controller_.playerThrow());
}

void Client::draw() {
    renderWindow_.clear();
    controller_.updateView();
    renderWindow_.setView(*controller_.getView());
    gameState_.draw(&renderWindow_);
    renderWindow_.display();
}

void Client::loadTextures() {
    auto fileNames = listDir(resourcePath("res/images/"));
    try {
        for (auto fileName : fileNames) {
            if (fileName.length() > 3) {
                textures_[fileName] = new sf::Texture();
                textures_[fileName]->loadFromFile(resourcePath("res/images/") + fileName);
                std::cout << "Loaded file: " << fileName << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
    }
}

sf::Texture* getTexturePtr(std::string name) {
    return textures_[name];
}

void Client::handleShots() {
    std::vector<Shot*> shots {gameState_.takeUnhandledShots()};
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
            if (player->intersectRay(shot->getRay(), centerAfterCollision))
                if (length(centerAfterCollision - shot->getOrigin()) < maxDistance) {
                    shot->setEndPoint(centerAfterCollision);
                    maxDistance = length(centerAfterCollision - shot->getOrigin());
                    shot->setTargetID(player->getClientID());
                    player->setHealth(shot->getDamage()); //För testning!
                    std::cout << "Health: " << player->getHealth() << std::endl; //För testning!
                }
        }
    }
    for (auto shot : shots) {
      if (shot->getTargetID() != -1) {
          gameState_.addAnimatedDecal(
              new AnimatedDecal(shot->getEndPoint(), sf::Vector2f(1.f, 1.f),
                                textures_["blood_hit_07.png"], sf::IntRect(0, 0, 128, 128),
                                20, 16, false, 4));
          gameState_.addAnimatedDecal(
              new AnimatedDecal(shot->getEndPoint() + shot->getDirection() * 128.f,
                                sf::Vector2f(1.f, 1.f), textures_["blood_hit_02.png"],
                                sf::IntRect(0, 0, 128, 128), 20, 16, false, 4));
      }
      else
          gameState_.addAnimatedDecal(
              new AnimatedDecal(shot->getEndPoint(), sf::Vector2f(0.4f,0.4f),
                                textures_["explosion1.png"], sf::IntRect(0, 0, 192, 195),
                                20, 25, false, 25));
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
	// Tangent
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

void Client::handleGameObjects() {
  for (auto gameObject : gameState_.getMovingGameObjects()) {
      if (Grenade* grenade = dynamic_cast<Grenade*>(gameObject)) {
          if (grenade->endOfFuse()) {
              gameState_.addUnhandledShots(grenade->explode());
              gameState_.addAnimatedDecal(
                  new AnimatedDecal(gameObject->getPosition(), sf::Vector2f(0.8f,0.8f),
                                    textures_["explosion1.png"], sf::IntRect(0, 0, 192, 195),
                                    20, 25, false, 25));
          }
      } else {
        collideMoveVector(gameObject->getPosition(),
                          gameObject->getMoveVector(),
                          gameObject->getRadius());
      }
  }
  gameState_.movingToStationaryObjects();
}
