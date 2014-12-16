/***************************************
Decal.h

Extention of sf::Sprite. Describes things to be drawn on the screen.

Written by:
Lage Ragnarsson
***************************************/

#ifndef _DECAL_
#define _DECAL_

#include <SFML/Graphics.hpp>

class Decal: public sf::Sprite {
public:
    Decal() = delete;
    explicit Decal(sf::Vector2f position, sf::Vector2f scale, sf::Texture* texture, sf::IntRect rect);
    ~Decal() = default;
};

class AnimatedDecal: public Decal {
public:
    AnimatedDecal() = delete;
    AnimatedDecal(sf::Vector2f position, sf::Vector2f scale, sf::Texture* spriteSheet,
                  sf::IntRect frameRect, unsigned int frameTime, unsigned int numberOfFrames,
                  bool permanent, unsigned int columns);
    ~AnimatedDecal() = default;
    bool animationComplete();
    void animate();
    bool isPermanent();

private:
    unsigned int frameTime_;
    unsigned int numberOfFrames_;
    unsigned int currentFrame_{0};
    unsigned int frameWidth_;
    unsigned int frameHeight_;
    bool permanent_;
    unsigned int columns_;
    sf::IntRect frameRect_;
    sf::Clock clock_;
    sf::Texture spriteSheet_;
};

#endif // _DECAL_
