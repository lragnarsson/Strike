//
//  GameState.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "ResourcePath.h"
#include "GameState.h"
#include "Player.h"
#include "Team.h"


GameState::GameState() {
    if (!mapTexture_.loadFromFile(resourcePath("res/images/") + "boat_lvl.bmp"))
        throw std::exception();
    mapSprite_.setTexture(mapTexture_);
}

void GameState::addPlayer(Player* playerP) {
    players_.push_back(playerP);
}

void GameState::addUnhandledShots(std::vector<Shot*> newShots) {
    if (!newShots.empty())
    {
        unhandledShots_.insert(unhandledShots_.end(), newShots.begin(), newShots.end()); // add the new shots.
    }
}

void GameState::addHandledShots(std::vector<Shot*> newShots) {
    if (!newShots.empty())
    {
        for (std::vector<Shot*>::iterator it = newShots.begin(); it != newShots.end(); ++it){
            (*it)->setTimestamp(gameTime_.getElapsedTime()); // gameTime_ is never restarted.
        }
        handledShots_.insert(handledShots_.end(), newShots.begin(), newShots.end()); // add the new shots.
    }
}

void GameState::draw(sf::RenderWindow& window) {
    window.draw(mapSprite_);
    for (std::vector<Player*>::iterator it = players_.begin(); it != players_.end(); ++it){
        window.draw(**it); // calls draw for every player

        //it->draw(window, sf::RenderStates::RenderStates()); // calls draw with a default RenderState for all players
    }
}

std::vector<PhysicalObject*> GameState::getPhysicalObjects() {
  return physicalObjects_;
}

std::vector<Shot*> GameState::takeUnhandledShots() {
    std::vector<Shot*> tempVec {unhandledShots_};
    unhandledShots_.clear();
    return tempVec;
}
