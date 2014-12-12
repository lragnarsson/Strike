//
//  Team.cpp
//  Strike
//

#include "Team.h"
#include "Player.h"

std::vector<Player*> Team::getPlayers() const {
    return players_;
}
void Team::addPlayer(Player* newPlayer){
    players_.push_back(newPlayer);
}

std::string Team::getTeamID() const {
    return teamID_;
}

int Team::getScore() const {
    return score_;
}

void Team::setScore(int newScore) {
    score_ = newScore;
}

void Team::setTeamID(std::string teamName) {
    teamID_ = teamName;
}

void Team::removePlayer(int clientID) {
    for (std::vector<Player*>::iterator it = players_.begin(); it != players_.end(); ++it){
        if((*it)->getClientID() == clientID)
            players_.erase(it);
        }
}
