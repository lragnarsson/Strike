#include "./Decal.h"
#include <iostream>

Decal::Decal(sf::Vector2f position, sf::Texture texture, sf::IntRect rect): sf::Sprite(texture, rect) {
    setPosition(position);
}

AnimatedDecal::AnimatedDecal(sf::Vector2f position, sf::Texture spriteSheet, sf::IntRect frameRect, int frameTime, unsigned int numberOfFrames)
    : Decal(position, spriteSheet, frameRect), frameTime_(frameTime), numberOfFrames_(numberOfFrames) {}

bool AnimatedDecal::animationComplete() {
    return currentFrame_ == numberOfFrames_;
}

void AnimatedDecal::animate() {
    if (!animationComplete() && clock_.getElapsedTime().asMilliseconds() >= frameTime_) {
        frameRect_.left = currentFrame_ * frameRect_.width;
        setTextureRect(frameRect_);
        currentFrame_++;
        clock_.restart();
    }
}
