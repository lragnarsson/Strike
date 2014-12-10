//
//  GameState.h
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#ifndef __Strike__GameState__
#define __Strike__GameState__

#include <stdio.h>
#include "Player.h"
#include "Shot.h"
#include "PhysicalObject.h"
#include "./Decal.h"
#include <vector>
#include "Map.h"
#include "Team.h"

class GameState{
public:
    GameState();
    ~GameState() = default;

    void addPlayer(Player* player);
    void draw(sf::RenderWindow* window);
    void addUnhandledShots(std::vector<Shot*>);
    void addHandledShots(std::vector<Shot*>);
    std::vector<PhysicalObject*> getPhysicalObjects() const;
    std::vector<sf::Vector2f> getTspawnpoints() const;
    std::vector<sf::Vector2f> getCTspawnpoints() const;
    void setplayerSpawnPoints();
    std::vector<Shot*> takeUnhandledShots();
    void removeOldShots(bool ignoreTime = false);
    std::vector<Player*> getPlayers();
    void addHUDElement(sf::Drawable* HUD);
    void addDecal(Decal* decal);
    void addAnimatedDecal(AnimatedDecal* decal);
    void handleDecals();
    void addTeam(Team* team);


private:
    std::vector<Team*> teams_;
    std::vector<Player*> players_;
    sf::Texture mapTexture_;
    sf::Sprite mapSprite_;
    Map map_;
    std::vector<PhysicalObject*> physicalObjects_;
    std::vector<Shot*> unhandledShots_;
    std::vector<Shot*> handledShots_;  // shots here have both timestamp and endpoint.
    sf::Clock gameTime_;
    std::vector<sf::Drawable*> HUDElements_;
    std::vector<Decal*> unhandledDecals_;
    std::vector<AnimatedDecal*> animatedDecals_;
    sf::Texture boomtexture;
};

#endif /* defined(__Strike__GameState__) */
