#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/System.hpp>
#include "Player.h"

class Controller
{
public:
    Controller() = default;
    ~Controller() = default;

    void movePlayer(const sf::RenderWindow&);
    //void rotatePlayer(const sf::Window&);
    void bindPlayer(Player*);
    void bindView(sf::View*);
    void updateView();
protected:
    
private:
    sf::Vector2f moveVector_;
    Player* player_;
    sf::View* view_;
    

};

#endif // CONTROLLER_H
