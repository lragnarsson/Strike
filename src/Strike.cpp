/***************************************
Strike.cpp

Main entry to the game. Has a simple command line menu to start either a server or a client.

Written by:
Lage Ragnarsson
***************************************/

#include "./ResourcePath.h"
#include "./Client.h"
#include "./Server.h"

#include <iostream>
#include <exception>
#include <sstream>
#include <string>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

const std::string valid_cmds("hcsql");
char command;
std::map<std::string, sf::Texture*> Client::textures_;
std::map<std::string, sf::SoundBuffer*> Client::soundBuffers_;

void startClient(std::string name, std::string team, std::string ip) {
    std::cout << name << "  " << team << "  " << ip << std::endl;

    Client client;
    unsigned int intteam;
    if (team == "T")
        intteam = 0;
    else
        intteam = 1;
    if (client.connectToServer(name, intteam, sf::IpAddress(ip))) {
        client.run();
    }
    else
        std::cout << "Could not connect to IP: " << ip << std::endl;
}
void startLocalClient(std::string name, unsigned int team) {
    std::cout << name << "  " << team << std::endl;
    Client client;
    client.run();
}
void startServer(unsigned int maxPlayers, std::string mapName) {
    std::cout << maxPlayers << "  " << mapName << "\nServer IP is: "
    << sf::IpAddress::getPublicAddress(sf::seconds(2.0f)) << std::endl;
    Server server;
    server.run();
}

bool validCommand() {
  if (valid_cmds.find(command) == std::string::npos) {
      std::cout << "Invalid command: " << command << "\n";
      return false;
  }
    return true;
}

void networkFunction() {
    while (true) {
        
    }
}

void printHelp() {
    std::cout << "  h                            Print this help messsage\n";
    std::cout << "  c <name> <T or CT> <ip>      Start a game client and connect to server\n";
    std::cout << "  s                            Start a game server\n";
    std::cout << "  l                            Start local client\n";
    std::cout << "  q                            Quit Strike\n";
}

void getCommand() {
    std::cout << ">> ";
    std::string tmp;
    std::getline(std::cin, tmp);
    std::istringstream ss{tmp};
    ss >> command;
    command = std::tolower(command);

    if (!validCommand())
        return;

    try {
        if (command == 'h')
            printHelp();
        else if (command == 'c') {
            std::string name;
            std::string team;
            std::string ip;
            ss >> name >> team >> ip;
            startClient(name, team, ip);
        } else if (command == 's') {
            unsigned int maxPlayers;
            std::string mapName;
            ss >> maxPlayers >> mapName;
            startServer(maxPlayers, mapName);
        } else if (command == 'q') {
            std::cout << "Thank you for playing Strike." << std::endl;
        } else if (command == 'l'){
            std::string name;
            unsigned int team;
            ss >> name >> team;
            startLocalClient(name, team);
        } else {
            std::cout << "The menu is broken!\n" << std::endl;
        }
    }
    catch(const std::exception& e) {
        std::cout << "NOOOO!" << e.what() << std::endl;
    }
}

void runMenu() {
    std::cout << "\n\nWelcome to Strike: Local Defensive\n\nA game created by:\nJesper Otterholm\nLage Ragnarsson\nErik Sköld\nRasmus Vilhelmsson\nIsak Wiberg\nFilip Östman\n\nType h for help." << std::endl;
    std::istringstream args;
    do {
        try {
            getCommand();
        }
        catch(const std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    } while (command != 'q');
}

int main(int, char const**) {
    runMenu();
    return EXIT_SUCCESS;
}
