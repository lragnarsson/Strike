//
//  GameState.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "./ResourcePath.h"
#include "./GameState.h"
#include "./Player.h"
#include "./Team.h"


GameState::GameState()  {
    //Map map_;
    //map_.load(resourcePath("res/maps/") + "map_test1.xml");
    if (!mapTexture_.loadFromFile(resourcePath("res/images/") + "boat_lvl.bmp"))
        throw std::exception();
    mapSprite_.setTexture(mapTexture_);
    physicalObjects_.push_back(new PhysicalAABox(sf::Vector2f(200.f, 50.f), 50.f, 300.f));
}

void GameState::addPlayer(Player* playerP) {
    players_.push_back(playerP);
}

void GameState::addUnhandledShots(std::vector<Shot*> newShots) {
    if (!newShots.empty()) {
        unhandledShots_.insert(unhandledShots_.end(),
                               newShots.begin(),
                               newShots.end());
    }
}

void GameState::addHandledShots(std::vector<Shot*> newShots) {
    if (!newShots.empty()) {
        for (auto shot : newShots)
            shot->setTimestamp(gameTime_.getElapsedTime());
        handledShots_.insert(handledShots_.end(),
                             newShots.begin(),
                             newShots.end());
    }
}

void GameState::removeOldShots() {
  int elapsed = gameTime_.getElapsedTime().asMilliseconds();
  auto f = [elapsed](Shot* s){return (elapsed - s->getTimestamp().asMilliseconds() > 5000);};
  handledShots_.erase(std::remove_if(handledShots_.begin(),
                                       handledShots_.end(), f),
                        handledShots_.end());
}

void GameState::draw(sf::RenderWindow* window) {
    window->draw(mapSprite_);
    //map_.draw(window);
    for (auto player : players_) {
        window->draw(*player);
    }
    for (auto shot : handledShots_) {
        window->draw(*shot);
    }
}

std::vector<PhysicalObject*> GameState::getPhysicalObjects() {
  return map_.getPhysicalObjects();
}

std::vector<Shot*> GameState::takeUnhandledShots() {
    std::vector<Shot*> tempVec {unhandledShots_};
    unhandledShots_.clear();
    return tempVec;
}

std::vector<Player*> GameState::getPlayers() {
    return players_;
}
