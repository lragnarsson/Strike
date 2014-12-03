/***************************************
NetworkHandler - Klass för att hålla koll på anslutna klienter och att skicka och ta emot data.

Skriven av:
Erik Sköld
***************************************/

#ifndef NETWORKHANDLER_H
#define NETWORKHANDLER_H

#include <SFML/Network.hpp>

#include "Messages.h"

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
        void recieveUDPPackets();
        void recieveTCPPackets();
        void sendUDPPacket(sf::Packet);
        void sendTCPPacket(sf::Packet);

        void checkForNewTcpConnections();
        void connectToServer(sf::IpAddress);
        void initServer();

    private:
        unsigned short serverPort_ = 5060;

        sf::UdpSocket Usocket_;
        sf::TcpListener listener;

        int clientIDcounter = 1;

        struct client_
        {
            int ID = -1;
            unsigned short UDPPort = -1;
            sf::TcpSocket* TCPSocket;
        };

        std::vector<client_> clients_;
        std::vector<Message*> messages_;
        std::vector<Message*> internalMessages_;

        std::map<int, int> playerLatestUpdate_;

        Message* unpackPacket(sf::Packet);
};

#endif // NETWORKHANDLER_H
