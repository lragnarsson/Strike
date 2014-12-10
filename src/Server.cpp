//
//  Server.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-25.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "Server.h"
#include "Game.h"
#include "NetworkHandler.h"

/* Implementation av Server
 */

void Server::run() {
    sf::sleep(sf::milliseconds(1000));

    nh_.initServer();
    acceptConnections(); //Waits until user presses enter


    std::cout << "Startar server" << std::endl;
}

void Server::readNetwork() {
    // ingen överraskning direkt att det va tomt här med.
}

void Server::writeNetwork() {
    // Men ändå rätt chill att Isak gjorde skalet iaf.
}

void Server::handleGameLogic() {
    // fan Isak är ju bäst typ.
}

void Server::handleCollisions() {
    std::vector<Shot*> shots{gameState_.takeUnhandledShots()};
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
                }
        }
    }
    gameState_.removeOldShots(true);
    gameState_.addHandledShots(shots);
}

void Server::acceptConnections() {

    while(true)
    {
        nh_.checkForNewTcpConnections();
        nh_.recieveTCPPackets();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            break;
    }
}

