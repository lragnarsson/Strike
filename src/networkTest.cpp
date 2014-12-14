#include "NetworkHandler.h"
#include "MessageCodes.h"


#include <iostream>
#include <string>

#include <stdlib.h>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/chrono/chrono.hpp>

/*
NetworkHandler nh;

void client()
{
    std::vector<sf::Packet> recievedPackets_;
    std::vector<Message*> recievedMessages_;
    sf::IpAddress addr("130.236.210.102");
    nh.initClient();
    nh.connectToServer(addr);

    while(true)
    {
        nh.recieveTCPPackets();
        for (int i = 0; i < 5; i++)
        {
            nh.recieveUDPPackets();
            sf::sleep(sf::milliseconds(1000));
        }


        recievedMessages_ = nh.getNewMessages();
        //std::cout << "recievedMessages_ innehÂller " << recievedMessages_.size() << " element" << std::endl;


        for (Message* message : recievedMessages_)
        {
            if (message->header == CONSOLE_PRINT_STRING)
            {
                std::cout << message->header << std::endl;
                std::cout << static_cast<ConsolePrintString*>(message)->str << std::endl;
            }
            if (message->header == SERVER_ACCEPT_CONNECTION)
            {
                // här måste detta meddelandes playerID sparas till serverobjektet
                ClientNotifyUDPPort cnudpp{static_cast<ServerAcceptConnection*>(message)->playerID, nh.Usocket_.getLocalPort()};
                nh.sendTCPPacket(cnudpp.asPacket(), 0);
                std::cout << "Recieved server_accept_connection and returned ClientNotifyUDPPort. \n"
                << "playerID, localPort: " << static_cast<ServerAcceptConnection*>(message)->playerID << ", " << nh.Usocket_.getLocalPort() << std::endl;
            }
            if (message->header == ADD_PLAYER)
            {
                std::cout << "Add player with id: " << static_cast<AddPlayer*>(message)->playerID << "\n";
            }
        }

        sf::sleep(sf::milliseconds(100));

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
*/

boost::mutex m;

void thrd1()
{
    for (int i = 0; i < 10; i++)
    {
        m.lock();
        std::cout << "Thread1" << std::endl;
        m.unlock();
        boost::this_thread::sleep_for( boost::chrono::seconds(1) );
    }
}

void thrd2()
{
    for (int i = 0; i < 10; i++)
    {
        m.lock();
        std::cout << "Thread2" << std::endl;
        m.unlock();
        boost::this_thread::sleep_for( boost::chrono::seconds(2) );
    }
}


void testThread()
{
    std::cout << "Starting 2 boost threads" << std::endl;
    boost::thread t1(thrd1);
    boost::thread t2(thrd2);

    t1.join();
    t2.join();

    std::cout << "Both threads ended" << std::endl;



}

int main()
{
    //testMessages();
    testThread();
    //client();
    //server();
}

