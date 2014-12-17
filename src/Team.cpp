/***************************************
Team.cpp

Simple class for keeping score of a team.

Written by:
Jesper Otterholm
***************************************/
#include "Team.h"
#include "Player.h"

int Team::getTeamID() const {
    return teamID_;
}

void Team::setTeamID(int teamID) {
	teamID_ = teamID;
}

void Team::increaseScore() {
    score_++;
}
int Team::getScore() const{
    return score_;
}

void Team::setScore(int score){
    score_ = score;
}
