/***************************************
Messages.cpp

Polymorph class structure for messages to be passed over the internet or localy.

Written by:
Erik Sköld
Isak Wiberg
***************************************/

#include "./Messages.h"

#include <SFML/Network.hpp>

ServerAcceptConnection::ServerAcceptConnection(sf::Packet packet) : Message(SERVER_ACCEPT_CONNECTION, TCP, -1)
{
    packet >> playerID;
}

sf::Packet ServerAcceptConnection::asPacket()
{
    sf::Packet pkt;
    pkt << header << playerID;
    return pkt;
}

AddPlayer::AddPlayer(sf::Packet packet) : Message(ADD_PLAYER, TCP, -1)
{
    packet >> playerID >> teamID >> name;
}

sf::Packet AddPlayer::asPacket()
{
    sf::Packet pkt;
    pkt << header << playerID << teamID << name;
    return pkt;
}

ClientNotifyUDPPort::ClientNotifyUDPPort(sf::Packet packet) : Message(CLIENT_NOTIFY_UDP_PORT, TCP, -1)
{
    packet >> playerID >> port;
}

sf::Packet ClientNotifyUDPPort::asPacket()
{
    sf::Packet pkt;
    pkt << header << playerID << port;
    return pkt;
}

ConsolePrintString::ConsolePrintString(sf::Packet packet) : Message(CONSOLE_PRINT_STRING, TCP, -1)
{
    packet >> str;
}

sf::Packet ConsolePrintString::asPacket()
{
    sf::Packet pkt;
    pkt << header << str;
    return pkt;
}

InitialInformation::InitialInformation(sf::Packet packet) :
    Message(INITIAL_INFORMATION, TCP, -1)
{
    packet >> clientID >> teamID >> clientName;
}

sf::Packet InitialInformation::asPacket()
{
    sf::Packet pkt;
    pkt << header << clientID << teamID << clientName;
    return pkt;
}


PlayerUpdate::PlayerUpdate(sf::Packet packet) : Message(PLAYER_UPDATE, UDP, -1)
{
    packet >> playerID >> xCoord >> yCoord >> rotation >> health >> speed;
}

sf::Packet PlayerUpdate::asPacket()
{
    sf::Packet pkt;
    pkt << header << playerID << xCoord << yCoord << rotation << health << speed;
    return pkt;
}

AddShot::AddShot(sf::Packet packet) : Message(ADD_SHOT, UDP, -1)
{
    packet >> clientID >> originXPos >> originYPos >> directionXPos
           >> directionYPos >> endPointXPos >> endPointYPos >> damage >> sound;
}

sf::Packet AddShot::asPacket()
{
    sf::Packet pkt;
    pkt << header << clientID << originXPos << originYPos << directionXPos
        << directionYPos << endPointXPos << endPointYPos << damage << sound;
    return pkt;
}

RoundRestart::RoundRestart(sf::Packet packet) : Message(ROUND_RESTART, TCP, -1)
{
    packet >> tTeamScore >> ctTeamScore >> spawnpointIndex;
}

sf::Packet RoundRestart::asPacket()
{
    sf::Packet pkt;
    pkt << header << tTeamScore << ctTeamScore << spawnpointIndex;
    return pkt;
}

GameObjUpdate::GameObjUpdate(sf::Packet packet) : Message(GAME_OBJ_UPDATE, UDP, -1) {
    packet >> xPos >> yPos >> isEquipped >> ownerID;
}

sf::Packet GameObjUpdate::asPacket() {
    sf::Packet pkt;
    pkt << header << xPos << yPos << isEquipped << ownerID;
    return pkt;
}
