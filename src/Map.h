/***************************************
Map.h

Representation of a map. Can parse a map from a (somewhat) modified .tmx-file

Written by
Rasmus Vilhelmsson
Lage Ragnarsson
***************************************/

#ifndef _MAP_
#define _MAP_

#include "./PhysicalObject.h"
#include <vector>

#include <SFML/Graphics.hpp>
#include <tinyxml.h>

class Map {
public:
    Map();
    ~Map();
    Map(std::string filename);
    Map(const Map&);

    std::vector<PhysicalObject*> getPhysicalObjects() const;
    std::vector<sf::Vector2f> getTspawnpoints() const;
    std::vector<sf::Vector2f> getCTspawnpoints() const;
    void load(std::string filename);
    void draw(sf::RenderWindow* window);
    void drawToMap(const sf::Drawable& drawable);
    std::vector<GameObject*> getSpawnedObjects() const;

private:
    std::vector<sf::Vector2f> makePolygonVector(std::string rawVector, float xpos, float ypos, bool forceClosedShape = false);
    std::vector<PhysicalObject*> physicalObjects_;
    std::vector<sf::Vector2f> Tspawnpoints_;
    std::vector<sf::Vector2f> CTspawnpoints_;
    sf::Texture mapTexture_;
    sf::Sprite mapSprite_;
    sf::RenderTexture renderTexture_;
    std::vector<GameObject*> spawnedObjects_;
};


#endif // _MAP_
