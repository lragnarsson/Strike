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

void Server::run(){
    sf::sleep(sf::milliseconds(1000));

    nh_.initServer();
    acceptConnections(); //Waits until user presses enter
    nh_.initRemotePlayers();

    std::cout << "Startar server" << std::endl;
}

void Server::readNetwork(){
    // ingen överraskning direkt att det va tomt här med.
}

void Server::writeNetwork(){
    // Men ändå rätt chill att Isak gjorde skalet iaf.
}

void Server::handleGameLogic(){
    // fan Isak är ju bäst typ.
}

void Server::handleCollisions(){
    //tomt
}

void Server::acceptConnections(){

    while(true)
    {
        nh_.checkForNewTcpConnections();
        nh_.recieveTCPPackets();
        nh_.processInternalMessages();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            break;
    }
}

