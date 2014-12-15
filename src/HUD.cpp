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

    score_.setFont(font_);
    score_.setColor(sf::Color::Red);
    score_.setStyle(sf::Text::Bold);
    score_.setCharacterSize(48);
    score_.setString("Scores: ");
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

void HUD::setScore(int tTeam, int ctTeam) {
    score_.setString("T: " + std::to_string(tTeam) + ", CT: " + std::to_string(ctTeam));
}

void HUD::setPositions(sf::RenderTarget& target) {
    sf::Vector2u windowSize = target.getSize();
    health_.setPosition(target.mapPixelToCoords(sf::Vector2i(10, windowSize.y - health_.getLocalBounds().height * 2 - 10)));
    ammo_.setPosition(target.mapPixelToCoords(sf::Vector2i(10, windowSize.y - ammo_.getLocalBounds().height - 10)));
    score_.setPosition(target.mapPixelToCoords(sf::Vector2i(10, windowSize.y - score_.getLocalBounds().height * 3 - 10)));
}

void HUD::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*crosshair_, states);
    target.draw(health_, states);
    target.draw(ammo_, states);
    target.draw(score_, states);
}
