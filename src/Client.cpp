/***************************************
Client.cpp

Class for running the game client-side

Written by:
Lage Ragnarsson
Isak Wiberg
Jesper Otterholm
Filip Östman
***************************************/

#include "./Client.h"

#include <boost/thread.hpp>

#include "./GeomUtils.h"
#include "./SysUtils.h"
#include "./Team.h"
#include "./WeaponFactory.h"


Client::Client() : renderWindow_(sf::VideoMode(1280, 720), "Strike") {
    renderWindow_.setFramerateLimit(120);
    renderWindow_.setMouseCursorVisible(false);

    loadTextures();

    Player* player = new Player(clientID_, gameState_.tTeam(), textures_["cage3.png"]);

    gameState_.addPlayer(player);
    controller_.bindPlayer(player);
    WeaponFactory w;
    player->addObject(w.createFrag(sf::Vector2f()));
    player->addObject(w.createFrag(sf::Vector2f()));
    player->addObject(w.createAK47(sf::Vector2f()));

    hud_.setCrosshair(player->getCrosshair());

    Player* p2 = new Player(2, gameState_.ctTeam(), textures_["cage3.png"]);
    p2->setPosition(sf::Vector2f(500.f, 100.f));
    p2->move();
    gameState_.addPlayer(p2);

    gameState_.setPlayerSpawnPoints();
    soundBuffer.loadFromFile(resourcePath("res/sounds/") + "pistol.wav");
    shotSound_.setBuffer(soundBuffer);
}

Client::~Client() noexcept {
    for (auto texture : textures_)
        delete texture.second;
}

void Client::networkFunction() {
    while (true) {
        nh_.update();
        sf::Time sleepTime {sf::milliseconds(10)};
        sf::sleep(sleepTime);
    }
}

void Client::run() {

    boost::thread networkThread(&Client::networkFunction, this);

    while (renderWindow_.isOpen()) {
        //nh_.update();
        readFromNetwork();
        handleInput();
        handleCollisions();
        handleSounds();
        handleGameLogic();
        writeToNetwork();
        draw();
    }
}

bool Client::connectToServer(std::string name,
                             int team,
                             sf::IpAddress ip) {
  return nh_.connectToServer(name, team, ip);
}

void Client::roundRestart() {
//TODO
}

void Client::readFromNetwork() {
    for (auto message : nh_.getNewMessages()) {
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
                    if ((player->getClientID() == msg->playerID) && (player->getClientID() != controller_.getPlayer()->getClientID())) {
                        player->setHealth(msg->health);
                        player->setPosition(msg->xCoord, msg->yCoord);
                        player->setRotation(msg->rotation);
                        player->move();
                    }
                }
                break;
            }
            case ROUND_RESTART: {
                RoundRestart* rrmsg {static_cast<RoundRestart*>(message)};
                gameState_.tTeam()->setScore(rrmsg->tTeamScore);
                gameState_.ctTeam()->setScore(rrmsg->ctTeamScore);
                int spawnpointIndex {rrmsg->spawnpointIndex};

                Player* myPlayer {controller_.getPlayer()};
                if (myPlayer->getTeam()->getTeamID() == T_TEAM) {
                    myPlayer->setPosition(gameState_.getTspawnpoints().at(spawnpointIndex));
                    myPlayer->move();
                }
                else {
                    myPlayer->setPosition(gameState_.getCTspawnpoints().at(spawnpointIndex));
                    myPlayer->move();
                }
                break;
            }
            case ADD_PLAYER: {
                AddPlayer* msg = static_cast<AddPlayer*>(message);
                if (msg->playerID == controller_.getPlayer()->getClientID())
                    break;
                gameState_.addPlayer(new Player(msg->playerID, (msg->teamID == T_TEAM ? gameState_.tTeam() : gameState_.ctTeam()), textures_["cage3.png"]));
                break;
            }
            case INITIAL_INFORMATION: {
                InitialInformation* msg = static_cast<InitialInformation*>(message);
                Player* myPlayer {controller_.getPlayer()};
                clientID_ = msg->clientID;
                myPlayer->setClientID(msg->clientID);
                myPlayer->setTeam((msg->teamID == T_TEAM ? gameState_.tTeam() : gameState_.ctTeam()));

                std::cout << "ClientID and TeamID (0 = T, 1 = CT) of player updated to: " << msg->clientID << ", " << msg->teamID << std::endl;
                break;
            }
        }

        delete message;
    }
}

void Client::writeToNetwork() {
    std::vector<Message*> outboundMessages;
    outboundMessages.push_back(new PlayerUpdate(controller_.getPlayer()->getClientID(),
                                                controller_.getPlayer()->getPosition().x,
                                                controller_.getPlayer()->getPosition().y,
                                                controller_.getPlayer()->getRotation(),
                                                controller_.getPlayer()->getHealth(),
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
    if (!controller_.getPlayer()->isDead()) {
        collideMoveVector(controller_.getPlayer()->getPosition(),
                          controller_.getPlayer()->getMoveVector(),
                          controller_.getPlayer()->getRadius());
        controller_.playerMove();
        handleGameObjects();
        handleShots();
        handleVision();
    }
}

void Client::handleGameLogic() {
    hud_.setHealth(controller_.getPlayer()->getHealth());
    hud_.setAmmo(controller_.getPlayer()->getMagazineAmmo(), controller_.getPlayer()->getAdditionalAmmo());
    hud_.setScore(gameState_.tTeam()->getScore(), gameState_.ctTeam()->getScore());
    hud_.setPositions(renderWindow_);
}

void Client::handleInput() {
    controller_.handleKeyEvents(&renderWindow_);
    if (!controller_.getPlayer()->isDead()) {
        controller_.handlePlayerActions();
        controller_.updatePlayerInputVector();
        controller_.setPlayerRotation(renderWindow_);
        controller_.pickupObjects(gameState_.getStationaryGameObjects());
        gameState_.addMovingGameObject(controller_.playerThrow());
        gameState_.addUnhandledShots(controller_.playerFire());
    }
}

void Client::draw() {
    /*
    std::cout << "\n\n\n\n";
    for (auto player : gameState_.getPlayers()) {
        std::cout << "Player info (id,xpos,ypos): (" << player->getClientID() << ", " << player->getPosition().x << ", " << player->getPosition().y << ")\n";
    }
    std::cout << std::endl;
     */
    renderWindow_.clear();
    controller_.updateView();
    renderWindow_.setView(*controller_.getView());
    handleVision();
    createDecals();
    gameState_.draw(&renderWindow_);
    renderWindow_.draw(hud_);
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

void Client::handleShots() {
    for (auto shot : gameState_.getUnhandledShots()) {
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
            if (player->getClientID() != clientID_ && player->intersectRay(shot->getRay(), centerAfterCollision))
                if (length(centerAfterCollision - shot->getOrigin()) < maxDistance) {
                    shot->setEndPoint(centerAfterCollision);
                    maxDistance = length(centerAfterCollision - shot->getOrigin());
                    shot->setTargetID(player->getClientID());
                }
        }
    }
    gameState_.removeOldShots();
}

void Client::createDecals() {
    for (auto shot : gameState_.getHandledShots()) {
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

void Client::handleVision() {
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

void Client::handleSounds() {

    for (auto shot : gameState_.getHandledShots()) {
        if (!shot->getSoundstatus()) {
            sf::Vector2f distanceVector;
            distanceVector = controller_.getPlayer()->getPosition() - shot->getOrigin();
            float distance = length(distanceVector);
            if(distance < 100.0f) {
                shotSound_.setVolume(100);
                shotSound_.play();
                shot->setSoundstatus();
            }
            else if(distance < 1000.0f) {
                shotSound_.setVolume(50);
                shotSound_.play();
                shot->setSoundstatus();                    
            }
            else {
                shotSound_.setVolume(10);
                shotSound_.play();
                shot->setSoundstatus(); 
            }
        }
    }
}

void Client::handleGameObjects() {
  for (auto gameObject : *(gameState_.getMovingGameObjects())) {
    if (Grenade* grenade = dynamic_cast<Grenade*>(gameObject)) {
        if (grenade->endOfFuse()) {
            gameState_.addUnhandledShots(grenade->explode());
            gameState_.addAnimatedDecal(
                new AnimatedDecal(gameObject->getPosition(), sf::Vector2f(1.5f,1.5f),
                                  textures_["explosion1.png"], sf::IntRect(0, 0, 192, 195),
                                  20, 25, false, 25));
        }
    }
    gameObject->calculateMoveVector(clock_.getElapsedTime().asMilliseconds());
    collideMoveVector(gameObject->getPosition(),
                      gameObject->getMoveVector(),
                      gameObject->getRadius());
    gameObject->move();
  }
  gameState_.movingToStationaryObjects();
  gameState_.removeGameObjects();
  clock_.restart();
}
