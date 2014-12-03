#ifndef MESSAGES_H
#define MESSAGES_H

#include <SFML/Network.hpp>

#include <string>

#include "MessageCodes.h"

class Message
{
public:
    virtual ~Message() = default;

    const int header;


protected:
    Message(int h) : header(h) {}
    Message(const Message&) = delete;
};

class ServerAcceptConnection : public Message
{
public:
    std::string str;

    ServerAcceptConnection() : Message(SERVER_ACCEPT_CONNECTION) {}
    ServerAcceptConnection(sf::Packet);
    ServerAcceptConnection(std::string s) : Message(CONSOLE_PRINT_STRING), str(s) {}

    sf::Packet asPacket();
};

class ConsolePrintString : public Message
{
public:
    std::string str;

    ConsolePrintString() : Message(CONSOLE_PRINT_STRING) {}
    ConsolePrintString(sf::Packet);
    ConsolePrintString(std::string s) : Message(CONSOLE_PRINT_STRING), str(s) {}

    sf::Packet asPacket();
};

class PlayerUpdate : public Message
{
public:

    PlayerUpdate() : Message(PLAYER_UPDATE) {}
    float xCoord;
    float yCoord;
    float rotation;
    int health;

    PlayerUpdate(float x, float y, float r, int h) : Message(PLAYER_UPDATE),
        xCoord(x), yCoord(y), rotation(r), health(h) {}

    PlayerUpdate& operator<<(sf::Packet& packet)
    {
        packet >> xCoord >> yCoord >> rotation >> health;
        return *this;
    }

    void operator>>(sf::Packet& packet)
    {
        packet << header << xCoord << yCoord << rotation << health;
    }

};

#endif
