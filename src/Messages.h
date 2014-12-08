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
    int playerID;

    ServerAcceptConnection() : Message(SERVER_ACCEPT_CONNECTION) {}
    ServerAcceptConnection(sf::Packet);
    ServerAcceptConnection(int pID) : Message(SERVER_ACCEPT_CONNECTION), playerID(pID) {}

    sf::Packet asPacket();
};

class AddPlayer : public Message
{
public:
    int playerID;
    AddPlayer() : Message(ADD_PLAYER) {}
    AddPlayer(sf::Packet);
    AddPlayer(int pID) : Message(ADD_PLAYER), playerID(pID) {}

    sf::Packet asPacket();
};

class ClientNotifyUDPPort : public Message
{
public:
    int playerID;
    unsigned short port;

    ClientNotifyUDPPort() : Message(CLIENT_NOTIFY_UDP_PORT) {}
    ClientNotifyUDPPort(sf::Packet);
    ClientNotifyUDPPort(int pID, unsigned short prt) : Message(CLIENT_NOTIFY_UDP_PORT), playerID(pID), port(prt)  {}

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
