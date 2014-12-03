#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "ResourcePath.h"
#include "Client.h"
#include <iostream>

int main(int, char const**) {
    Client client;
    client.run();
    /*
    Weapon weapon{10,30,10,10,500,10};
    SemiAutomaticWeapon semi{10,30,10,10,500,10};
    Shotgun shotgun{5,20,5,50,1000,5,6};
    */

    return EXIT_SUCCESS;
}
