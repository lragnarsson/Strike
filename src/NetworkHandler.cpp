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
#include <exception>
#include <thread>


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
    return incomingMessages_.stealNewMessages();
}

void NetworkHandler::addToOutbox(std::vector<Message*> messages)
{
    outgoingMessages_.append(messages);
}

void NetworkHandler::update()
{
    recieveTCPPackets();
    recieveUDPPackets();

    processInternalMessages();

    std::vector<Message*> outboundMessages {outgoingMessages_.stealNewMessages()};
    for (auto& outgoingMessage : outboundMessages)
    {
        sf::Packet pkt;
        pkt = outgoingMessage->asPacket(); // polymorph madness
        if (outgoingMessage->protocol == TCP)
        {
            if (outgoingMessage->reciever == -1)
                broadcastTCPPacket(pkt);
            sendTCPPacket(pkt, outgoingMessage->reciever);
        }
        else if (outgoingMessage->protocol == UDP)
        {
            if (outgoingMessage->reciever == -1)
                broadcastUDPPacket(pkt);
            sendUDPPacket(pkt, outgoingMessage->reciever);
        }
        else         {
            std::cout << "I refuse to send via undefined protocol! (message protocol was not defined in update)" << std::endl;
        }
    }
}

void NetworkHandler::recieveUDPPackets()
{
    sf::Packet recievePacket;
    sf::IpAddress remoteIP;
    unsigned short remotePort;

    if (Usocket_.receive(recievePacket, remoteIP, remotePort) == sf::Socket::Done)
    {
        std::cout << "Recieved one UDP packet from: " << remoteIP.toString() << std::endl;
        incomingMessages_.push_back(unpackPacket(recievePacket));
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
            std::cout << m->header << std::endl;
            if (m->header < INTERNAL_MESSAGE_LIMIT)
            {
                std::cout << "was internal message" << std::endl;
                internalMessages_.push_back(m);
            }
            else
            {
                std::cout << "was normal message" << std::endl;
                incomingMessages_.push_back(m);
            }
        }
    }
}


void NetworkHandler::sendUDPPacket(sf::Packet data, int clientID)
{
    bool recieverFound {false};
    for (auto& client : clients_)
    {
        if (client.ID == clientID)
        {
            Usocket_.send(data, client.TCPSocket->getRemoteAddress(), client.UDPPort);
            recieverFound = true;
        }
    }
    if (!recieverFound)
        std::cout << "No matching client found for reciever of message." << std::endl;
}

void NetworkHandler::broadcastUDPPacket(sf::Packet data)
{
    for (auto& client : clients_)
    {
        std::cout << "Skickar udp till klient " << client.ID << "på port " << client.UDPPort << std::endl;
        Usocket_.send(data, client.TCPSocket->getRemoteAddress(), client.UDPPort);
    }
}

void NetworkHandler::sendTCPPacket(sf::Packet data, int clientID)
{
    bool recieverFound {false};
    for (auto& client : clients_)
    {
        if (client.ID == clientID)
        {
            recieverFound = true;
            client.TCPSocket->send(data);
        }

    }
    if (!recieverFound)
        std::cout << "No matching client found for reciever of message." << std::endl;

}

void NetworkHandler::broadcastTCPPacket(sf::Packet data)
{
    for (auto& client : clients_)
    {
        client.TCPSocket->send(data);
    }
}

void NetworkHandler::checkForNewTcpConnections() //Server only
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
        sf::Packet packet = sac.asPacket();
        newClient.TCPSocket->send(packet); //Send SERVER_ACCEPT_CONNECTION


        clients_.push_back(std::move(newClient));

        for (auto& client : clients_)
        {
            std::cout << "Anlutna ID:n :" << client.ID << std::endl;
        }
    }

}

bool NetworkHandler::connectToServer(std::string name, int newTeamID, sf::IpAddress ip)
{
    initClient();
    playerName = name;
    teamID = newTeamID;
    sf::TcpSocket* conn = new sf::TcpSocket();
    if (conn->connect(ip, serverPort_) != sf::Socket::Done)
    {
        std::cout << "Kunde inte ansluta till servern" << std::endl;
        delete conn;
        return false;
    }
    else
    {
        std::cout << "Ansluten!" << std::endl;


        conn->setBlocking(false);

        client_ serverClient;

        serverClient.ID = 0;
        serverClient.UDPPort = serverPort_;
        serverClient.TCPSocket = conn;

        clients_.push_back(serverClient);

        return true;
    }
}

void NetworkHandler::initServer()
{
    listener.setBlocking(false);
    listener.listen(serverPort_);
    Usocket_.bind(serverPort_);
}

void NetworkHandler::initClient()
{
    Usocket_.setBlocking(false);
    Usocket_.bind(sf::Socket::AnyPort);
}

/*HAS STOPPED WORKING!!! FIXING IN PROGRESS
void NetworkHandler::initRemotePlayers() //Server only
{
    AddPlayer ap {

    for (auto& client : clients_)
        {
            ap.playerID = client.ID;
            broadcastTCPPacket(ap.asPacket());
        }
}
*/

Message* NetworkHandler::unpackPacket(sf::Packet packet)
{
    int header;
    packet >> header;
    switch(header)
    {
        case PLAYER_UPDATE:
        {
            return new PlayerUpdate(packet);
            break;
        }
        case ADD_SHOT:
        {
            return new AddShot(packet);
            break;
        }
        case ROUND_RESTART:
        {
            return new RoundRestart(packet);
            break;
        }
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
        default:
        {
            throw std::exception();
        }
    }
}

void NetworkHandler::processInternalMessages()
{
    for (Message* internalMessage : internalMessages_)
        {
            switch(internalMessage->header)
            {
            case CLIENT_NOTIFY_UDP_PORT:
            {
                std::cout << "Found CLIENT_NOTIFY_UDP_PORT message" << std::endl;
                for (auto& client : clients_)
                {
                    if (client.ID == static_cast<ClientNotifyUDPPort*>(internalMessage)->playerID)
                    {
                        std::cout << "Updated player " << static_cast<ClientNotifyUDPPort*>(internalMessage)->playerID <<
                                ":s UDP port to " << static_cast<ClientNotifyUDPPort*>(internalMessage)->port << std::endl;

                        client.UDPPort = static_cast<ClientNotifyUDPPort*>(internalMessage)->port;
                        break;
                    }
                }

                break;
            }
            case SERVER_ACCEPT_CONNECTION:
                {
                    ClientNotifyUDPPort cnudpp{static_cast<ServerAcceptConnection*>(internalMessage)->playerID, Usocket_.getLocalPort(), 0};
                    sendTCPPacket(cnudpp.asPacket(), 0);
                    std::cout << "Recieved server_accept_connection and returned ClientNotifyUDPPort. \n"
                    << "playerID, localPort: " << static_cast<ServerAcceptConnection*>(internalMessage)->playerID << ", " << Usocket_.getLocalPort() << "\n";

                    int myPlayerID = static_cast<ServerAcceptConnection*>(internalMessage)->playerID;

                    AddPlayer ap{myPlayerID, teamID, playerName, 0};
                    sendTCPPacket(ap.asPacket(), 0);

                    std::cout << "Sent AddPlayer message to server." << std::endl;
                }

            }

        }

        internalMessages_.clear();
}


