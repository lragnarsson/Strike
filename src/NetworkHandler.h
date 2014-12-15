
#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <SFML/Network.hpp>

#include "Messages.h"
#include "SecureVector.h"

#include <vector>
#include <map>

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
    sf::UdpSocket Usocket_; // f�r test endast
    
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

    std::map<int, int> playerLatestUpdate_;

    void recieveUDPPackets();
    void recieveTCPPackets();
    void sendUDPPacket(sf::Packet, int recieverID);
    void broadcastUDPPacket(sf::Packet);
    void sendTCPPacket(sf::Packet, int recieverID);
    void broadcastTCPPacket(sf::Packet);

    Message* unpackPacket(sf::Packet);
};

#endif // NETWORKHANDLER_H
