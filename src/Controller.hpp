#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/System.hpp>
#include "Player.h"

class Controller
{
    public:
        Controller() = default;
        ~Controller() = default;

        void movePlayer();
        void bindPlayer(Player*);
    protected:
    private:
        sf::Vector2f moveVector_;
        Player* player_;

};

#endif // CONTROLLER_H
