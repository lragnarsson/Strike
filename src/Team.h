/***************************************
Team.h

Simple class for keeping score of a team.

Written by:
Jesper Otterholm
***************************************/

#ifndef _TEAM_
#define _TEAM_

#define T_TEAM 0
#define CT_TEAM 1

class Team {
public:
    Team() = default;
    ~Team() = default;

    Team(int teamID) : teamID_(teamID) {}
    void setTeamID(int teamID);
    int getTeamID() const;
    void setScore(int score);
    int getScore() const;

private:
    int teamID_ = 0;
    int score_ = 0;
};

#endif // _TEAM_
