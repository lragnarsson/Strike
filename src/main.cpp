
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.h"
#include "Player.h"
#include "GameState.h"
#include "Controller.h"
#include "Team.h"
#include "Weapon.h"

#include <iostream>

int main(int, char const**)
{
    // Create the main window
    //sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML-Playground", sf::Style::Fullscreen);
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML-Playground");
    window.setFramerateLimit(120);
    // let's define a view
    sf::View view(sf::FloatRect(0, 0, 500, 300));

    // activate it
    window.setView(view);

    // draw something to that view
    //window.draw(some_sprite);

    /*
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath("res/img/") + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath("res/img/") + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath("res/fonts/") + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setColor(sf::Color::Black);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath("res/sound/") + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

     
    
    // Play the music
    music.play();
     */


    
    Team blueTeam;
    Team redTeam;

    Weapon weapon1{5,30,10,1000,5000,10};

    Weapon weapon2{weapon1}; // just for lullz
    
    GameState Game;
    Player player1{1};
    Player player2{2};
    Controller controller;

    Game.addPlayer(&player1);
    Game.addPlayer(&player2); // this player does not have a controller. just for fun.

    blueTeam.addPlayer(&player1);
    redTeam.addPlayer(&player2);

    player2.setPosition(100.0f,100.0f);
    player1.setWeapon(&weapon1);

    controller.bindPlayer(&player1);
    controller.bindView(&view);

    // vertexArray test
    sf::VertexArray lines(sf::LinesStrip, 4);
    lines[0].position = sf::Vector2f(10, 0);
    lines[1].position = sf::Vector2f(20, 0);
    lines[2].position = sf::Vector2f(30, 5);
    lines[3].position = sf::Vector2f(40, 2);


    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();
/*
        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);
*/
        // Move the player, debug position in console
        controller.updatePlayerMoveVector();
        controller.playerRotate(window);
        controller.reloadWeapon();
        controller.playerFire();
        controller.updateView();

        window.setView(view);
        Game.draw(window);
        window.draw(lines);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
