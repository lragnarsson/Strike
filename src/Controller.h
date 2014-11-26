#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/System.hpp>
#include "Player.h"
#include <vector>
#include "Shot.h"

class Controller{
public:
    Controller() = default;
    ~Controller();
    
    void updatePlayerMoveVector();
    void playerRotate(const sf::RenderWindow&);
    void bindPlayer(Player*);
    void bindView(sf::View*);
    void updateView();
    std::vector<Shot*> playerFire();
protected:
    
private:
    sf::Vector2f moveVector_;
    Player* player_;
    sf::View* view_;
    sf::Clock clock_;
    sf::Vector2i lastMousePosition_;
    float sqrt2{1.4142135};

};

#endif // CONTROLLER_H
