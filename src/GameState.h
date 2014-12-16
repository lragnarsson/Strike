/***************************************

Holds information about the game. Map, players, team etc.

Written by:
Lage Ragnarsson
Isak Wiberg
Rasmus Vilhelmsson
Filip Östman
***************************************/

#ifndef _GAME_STATE_
#define _GAME_STATE_

#include "./Player.h"
#include "./Shot.h"
#include "./PhysicalObject.h"
#include "./Decal.h"
#include "./Map.h"
#include "./Team.h"

#include <stdio.h>
#include <vector>
#include "./GameObject.h"

class GameState{
public:
    GameState();
    ~GameState();

    void initWorld();
    void addPlayer(Player* player);
    void draw(sf::RenderWindow* window);
    void addUnhandledShots(std::vector<Shot*>);
    void addHandledShot(Shot* shot);
    std::vector<PhysicalObject*> getPhysicalObjects() const;
    std::vector<sf::Vector2f> getTspawnpoints() const;
    std::vector<sf::Vector2f> getCTspawnpoints() const;
    void setPlayerSpawnPoints();
    std::vector<Shot*> getHandledShots();
    std::vector<Shot*> getUnhandledShots() const;
    void removeOldShots(bool ignoreTime = false);
    std::vector<Player*> getPlayers();
    Team* ctTeam();
    Team* tTeam();
    void addDecal(Decal* decal);
    void addAnimatedDecal(AnimatedDecal* decal);
    void handleDecals();
    void migrateShots();
    void addTeam(Team* team);
    void addMovingGameObject(GameObject* gameObject);
    void addStationaryGameObject(GameObject* gameObject);
    void movingToStationaryObjects();
    std::vector<GameObject*>* getMovingGameObjects();
    std::vector<GameObject*>* getStationaryGameObjects();
    void removeGameObjects();

private:
    Team ctTeam_{CT_TEAM};
    Team tTeam_{T_TEAM};
    std::vector<Player*> players_;
    Map map_;
    std::vector<Shot*> unhandledShots_;
    std::vector<Shot*> handledShots_;  // shots here have both timestamp and endpoint.
    sf::Clock gameTime_;
    std::vector<Decal*> unhandledDecals_;
    std::vector<AnimatedDecal*> animatedDecals_;
    std::vector<GameObject*> movingGameObjects_;
    std::vector<GameObject*> stationaryGameObjects_;
};

#endif // _GAME_STATE_
