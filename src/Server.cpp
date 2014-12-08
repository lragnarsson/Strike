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
#include "Messages.h"



/* Implementation av Server
 */
NetworkHandler nh;

void Server::run(){

    nh.initServer();
    std::string tmp;
    while(true)
    {
        nh.checkForNewTcpConnections();
        std::getline(std::cin, tmp);

        ConsolePrintString cps;
        cps.str = tmp;

        std::cout << cps.header << " " << cps.str << std::endl;
        sf::Packet p = cps.asPacket();
        int i;
        std::string s;
        p >> i >> s;
        std::cout << i << " " << s << std::endl;
        nh.sendTCPPacket(cps.asPacket());

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

