// Decal.h
#ifndef __Strike__Decal__
#define __Strike__Decal__
#include <SFML/Graphics.hpp>
/*
 * 
 */

class Decal: public sf::Sprite {
public:
    Decal() = delete;
    explicit Decal(sf::Vector2f position, sf::Texture texture, sf::IntRect rect);
    ~Decal() = default;
};

class AnimatedDecal: public Decal {
public:
    AnimatedDecal() = delete;
    AnimatedDecal(sf::Vector2f position, sf::Texture spriteSheet, sf::IntRect frameRect,
                  int frameTime, unsigned int numberOfFrames);
    ~AnimatedDecal() = default;
    bool animationComplete();
    void animate();

private:
    int frameTime_;
    unsigned int numberOfFrames_;
    unsigned int currentFrame_{0};
    sf::IntRect frameRect_;
    sf::Clock clock_;
    sf::Texture spriteSheet_;
};

#endif /* defined(__Strike__Decal__) */
