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


    std::cout << "Startar server" << std::endl;
}

void Server::readNetwork(){
    // ingen �verraskning direkt att det va tomt h�r med.
}

void Server::writeNetwork(){
    // Men �nd� r�tt chill att Isak gjorde skalet iaf.
}

void Server::handleGameLogic(){
    // fan Isak �r ju b�st typ.
}

void Server::handleCollisions(){
    //tomt
}

void Server::acceptConnections(){

    while(true)
    {
        nh_.checkForNewTcpConnections();
        nh_.recieveTCPPackets();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            break;
    }
}

