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
    map_.load("map2.tmx");
    WeaponFactory w;
    addStationaryGameObject(w.createAK47());
}

GameState::~GameState() {
    for (auto shot : unhandledShots_)
        delete shot;
    for (auto shot : handledShots_)
        delete shot;
    for (auto player : players_)
        delete player;/*
    for (auto elem : HUDElements_)
        delete elem;*/
    for (auto decal : unhandledDecals_)
        delete decal;
    for (auto decal : animatedDecals_)
        delete decal;
}

void GameState::addPlayer(Player* playerP) {
    players_.push_back(playerP);
}

Team* GameState::ctTeam() {
    return &ctTeam_;
}

Team* GameState::tTeam() {
    return &tTeam_;
}

void GameState::addUnhandledShots(std::vector<Shot*> newShots) {
    if (!newShots.empty()) {
        unhandledShots_.insert(unhandledShots_.end(),
                               newShots.begin(),
                               newShots.end());
    }
}

void GameState::addHandledShot(Shot* shot) {
    handledShots_.push_back(shot);
}

void GameState::removeOldShots(bool ignoreTime) {
    int elapsed = gameTime_.getElapsedTime().asMilliseconds();
    auto f = [ignoreTime, elapsed](Shot* s) {
        bool tooOld = ignoreTime || (elapsed - s->getTimestamp().asMilliseconds() > 20);
        if (tooOld)
            delete s;
        return tooOld;
    };

    handledShots_.erase(std::remove_if(handledShots_.begin(),
                                       handledShots_.end(), f),
                        handledShots_.end());
}

std::vector<Shot*> GameState::getHandledShots() {
    return handledShots_;
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
    std::vector<sf::Vector2f> tSpawns = getTspawnpoints();
    std::vector<sf::Vector2f> ctSpawns = getCTspawnpoints();
    int ti = 0;
    int cti = 0;

    for (Player* player : players_) {
        if (player->getTeam()->getTeamID() == T_TEAM) {
            player->setPosition(tSpawns[ti++ % tSpawns.size()]);
            player->move();
        }
        else {
            player->setPosition(ctSpawns[cti++ % ctSpawns.size()]);
            player->move();
        }
    }
}

std::vector<Shot*> GameState::getUnhandledShots() const {
    return unhandledShots_;
}

std::vector<Player*> GameState::getPlayers() {
    return players_;
}

void GameState::migrateShots() {
    for (auto shot : unhandledShots_)
        shot->setTimestamp(gameTime_.getElapsedTime());
    handledShots_.insert(handledShots_.end(),
                         unhandledShots_.begin(),
                         unhandledShots_.end());
    unhandledShots_.clear();
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
