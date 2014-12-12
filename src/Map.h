//
//  Map.h
//  Strike
//

#ifndef __Strike__Map__
#define __Strike__Map__

#include <SFML/Graphics.hpp>
#include <tinyxml.h>

#include "PhysicalObject.h"
#include <vector>

class Map {
public:
    Map();
    ~Map();
    Map(std::string filename); // skapa utifrån kartfil
    Map(const Map&);

    std::vector<PhysicalObject*> getPhysicalObjects() const;
    std::vector<sf::Vector2f> getTspawnpoints() const;
    std::vector<sf::Vector2f> getCTspawnpoints() const;
    void load(std::string filename);
    void draw(sf::RenderWindow* window);
    void drawToMap(const sf::Drawable& drawable);

private:
    std::vector<sf::Vector2f> makePolygonVector(std::string rawVector, float xpos, float ypos, bool forceClosedShape = false);
    std::vector<PhysicalObject*> physicalObjects_;
    std::vector<sf::Vector2f> Tspawnpoints_;
    std::vector<sf::Vector2f> CTspawnpoints_;
  //std::vector<??> objectpoints_;
    sf::Texture mapTexture_;
    sf::Sprite mapSprite_;
    sf::RenderTexture renderTexture_;
};


#endif /* defined(__Strike__Map__) */
