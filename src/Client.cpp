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
    player->setWeapon(new Weapon(1000, 2000, 1000, 20, 500, 10, 500.f));
    gameState_.addPlayer(player);
    gameState_.addHUDElement(player->getCrosshair());
    controller_.bindPlayer(player);
    gameState_.setplayerSpawnPoints();

    Player* p2 = new Player(2, textures_["cage3.png"]);
    p2->setPosition(sf::Vector2f(500.f, 100.f));
    p2->move();
    gameState_.addPlayer(p2);
}

void Client::run() {
    while (renderWindow_.isOpen()) {
        readFromNetwork();
        handleInput();
        handleCollisions();
        handleGameLogic();
        writeToNetwork();
        draw();
    }
}

bool Client::connectToServer(std::string name,
                             int team,
                             sf::IpAddress ip) {
  //return nh_.connectToServer(name, team, ip);
  return true;
}

void Client::readFromNetwork() {
    std::vector<Message*> receivedMessages = nh_.getNewMessages();
    for (auto message : receivedMessages) {
        switch (message->header) {
            case ADD_SHOT: {
                AddShot* msg = static_cast<AddShot*>(message);
                if (msg->clientID == clientID_)
                    break;
                gameState_.addHandledShot(new Shot(msg->clientID,
                                                    sf::Vector2f(msg->originXPos, msg->originYPos),
                                                    sf::Vector2f(msg->directionXPos, msg->directionYPos),
                                                    sf::Vector2f(msg->endPointXPos, msg->endPointYPos),
                                                    msg->damage));
                break;
          }
          case PLAYER_UPDATE: {
              PlayerUpdate* msg = static_cast<PlayerUpdate*>(message);
              for (auto player : gameState_.getPlayers()) {
                  if (player->getClientID() == clientID_) {
                      player->setHealth(msg->health);
                      player->setPosition(msg->xCoord, msg->yCoord);
                      player->setRotation(msg->rotation);
                  }
              }
              break;
          }
          case ROUND_RESTART:

                break;
          case ADD_PLAYER: {
              AddPlayer* msg = static_cast<AddPlayer*>(message);
              gameState_.addPlayer(new Player(msg->playerID, textures_["cage3.png"]));
              break;
          }
        }

        delete message;
    }
}

void Client::writeToNetwork() {
    std::vector<Message*> outboundMessages;
    outboundMessages.push_back(new PlayerUpdate(controller_.getPlayer()->getPosition().x,
                                                controller_.getPlayer()->getPosition().y,
                                                controller_.getPlayer()->getRotation(),
                                                0));
    for (auto shot : gameState_.getUnhandledShots())
        outboundMessages.push_back(new AddShot(shot->getClientID(),
                                               shot->getOrigin().x,
                                               shot->getOrigin().y,
                                               shot->getDirection().x,
                                               shot->getDirection().y,
                                               shot->getEndPoint().x,
                                               shot->getEndPoint().y,
                                               shot->getDamage()));
    nh_.addToOutbox(outboundMessages);
    gameState_.migrateShots();
}

void Client::handleCollisions() {
    collideMoveVector(controller_.getPlayer()->getPosition(),
                      controller_.getPlayer()->getMoveVector(),
                      controller_.getPlayer()->getRadius());
    controller_.playerMove();
    handleShots();
}

void Client::handleGameLogic() {
    // Check player visibility
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
                textures_[fileName]->setRepeated(false);
                std::cout << "Loaded file: " << fileName << std::endl;
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
    }
}

void Client::handleShots() {
    std::vector<Shot*> shots {gameState_.getUnhandledShots()};
    for (auto shot : shots) {
        float maxDistance = 100000.f;
        sf::Vector2f centerAfterCollision = shot->getEndPoint();

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
                moveVector = centerAfterCollision - position;
                maxDistance = length(moveVector);
            }
    }

    for (auto physObj : gameState_.getPhysicalObjects()) {
        if (physObj->intersectCircle(radius, ls, centerAfterCollision, dummy, intersectionNormal))
            if (length(centerAfterCollision - position) < maxDistance) {
                dummy = position + moveVector - centerAfterCollision;
                tangentMoveVector = dummy - dot(dummy, intersectionNormal) * intersectionNormal;
                moveVector = centerAfterCollision - position;
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
