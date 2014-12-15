/***************************************
Shot.h

Class for representing shots.

Written by:
Filip Östman
Rasmus Vilhelmsson
***************************************/

#ifndef _SHOT_
#define _SHOT_

#include "./GeomUtils.h"
#include <SFML/Graphics.hpp>

class Shot: public sf::Drawable {
public:
    Shot() = default;
    Shot(int clientID, sf::Vector2f origin, sf::Vector2f direction, sf::Vector2f endPoint, int damage);
    Shot(int clientID, Ray ray_, sf::Vector2f endPoint, int damage);
    Shot(const Shot& shot) = default;
    virtual ~Shot() = default;

    int getDamage();
    void setEndPoint(sf::Vector2f);
    sf::Vector2f getEndPoint();
    void setTimestamp(sf::Time);
    sf::Time getTimestamp() const;
    sf::Vector2f getOrigin() const;
    sf::Vector2f getDirection() const;
    Ray getRay() const;
    int getClientID() const;
    int getTargetID();
    void setTargetID(int id);
    bool getSoundstatus() const;
    void setSoundstatus();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    int timestamp_;  // in milliseconds
    int clientID_;
    sf::Vector2f origin_;
    sf::Vector2f direction_;
    sf::Vector2f endPoint_;
    int damage_;
    int targetID_{-1};
    bool soundHasPlayed_{false};
};

#endif // _SHOT_
