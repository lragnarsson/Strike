#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <exception>
#include <sstream>
#include <string>
#include "./ResourcePath.h"
#include "./Client.h"
#include "Server.h"

const std::string valid_cmds("hcsql");
char command;

void startClient(std::string name, unsigned int team, std::string ip) {
    std::cout << name << "  " << team << "  " << ip << std::endl;

    Client client;
    if (client.connectToServer(name, team, sf::IpAddress(ip)))
        client.run();
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

void printHelp() {
    std::cout << "  h                            Print this help messsage\n";
    std::cout << "  c <name> <team> <ip>         Start a game client\n";
    std::cout << "  s <maxplayers> <mapname>     Start a game server\n";
    std::cout << "  q                            Quit Strike\n";
    std::cout << "  l                            Start local client\n";
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
            unsigned int team;
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
    std::cout << "Strike: Local Defensive\ntype h for help." << std::endl;
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
