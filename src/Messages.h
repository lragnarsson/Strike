/***************************************
Messages.h

Polymorph class structure for messages to be passed over the internet or localy.

Written by:
Erik Sköld
Isak Wiberg
***************************************/

#ifndef _MESSAGES_
#define _MESSAGES_

#include "./MessageCodes.h"
#include "./GeomUtils.h"

#include <string>

#include <SFML/Network.hpp>

class Message
{
public:
    virtual ~Message() = default;

    const int header;
    const int protocol;
    int reciever; //-1 means broadcast

    virtual sf::Packet asPacket() = 0;

protected:
    Message(int header, int protocol, int reciever) : header(header), protocol(protocol), reciever(reciever) {}
    Message(const Message&) = delete;
};

class ServerAcceptConnection : public Message
{
public:

    int playerID;

    ServerAcceptConnection() = delete;
    ServerAcceptConnection(sf::Packet);
    ServerAcceptConnection(int pID, int reciever = -1) : Message(SERVER_ACCEPT_CONNECTION, TCP, reciever), playerID(pID) {}

    sf::Packet asPacket() override;
};

class AddPlayer : public Message
{
public:

    int playerID;
    int teamID;
    std::string name;

    AddPlayer() = delete;
    AddPlayer(sf::Packet);
    AddPlayer(int pID, int tID, std::string name, int reciever = -1) : Message(ADD_PLAYER, TCP, reciever), playerID(pID), teamID(tID), name(name) {}

    sf::Packet asPacket() override;
};

class ClientNotifyUDPPort : public Message
{
public:

    int playerID;
    unsigned short port;

    ClientNotifyUDPPort() = delete;
    ClientNotifyUDPPort(sf::Packet);
    ClientNotifyUDPPort(int pID, unsigned short prt, int reciever = -1) : Message(CLIENT_NOTIFY_UDP_PORT, TCP, reciever), playerID(pID), port(prt)  {}

    sf::Packet asPacket() override;
};

class ConsolePrintString : public Message
{
public:

    std::string str;

    ConsolePrintString() = delete;
    ConsolePrintString(sf::Packet);
    ConsolePrintString(std::string s, int reciever = -1) : Message(CONSOLE_PRINT_STRING, TCP, reciever), str(s) {}

    sf::Packet asPacket() override;
};

class InitialInformation : public Message
{
public:

    int clientID;
    int teamID;
    std::string clientName;

    InitialInformation() = delete;
    InitialInformation(sf::Packet);
    InitialInformation(int clientID, int teamID, std::string clientName, int reciever = -1)
    :  Message(INITIAL_INFORMATION, TCP, reciever), clientID(clientID), teamID(teamID), clientName(clientName) {}

    sf::Packet asPacket();

};


class PlayerUpdate : public Message
{
public:

    int playerID;
    float xCoord;
    float yCoord;
    float rotation;
    int health;

    PlayerUpdate() = delete;
    PlayerUpdate(sf::Packet);
    PlayerUpdate(float x, float y, float r, int h, int reciever = -1) : Message(PLAYER_UPDATE, UDP, reciever),
        xCoord(x), yCoord(y), rotation(r), health(h) {}

    sf::Packet asPacket() override;
};

class AddShot : public Message
{
public:

    int clientID;
    float originXPos;
    float originYPos;
    float directionXPos;
    float directionYPos;
    float endPointXPos;
    float endPointYPos;
    int damage;

    AddShot() = delete;
    AddShot(sf::Packet);
    AddShot(int cID, float origXP, float origYP, float dirXP, float dirYP, float endPXP, float endPYP, int dmg, int reciever = -1) :
        Message(ADD_SHOT, UDP, reciever), clientID(cID), originXPos(origXP), originYPos(origYP), directionXPos(dirXP),
            directionYPos(dirYP), endPointXPos(endPXP), endPointYPos(endPYP), damage(dmg) {}

    sf::Packet asPacket() override;
};

class RoundRestart : public Message
{
public:

    int tTeamScore;
    int ctTeamScore;
    int spawnpointIndex;

    RoundRestart() = delete;
    RoundRestart(sf::Packet);
    RoundRestart(int tTS, int ctTS, int spawnPInd, int reciever = -1) : Message(ROUND_RESTART, TCP, reciever), tTeamScore(tTS), ctTeamScore(ctTS), spawnpointIndex(spawnPInd) {}

    sf::Packet asPacket() override;
};
#endif // _MESSAGES_
