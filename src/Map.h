//
//  Map.h
//  Strike
//
//  Created by Isak Wiberg on 2014-11-24.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#ifndef __Strike__Map__
#define __Strike__Map__

#include <SFML/Graphics.hpp>
#include <tinyxml.h>
#include "PhysicalObject.h"
#include <vector>

class Map {
public:
    Map() = default; // farligt att använda sprite osv om inte load körs.
    ~Map();
    Map(std::string filename); // skapa utifrån kartfil
    Map(const Map&);

    std::vector<PhysicalObject*> getPhysicalObjects() const;
    void load(std::string filename);
    void draw(sf::RenderWindow* window);

private:
    std::vector<sf::Vector2f> makePolygonVector(std::string rawVector, float xpos, float ypos);
    std::vector<PhysicalObject*> physicalObjects_;
	sf::Texture mapTexture_;
    sf::Sprite mapSprite_;
};


#endif /* defined(__Strike__Map__) */
