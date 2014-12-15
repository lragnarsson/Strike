//
//  Team.cpp
//  Strike
//

#include "Team.h"
#include "Player.h"

int Team::getTeamID() const {
    return teamID_;
}

void Team::setTeamID(int teamID) {
	teamID_ = teamID;
}

int Team::getScore() const{
    return score_;
}

void Team::setScore(int score){
    score_ = score;
}
