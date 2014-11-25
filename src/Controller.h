#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/System.hpp>
#include "Player.h"
//#include "Shot.h"

class Controller
{
public:
    Controller() = default;
    ~Controller();

    //std::vector<Shot*> playerFire();
    void playerMove(const sf::RenderWindow&);
    //void rotatePlayer(const sf::Window&);
    void bindPlayer(Player*);
    void bindView(sf::View*);
    void updateView();
protected:
    
private:
    sf::Vector2f moveVector_;
    Player* player_;
    sf::View* view_;
    sf::Clock clock_;
    

};

#endif // CONTROLLER_H
