//
//  Server.cpp
//  Strike
//

#include "Server.h"
#include "Game.h"
#include "NetworkHandler.h"
#include "./MessageCodes.h"
#include <SFML/System.hpp>

void Server::run() {
    sf::sleep(sf::milliseconds(1000));
    nh_.initServer();
    acceptConnections();     // Loops until user presses enter
    //nh_.initRemotePlayers();
    std::cout << "Startar server" << std::endl;
    initRemotePlayers();
    roundRestart();

    while (true) {
        nh_.update();
        readFromNetwork();
        handleGameLogic();
        writeToNetwork();
        /*ConsolePrintString cps{"Servern säger hej!"};
          nh_.broadcastUDPPacket(cps.asPacket());
          sf::sleep(sf::milliseconds(1000));*/
    }
}

void Server::readFromNetwork() {
  for (auto message : nh_.getNewMessages()) {
      switch (message->header) {
          case PLAYER_UPDATE: updatePlayer(static_cast<PlayerUpdate*>(message)); break;
          case ADD_SHOT: handleShot(static_cast<AddShot*>(message)); break;
      }
      delete message;
  }
}

void Server::writeToNetwork() {
    std::vector<Message*> outboundMessages;
    for (auto player : gameState_.getPlayers())
        outboundMessages.push_back(new PlayerUpdate(player->getPosition().x,
                                                    player->getPosition().y,
                                                    player->getRotation(),
                                                    player->getHealth()));
    for (auto shot : gameState_.getHandledShots())
        outboundMessages.push_back(new AddShot(shot->getClientID(),
                                               shot->getOrigin().x,
                                               shot->getOrigin().y,
                                               shot->getDirection().x,
                                               shot->getDirection().y,
                                               shot->getEndPoint().x,
                                               shot->getEndPoint().y,
                                               shot->getDamage()));
    nh_.addToOutbox(outboundMessages);
    gameState_.removeOldShots(true);
}

void Server::handleGameLogic() {

}

void Server::acceptConnections() {
    std::cout << "Waiting for players to connect. Press right shift when you want to start the game." << std::endl;
    while(true)
    {
        nh_.checkForNewTcpConnections();
        nh_.update();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
            break;
    }
}

void Server::initRemotePlayers() {
    std::vector<Message*> newPlayerMessages;
    for (Message* msg : nh_.getNewMessages()) {
        if (msg->header == ADD_PLAYER) {
            AddPlayer* ap {static_cast<AddPlayer*>(msg)};
            gameState_.addPlayer(new Player(ap->playerID));
            msg->reciever = -1; // set message to broadcastmode
            newPlayerMessages.push_back(msg);
        }
    }

    nh_.addToOutbox(newPlayerMessages);
}

void Server::roundRestart() {
    std::vector<Message*> outboundMessages;

    int ti = 0;
    int cti = 0;
    for (auto player : gameState_.getPlayers()) {
        player->setHealth(100);
        outboundMessages.push_back(new RoundRestart(gameState_.ctTeam()->getScore(), gameState_.tTeam()->getScore(), (player->getTeam()->getTeamID() == T_TEAM ? ti++ : cti++), player->getClientID()));
    }

    nh_.addToOutbox(outboundMessages);
}

void Server::updatePlayer(PlayerUpdate* message) {
  for (auto player : gameState_.getPlayers())
      if (player->getClientID() == message->playerID) {
          player->setPosition(sf::Vector2f(message->xCoord,
                                           message->yCoord));
          player->setRotation(message->rotation);
      }
}

void Server::handleShot(AddShot* message) {
    Shot* shot = new Shot(message->clientID,
                          sf::Vector2f(message->originXPos, message->originYPos),
                          sf::Vector2f(message->directionXPos, message->directionYPos),
                          sf::Vector2f(message->endPointXPos, message->endPointYPos),
                          message->damage);
    Player* hitPlayer;
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
                hitPlayer = player;
            }
    }
    hitPlayer->decreaseHealth(shot->getDamage());
    gameState_.addHandledShot(shot);
}
