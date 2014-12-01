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
#include <vector>

class GameState{
public:
    GameState();
    ~GameState() = default;

    void addPlayer(Player*);
    void draw(sf::RenderWindow& window);
    void addUnhandledShots(std::vector<Shot*>);
    void addHandledShots(std::vector<Shot*>);
    vector<PhysicalObject*> getPhysicalObjects();
    std::vector<Shot*> takeUnhandledShots();

private:
    std::vector<Player*> players_;

    sf::Texture mapTexture_;
    sf::Sprite mapSprite_;
    std::vector<Shot*> unhandledShots_;
    std::vector<Shot*> handledShots_;       // shots here have both timestamp and endpoint.
    sf::Clock gameTime_;
};

#endif /* defined(__Strike__GameState__) */
