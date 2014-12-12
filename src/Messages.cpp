#include "Messages.h"

#include <SFML/Network.hpp>

ServerAcceptConnection::ServerAcceptConnection(sf::Packet packet) : Message(SERVER_ACCEPT_CONNECTION)
{
    packet >> playerID;
}

sf::Packet ServerAcceptConnection::asPacket()
{
    sf::Packet pkt;
    pkt << header << playerID;
    return pkt;
}

AddPlayer::AddPlayer(sf::Packet packet) : Message(ADD_PLAYER)
{
    packet >> playerID >> teamID;
}

sf::Packet AddPlayer::asPacket()
{
    sf::Packet pkt;
    pkt << header << playerID << teamID;
    return pkt;
}

ClientNotifyUDPPort::ClientNotifyUDPPort(sf::Packet packet) : Message(CLIENT_NOTIFY_UDP_PORT)
{
    packet >> playerID >> port;
}

sf::Packet ClientNotifyUDPPort::asPacket()
{
    sf::Packet pkt;
    pkt << header << playerID << port;
    return pkt;
}

ConsolePrintString::ConsolePrintString(sf::Packet packet) : Message(CONSOLE_PRINT_STRING)
{
    packet >> str;
}

sf::Packet ConsolePrintString::asPacket()
{
    sf::Packet pkt;
    pkt << header << str;
    return pkt;
}

PlayerUpdate::PlayerUpdate(sf::Packet packet) : Message(PLAYER_UPDATE)
{
    packet >> playerID >> xCoord >> yCoord >> rotation >> health;
}

sf::Packet PlayerUpdate::asPacket()
{
    sf::Packet pkt;
    pkt << header << playerID << xCoord << yCoord << rotation << health;
    return pkt;
}

AddShot::AddShot(sf::Packet packet) : Message(ADD_SHOT)
{
    packet >> clientID >> originXPos >> originYPos >> directionXPos
    >> directionYPos >> endPointXPos >> endPointYPos >> damage;
}

sf::Packet AddShot::asPacket()
{
    sf::Packet pkt;
    pkt << header << clientID << originXPos << originYPos << directionXPos
    << directionYPos << endPointXPos << endPointYPos << damage;
    return pkt;
}

RoundRestart::RoundRestart(sf::Packet packet) : Message(ROUND_RESTART)
{
    packet >> tTeamScore >> ctTeamScore >> spawnpointIndex;
}

sf::Packet RoundRestart::asPacket()
{
    sf::Packet pkt;
    pkt << header << tTeamScore << ctTeamScore << spawnpointIndex;
    return pkt;
}