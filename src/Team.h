//
//  Team.h
//  Strike
//
//  Created by Isak Wiberg on 2014-11-19.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#ifndef __Strike__Team__
#define __Strike__Team__

#include <stdio.h>
#include "Player.h"
#include <vector>

class Team
{
public:
    Team() = default;
    ~Team() = default;
    Team(std::string teamname) : teamID_{teamname} {};
    std::vector<Player*> getPlayers() const;
    void addPlayer(Player*);
    void removePlayer(int playerID);
    std::string getTeamID() const;
    int getScore() const;
    void setScore(int);
    void setTeamID(std::string);

private:
    std::string teamID_;
    std::vector<Player*> players_;
    int score_;

};

#endif /* defined(__Strike__Team__) */
