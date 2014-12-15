/***************************************
NetworkHandler.h

Class for recieving and sending messages between server and client.
Also Handles connections.

Written by:
Erik Sköld
Isak Wiberg
***************************************/

#ifndef _NETWORKHANDLER_
#define _NETWORKHANDLER_

#include "./Messages.h"
#include "./SecureVector.h"

#include <vector>
#include <map>

#include <SFML/Network.hpp>

class NetworkHandler
{
public:
    NetworkHandler();
    NetworkHandler(NetworkHandler&) = delete;
    ~NetworkHandler();

    NetworkHandler& operator=(const NetworkHandler& rhs) = delete;

    std::vector<Message*> getNewMessages();
    void addToOutbox(std::vector<Message*> messages);

    void checkForNewTcpConnections();
    bool connectToServer(std::string name, int teamID, sf::IpAddress);
    void initServer();
    void initClient();
    void update();

    void initRemotePlayers();

    void processInternalMessages();

    

private:

    unsigned short serverPort_ = 5060;
    sf::UdpSocket Usocket_; // fšr test endast
    
    sf::TcpListener listener;

    int clientIDcounter = 1;
    int teamID;
    std::string playerName;

    struct client_
    {
        int ID = -1;
        unsigned short UDPPort = -1;
        sf::TcpSocket* TCPSocket;
    };

    std::vector<client_> clients_;

    // the message-vectors are guarded by mutexlock
    SecureVector incomingMessages_;
    SecureVector outgoingMessages_;
    std::vector<Message*> internalMessages_;

    void recieveUDPPackets();
    void recieveTCPPackets();
    void sendUDPPacket(sf::Packet, int recieverID);
    void broadcastUDPPacket(sf::Packet);
    void sendTCPPacket(sf::Packet, int recieverID);
    void broadcastTCPPacket(sf::Packet);

    Message* unpackPacket(sf::Packet);
};

#endif // _NETWORKHANDLER_
