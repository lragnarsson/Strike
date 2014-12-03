#include "Messages.h"

#include <SFML/Network.hpp>

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
