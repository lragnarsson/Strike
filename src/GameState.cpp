//
//  GameState.cpp
//  Strike
//

#include <vector>
#include "./ResourcePath.h"
#include "./GameState.h"
#include "./Player.h"
#include "./Team.h"
#include "./GeomUtils.h"
#include "./Map.h"
#include "./WeaponFactory.h"

GameState::GameState()  {
    map_.load("map_test1.tmx");
    WeaponFactory w;
    addStationaryGameObject(w.createAK47());
}

void GameState::addTeam(Team* team){
    teams_.push_back(team);
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

void GameState::removeOldShots(bool ignoreTime) {
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
    for (auto gameObject : movingGameObjects_) {
        window->draw(*gameObject);
    }
    for (auto gameObject : stationaryGameObjects_) {
        window->draw(*gameObject);
    }
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

std::vector<PhysicalObject*> GameState::getPhysicalObjects() const {
    return map_.getPhysicalObjects();
}

std::vector<sf::Vector2f> GameState::getTspawnpoints() const {
    return map_.getTspawnpoints();
}

std::vector<sf::Vector2f> GameState::getCTspawnpoints() const {
    return map_.getCTspawnpoints();
}


void GameState::setplayerSpawnPoints(){
    std::vector<sf::Vector2f> Tspawns = getTspawnpoints();
    std::vector<sf::Vector2f> CTspawns = getCTspawnpoints();
    for(auto team : teams_){
        int i{0};
        for(auto player : team->getPlayers()){
            if(team->getTeamID() == "T"){
                sf::Vector2f spawn = Tspawns.at(i);
                player->setPosition(spawn.x,spawn.y);
            }
            if(team->getTeamID() == "CT"){
                sf::Vector2f spawn = CTspawns.at(i);
                player->setPosition(spawn.x,spawn.y);
            }
            i += 1;
        }
    }
}

std::vector<Shot*> GameState::takeUnhandledShots() {
    std::vector<Shot*> tempVec;// {unhandledShots_};
    tempVec.swap(unhandledShots_);
    //unhandledShots_.clear();
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

void GameState::addMovingGameObject(GameObject* gameObject) {
    movingGameObjects_.push_back(gameObject);
}

void GameState::addStationaryGameObject(GameObject* gameObject) {
    stationaryGameObjects_.push_back(gameObject);
}

void GameState::movingToStationaryObjects() {
  for (auto gameObject : movingGameObjects_) {
      if (gameObject->isStationary())
          stationaryGameObjects_.push_back(gameObject);
  }
  movingGameObjects_.erase(std::remove_if(movingGameObjects_.begin(),
                                          movingGameObjects_.end(),
                                          [](GameObject* go) { return go->isStationary(); }),
                           movingGameObjects_.end());
}

std::vector<GameObject*>& GameState::getMovingGameObjects() {
    return movingGameObjects_;
}
