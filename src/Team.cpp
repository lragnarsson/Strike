//
//  Team.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-19.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "Team.h"
#include "Player.h"
std::vector<Player*> Team::getPlayers() const{
    return players_;
}
void Team::addPlayer(Player* newPlayer){
    players_.push_back(newPlayer);
}

int Team::getScore() const{
    return score_;
}

void Team::setScore(int newScore){
    score_ = newScore;
}

void Team::removePlayer(int clientID){
    for (std::vector<Player*>::iterator it = players_.begin(); it != players_.end(); ++it){
        if((*it)->getClientID() == clientID)
            players_.erase(it);
        }
}