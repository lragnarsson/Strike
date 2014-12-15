#include "./HUD.h"

HUD::HUD()  {
    font_.loadFromFile(resourcePath("res/fonts/") + "sansation.ttf");

    health_.setFont(font_);
    health_.setColor(sf::Color::Red);
    health_.setStyle(sf::Text::Bold);
    health_.setCharacterSize(48);
    health_.setString("HP: ");

    ammo_.setFont(font_);
    ammo_.setColor(sf::Color::Red);
    ammo_.setStyle(sf::Text::Bold);
    ammo_.setCharacterSize(48);
    ammo_.setString("Ammo: ");
}

void HUD::setCrosshair(sf::Drawable* crosshair) {
    crosshair_ = crosshair;
}

sf::Drawable* HUD::getCrosshair() const {
    return crosshair_;
}

void HUD::setHealth(int health) {
    health_.setString("HP: " + std::to_string(health));
}

void HUD::setAmmo(int mag, int additional) {
    ammo_.setString("Ammo: " + std::to_string(mag) + " (" + std::to_string(additional) + ")");
}

void HUD::setPositions(sf::RenderTarget& target) {
    sf::Vector2u windowSize = target.getSize();
    health_.setPosition(target.mapPixelToCoords(sf::Vector2i(10, windowSize.y - health_.getLocalBounds().height * 2 - 10)));
    ammo_.setPosition(target.mapPixelToCoords(sf::Vector2i(10, windowSize.y - ammo_.getLocalBounds().height - 10)));
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*crosshair_, states);
    target.draw(health_, states);
    target.draw(ammo_, states);
}
