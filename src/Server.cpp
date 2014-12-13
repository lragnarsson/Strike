//
//  Server.cpp
//  Strike
//

#include "Server.h"
#include "Game.h"
#include "NetworkHandler.h"
#include "./MessageCodes.h"

void Server::run(){
    sf::sleep(sf::milliseconds(1000));
    nh_.initServer();
    acceptConnections();
    nh_.initRemotePlayers();
    std::cout << "Startar server" << std::endl;

    while (event.type == sf::Event::KeyPressed &&
           event.key.code == sf::Keyboard::Escape) {
      readFromNetwork();
      handleGameLogic();
      writeToNetwork();
      /*ConsolePrintString cps{"Servern säger hej!"};
      nh_.broadcastUDPPacket(cps.asPacket());
      sf::sleep(sf::milliseconds(1000));*/
    }
}

void Server::readFromNetwork() {
  std::vector<Message*> receivedMessages = nh_.getNewMessages();
  for (auto message : recievedMessages_) {
      switch (message.header) {
          case PLAYER_UPDATE: updatePlayer(message); break;
          case ADD_SHOT: handleShot(message); break;
      }
  }
  for (auto message : recievedMessages_)
      delete message;
}

void Server::updatePlayer(Message* message) {
  for (auto player : gameState_.getPlayers())
      if (player->getClientID() == message->playerID) {
          player->setPosition(sf::Vector2f(message->xCoord,
                                           message->yCoord));
          player->setRotation(message->rotation);
    }
}

void Server::writeToNetwork() {
  
}

void Server::handleGameLogic(){
  
}

void Server::acceptConnections(){
    while(true) {
        nh_.checkForNewTcpConnections();
        nh_.recieveTCPPackets();
        nh_.processInternalMessages();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            break;
    }
}

void Server::roundRestart() {
  
}

void Server::handleShot(Message* message) {
    Shot* shot = new Shot(message->clientID,
                          sf::Vector2f(message->originXPos, message->originYPos),
                          sf::Vector2f(message->directlaionXPos, message->directionYPos),
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
    gameState_.addHandledShots(shot);
}
