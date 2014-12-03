#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.h"
#include "Client.h"
#include <iostream>

int main(int, char const**) {
    Client client;
    client.run();

    return EXIT_SUCCESS;
}
