#ifndef _HUD_
#define _HUD_

#include "./ResourcePath.h"

#include <SFML/Graphics.hpp>

class HUD : public sf::Drawable
{
public:
    HUD();
    ~HUD() = default;
    void setCrosshair(sf::Drawable* cosshair);
    sf::Drawable* getCrosshair() const;
    void setHealth(int health);
    void setAmmo(int mag, int additional);
    void setScore(int tTeam, int ctTeam);
    void setPositions(sf::RenderTarget& target);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Font font_;
    sf::Drawable* crosshair_;
    sf::Text health_;
    sf::Text ammo_;
    sf::Text score_;
};

#endif // HUD

