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

AddPlayer::AddPlayer(sf::Packet packet) : Message(AddPlayer)
{
    packet >> playerID;
}

sf::Packet AddPlayer::asPacket()
{
    sf::Packet pkt;
    pkt << header << playerID;
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
