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
#include "./GeomUtils.h"


GameState::GameState()  {
    map_.load("map_test1.tmx");
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
  auto f = [elapsed](Shot* s) {
      bool tooOld = (elapsed - s->getTimestamp().asMilliseconds() > 10000);
      if (tooOld)
          delete s;
      return tooOld;
  };

  handledShots_.erase(std::remove_if(handledShots_.begin(),
                                       handledShots_.end(), f),
                        handledShots_.end());
}

void GameState::draw(sf::RenderWindow* window) {
    window->draw(mapSprite_);
    map_.draw(window);
    for (auto player : players_) {
        if (player->getLastSeen() < 500) {
            player->setColor(sf::Color(255, 255, 255, (sf::Uint8)255*(1 - smoothstep(0, 100, player->getLastSeen()))));
            window->draw(*player);
        }
    }
    for (auto shot : handledShots_) {
        window->draw(*shot);
    }
    for (auto decal : animatedDecals_) {
        decal->animate();
        window->draw(*decal);
    }
    for (auto HUDElement : HUDElements_) {
        window->draw(*HUDElement);
    }
    handleDecals();
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

void GameState::addHUDElement(sf::Drawable* HUD) {
    HUDElements_.push_back(HUD);
}

void GameState::addDecal(Decal* decal) {
    unhandledDecals_.push_back(decal);
}

void GameState::addAnimatedDecal(AnimatedDecal* decal) {
    animatedDecals_.push_back(decal);
}

void GameState::handleDecals() {
  for (auto decal : animatedDecals_) {
      if (decal->animationComplete() && decal->isPermanent()) 
          unhandledDecals_.push_back(decal);
  }
  for (auto decal : unhandledDecals_) {
      map_.drawToMap(*decal);
      delete decal;
  }
  unhandledDecals_.clear();
  animatedDecals_.erase(std::remove_if(animatedDecals_.begin(),
                                       animatedDecals_.end(),
                                       [](AnimatedDecal* d) { return d->animationComplete(); }),
                        animatedDecals_.end());
}

