#include "NetworkHandler.h"
#include "MessageCodes.h"


#include <iostream>
#include <string>

#include <stdlib.h>

NetworkHandler nh;

void client()
{
    std::vector<sf::Packet> recievedPackets_;
    std::vector<Message*> recievedMessages_;
    //sf::IpAddress addr("130.236.227.231");
    nh.connectToServer(sf::IpAddress::getLocalAddress());
    while(true)
    {
        nh.recieveTCPPackets();
        recievedMessages_ = nh.getNewMessages();
        //std::cout << "recievedMessages_ innehåller " << recievedMessages_.size() << " element" << std::endl;


        for (Message* message : recievedMessages_)
        {
            if (message->header == CONSOLE_PRINT_STRING)
            {
                std::cout << message->header << std::endl;
                std::cout << static_cast<ConsolePrintString*>(message)->str << std::endl;
            }
            if (message->header == SERVER_ACCEPT_CONNECTION)
            {
                static_cast<ServerAcceptConnection*> (message);
                ClientNotifyUDPPort cnudpp{message->playerID, nh.Usocket_.getLocalPort()};
                nh.sendTCPPacket(cnudpp.asPacket(),0);
            }
        }

        sf::sleep(sf::milliseconds(10));

    /*
        if (recievedMessages_.size() > 0)
            {
                std::cout << "Fick ett paket med header: " << recievedMessages_[0]->header << std::endl;
                std::cout << static_cast<ConsolePrintString*>(recievedMessages_[0])->str << std::endl;
            }
    */

    }
}

void server()
{
    nh.initServer();
    std::string tmp;
    while(true)
    {
        nh.checkForNewTcpConnections();
        std::getline(std::cin, tmp);

        ConsolePrintString cps;
        cps.str = tmp;

        std::cout << cps.header << " " << cps.str << std::endl;
        sf::Packet p = cps.asPacket();
        int i;
        std::string s;
        p >> i >> s;
        std::cout << i << " " << s << std::endl;
        nh.broadcastTCPPacket(cps.asPacket());
    }
}

void testMessages()
{
    ConsolePrintString* m1 = new ConsolePrintString();
    m1->str = "Test";
    std::cout << "Paket av typ: " << m1->header << "med innehåll: " << m1->str << std::endl;
    delete m1;
}


int main()
{
    //testMessages();
    client();
    //server();
}

