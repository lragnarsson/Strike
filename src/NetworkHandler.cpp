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


void NetworkHandler::recieveUDPPackets() //OUTDATED
{
    sf::Packet recievePacket;
    sf::IpAddress remoteIP;
    unsigned short remotePort;

    std::string message;

    if (Usocket_.receive(recievePacket, remoteIP, remotePort) == sf::Socket::Done)
    {
        recievePacket >> message;
        std::cout << "Fick ett paket innehållande strängen: " << message << "från " << remoteIP.toString() << std::endl;
    }
}

void NetworkHandler::recieveTCPPackets()
{
    sf::Packet recievePacket;

    std::string message;

    for (auto& client : clients_)
    {
        if (client.TCPSocket->receive(recievePacket) == sf::Socket::Done)
        {
            std::cout << "Recieved one TCP packet from: " << client.TCPSocket->getRemoteAddress().toString() << std::endl;
            messages_.push_back(unpackPacket(recievePacket));
        }
    }
}


void NetworkHandler::sendUDPPacket(sf::Packet packet)
{

}

void NetworkHandler::sendTCPPacket(sf::Packet data)
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
        newConn->setBlocking(false);

        std::cout << "Ny klient ansluten! Ip: " << newConn->getRemoteAddress() << " Port: " << newConn->getRemotePort() << std::endl;

        client_ newClient;
        newClient.ID = clientIDcounter++;
        newClient.TCPSocket = newConn;

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
    case CONSOLE_PRINT_STRING:
        {
            return new ConsolePrintString{packet};
            break;
        }
    }
}


