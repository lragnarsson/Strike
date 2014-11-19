//
//  GameState.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "ResourcePath.hpp"
#include "GameState.h"
#include "Player.h"
#include "Team.h"

void GameState::addPlayer(Player* playerP) {

    players_.push_back(playerP);

}

GameState::GameState() {
    if (!mapTexture_.loadFromFile(resourcePath("res/img/") + "boat_lvl.bmp"))
        throw std::exception();
    mapSprite_.setTexture(mapTexture_);
}

void GameState::draw(sf::RenderWindow& window) {
    window.draw(mapSprite_);
    for (std::vector<Player*>::iterator it = players_.begin(); it != players_.end(); ++it){
        window.draw(**it); // calls draw for every player

        //it->draw(window, sf::RenderStates::RenderStates()); // calls draw with a default RenderState for all players
    }

}
