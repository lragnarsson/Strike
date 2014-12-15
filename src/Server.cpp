/***************************************
Server.cpp

Class for running the game server-side

Written by:
Lage Ragnarsson
Isak Wiberg
Erik Sköld
***************************************/

#include "./Server.h"

#include "./Game.h"
#include "./NetworkHandler.h"
#include "./MessageCodes.h"

#include <boost/thread.hpp>
#include <SFML/System.hpp>

void Server::networkFunction() {
    while (true) {
        nh_.update();
        sf::Time sleepTime {sf::milliseconds(100)};
        sf::sleep(sleepTime);
    }
}


void Server::run() {
    sf::sleep(sf::milliseconds(1000));
    nh_.initServer();
    
    boost::thread networkThread(&Server::networkFunction, this);
    
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
    }
}

void Server::readFromNetwork() {
  std::vector<Message*> resMess = nh_.getNewMessages();
  for (auto message : resMess) {
      switch (message->header) {
          case PLAYER_UPDATE: {
              updatePlayer(static_cast<PlayerUpdate*>(message));
              std::cout << "got player update from " << static_cast<PlayerUpdate*>(message)->playerID << std::endl;
              break;
          }
          case ADD_SHOT: {
              handleShot(static_cast<AddShot*>(message));
              break;
          }
          case ADD_PLAYER: {
              AddPlayer* ap {static_cast<AddPlayer*>(message)};
              if (ap->teamID == CT_TEAM) {
                  gameState_.addPlayer(new Player{ap->playerID, gameState_.ctTeam()});
                  std::cout << "added player to CT_TEAM with id: " << ap->playerID << std::endl;
                  delete ap;
              }
              else if (ap->teamID == T_TEAM) {
                  gameState_.addPlayer(new Player{ap->playerID, gameState_.tTeam()});
                  std::cout << "added player to CT_TEAM with id: " << ap->playerID << std::endl;
                  delete ap;
              }
              else
                  std::cout << "Team index did not match any of CT_TEAM or T_Team. No player was created." << std::endl;
              break;
          }

      }
  }
}

void Server::writeToNetwork() {
    std::vector<Message*> outboundMessages;
    for (auto player : gameState_.getPlayers())
        outboundMessages.push_back(new PlayerUpdate(player->getClientID(),
                                                    player->getPosition().x,
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
        //nh_.update();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
            break;
    }
}

void Server::initRemotePlayers() {
    std::vector<Message*> newPlayerMessages;
    for (Message* msg : nh_.getNewMessages()) {
        if (msg->header == ADD_PLAYER) {
            AddPlayer* ap {static_cast<AddPlayer*>(msg)};
            if (ap->teamID == CT_TEAM) {
                gameState_.addPlayer(new Player(ap->playerID, gameState_.ctTeam()));
                std::cout << "Added player with (clientID, team): (" << ap->playerID << ", " << "CT_TEAM)" << std::endl;
            }
            else if (ap->teamID == T_TEAM) {
                gameState_.addPlayer(new Player{ap->playerID, gameState_.tTeam()});
                std::cout << "Added player with (clientID, team): (" << ap->playerID << ", " << "T_TEAM)" << std::endl;
            }
            else
                std::cout << "Team index did not match any CT_TEAM or T_Team. No player was created." << std::endl;
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
    delete message;
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
        if (player->getClientID() != shot->getClientID() && player->intersectRay(shot->getRay(), centerAfterCollision))
            if (length(centerAfterCollision - shot->getOrigin()) < maxDistance) {
                shot->setEndPoint(centerAfterCollision);
                maxDistance = length(centerAfterCollision - shot->getOrigin());
                hitPlayer = player;
            }
    }
    hitPlayer->decreaseHealth(shot->getDamage());
    gameState_.addHandledShot(shot);
    delete message;
}
