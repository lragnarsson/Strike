/***************************************
NetworkHandler - Klass för att hålla koll på anslutna klienter och att skicka och ta emot data.

Skriven av:
Erik Sköld
***************************************/

#include <SFML/Network.hpp>

#include "NetworkHandler.h"
#include "MessageCodes.h"
#include "Messages.h"

#include <iostream>
#include <string>

NetworkHandler::NetworkHandler()
{

}


NetworkHandler::~NetworkHandler()
{
    for (auto& client : clients_)
    {
        client.TCPSocket->disconnect();
        delete client.TCPSocket;
    }
}

std::vector<Message*> NetworkHandler::getNewMessages()
{
    std::vector<Message*> tmp;
    tmp.swap(messages_);
    return tmp;
}


void NetworkHandler::recieveUDPPackets()
{
    sf::Packet recievePacket;
    sf::IpAddress remoteIP;
    unsigned short remotePort;

    if (Usocket_.receive(recievePacket, remoteIP, remotePort) == sf::Socket::Done)
    {
        std::cout << "Recieved one UDP packet from: " << remoteIP.toString() << std::endl;
        messages_.push_back(unpackPacket(recievePacket));
    }
}

void NetworkHandler::recieveTCPPackets()
{
    sf::Packet recievePacket;

    for (auto& client : clients_)
    {
        if (client.TCPSocket->receive(recievePacket) == sf::Socket::Done)
        {
            std::cout << "Recieved one TCP packet from: " << client.TCPSocket->getRemoteAddress().toString() << std::endl;
            Message* m = unpackPacket(recievePacket);
            //TODO sort internal
            messages_.push_back(unpackPacket(recievePacket));
        }
    }
}


void NetworkHandler::sendUDPPacket(sf::Packet data, int clientID)
{
    for (auto& client : clients_)
    {
        if (client.ID == clientID)
        {
            Usocket_.send(data, client.TCPSocket->getRemoteAddress(), client.TCPSocket->getRemotePort());
        }

    }
}

void NetworkHandler::broadcastUDPPacket(sf::Packet data)
{
    for (auto& client : clients_)
    {
       Usocket_.send(data, client.TCPSocket->getRemoteAddress(), client.TCPSocket->getRemotePort());
    }
}

void NetworkHandler::sendTCPPacket(sf::Packet data, int clientID)
{
    for (auto& client : clients_)
    {
        if (client.ID == clientID)
        {
            client.TCPSocket->send(data);
        }

    }
}

void NetworkHandler::broadcastTCPPacket(sf::Packet data)
{
    for (auto& client : clients_)
    {
        client.TCPSocket->send(data);
    }
}

void NetworkHandler::checkForNewTcpConnections()
{
    sf::TcpSocket*  newConn = new sf::TcpSocket();
    if (listener.accept(*newConn) != sf::Socket::Done)
    {
        delete newConn;
    }
    else
    {
        std::cout << "Ny klient ansluten! Ip: " << newConn->getRemoteAddress() << " Port: " << newConn->getRemotePort() << std::endl;

        client_ newClient;
        newClient.ID = clientIDcounter++;
        newClient.TCPSocket = newConn;

        newClient.TCPSocket->setBlocking(false);

        ServerAcceptConnection sac(newClient.ID);
        newClient.TCPSocket->send(sac.asPacket(); //Send SERVER_ACCEPT_CONNECTION

        messages_.push_back(new AddPlayer(newClient.ID));

        clients_.push_back(std::move(newClient));

        for (auto& client : clients_)
        {
            std::cout << "Anlutna ID:n :" << client.ID << std::endl;
        }
    }

}

void NetworkHandler::connectToServer(sf::IpAddress ip)
{

    sf::TcpSocket* conn = new sf::TcpSocket();
    if (conn->connect(ip, serverPort_) != sf::Socket::Done)
    {
        std::cout << "Kunde inte ansluta till servern" << std::endl;
        delete conn;
    }
    else
    {
        std::cout << "Ansluten!" << std::endl;
    }

    conn->setBlocking(false);

    client_ serverClient;

    serverClient.ID = 0;
    serverClient.UDPPort = serverPort_;
    serverClient.TCPSocket = conn;

    clients_.push_back(serverClient);
}

void NetworkHandler::initServer()
{
    listener.setBlocking(false);
    listener.listen(serverPort_);
    Usocket_.bind(serverPort_);
}

Message* NetworkHandler::unpackPacket(sf::Packet packet)
{
    int header;
    packet >> header;
    switch(header)
    {
        case CLIENT_NOTIFY_UDP_PORT:
        {
            return new ClientNotifyUDPPort(packet);
            break;
        }
        case SERVER_ACCEPT_CONNECTION:
        {
            return new ServerAcceptConnection(packet);
            break;
        }
        case ADD_PLAYER:
        {
            return new AddPlayer(packet);
            break;
        }
        case CONSOLE_PRINT_STRING:
        {
            return new ConsolePrintString{packet};
            break;
        }
    }
}


