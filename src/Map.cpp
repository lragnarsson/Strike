//
//  Map.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-24.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "Map.h"

Map::~Map(){
    // ta bort allt som behövs.
}

void Map::draw(sf::RenderTarget& window){
    window.draw(mapSprite);
}

