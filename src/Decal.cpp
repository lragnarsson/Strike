#include "./Decal.h"
#include <iostream>

Decal::Decal(sf::Vector2f position, sf::Vector2f scale, sf::Texture* texture, sf::IntRect rect): sf::Sprite(*texture, rect) {
    setPosition(position);
    setScale(scale);
    setOrigin((float)rect.width / 2.f, (float)rect.height / 2.f);
}

AnimatedDecal::AnimatedDecal(sf::Vector2f position, sf::Vector2f scale, sf::Texture* spriteSheet,
                             sf::IntRect frameRect, unsigned int frameTime, unsigned int numberOfFrames,
                             bool permanent, unsigned int columns)
    : Decal(position, scale, spriteSheet, frameRect), frameTime_(frameTime),
      numberOfFrames_(numberOfFrames), frameWidth_(frameRect.width),
      frameHeight_(frameRect.height), permanent_(permanent) , columns_(columns) {}

bool AnimatedDecal::animationComplete() {
    return currentFrame_ == numberOfFrames_;
}

bool AnimatedDecal::isPermanent() {
    return permanent_;
}
void AnimatedDecal::animate() {
    if (!animationComplete() && clock_.getElapsedTime().asMilliseconds() >= frameTime_) {
      setTextureRect(sf::IntRect(frameWidth_ * (currentFrame_ % columns_),
                                 frameHeight_ * (currentFrame_ / columns_),
                                 frameWidth_, frameHeight_));
      currentFrame_++;
      clock_.restart();
    }
}
