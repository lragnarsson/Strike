//
//  Map.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-24.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "Map.h"
#include <stdio.h>
#define TIXML_USE_STL
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "ResourcePath.h"
#include <sstream>

Map::~Map(){
    for(auto pObj : physicalObjects_)
        delete pObj;
}
std::vector<PhysicalObject*> Map::getPhysicalObjects() const {
    return physicalObjects_;
}

std::vector<sf::Vector2f> Map::makePolygonVector(std::string rawVector, float xpos, float ypos){
    std::vector<sf::Vector2f> pointPairVector;

    float tempNum{0};
    float x{0};
    float y{0};
    char c;
	std::stringstream ss(rawVector);

    while (!ss.eof()){
		ss >> tempNum; //is now xpos' origin
		x = xpos + tempNum;
		ss >> c; //throw away the ","
		ss >> tempNum; //is now ypos' origin
		y = ypos + tempNum;

		sf::Vector2f newPair{x,y};
        pointPairVector.push_back(newPair);

        x = 0;
        y = 0;
	}
	return pointPairVector;
}

void Map::load(std::string filename){

    TiXmlDocument doc;

    if(!doc.LoadFile( (resourcePath("res/maps/") + filename).c_str() )) {
        std::cerr << doc.ErrorDesc() << std::endl;
    }

    TiXmlElement* root = doc.FirstChildElement();

    if(root == nullptr){
        std::cerr << "Failed to load file: No root element."
        << std::endl;
        doc.Clear();
    }

    for(TiXmlElement* elem = root->FirstChildElement(); elem != nullptr; elem = elem->NextSiblingElement()){
        std::string elemName = elem->Value();

        if(elemName == "properties"){
            TiXmlElement* property = elem->FirstChildElement();
            std::string mapfile;
            std::string propertyName = property->Attribute("name");
            if (propertyName == "background")
                mapfile = property->Attribute("value");
            if (!mapTexture_.loadFromFile(resourcePath("res/maps/") + mapfile.c_str()))
                std::cerr << "Failed to load background file ";
            mapSprite_.setTexture(mapTexture_);
        }
        else if(elemName == "objectgroup"){
            std::string whatobject = elem->Attribute("name");

            if(whatobject == "Collison"){
                for (TiXmlElement* elem1 = elem->FirstChildElement(); elem1 != nullptr; elem1 = elem1->NextSiblingElement()){
                    std::string elemName1 = elem1->Value();
                    if (TiXmlElement* objTest = elem1->FirstChildElement()){ ///Polygon or circle

                        std::string polCircle = objTest->Value();

                        if (polCircle == "ellipse"){ ///in this case it's a circle
                            std::string xCoord = elem1->Attribute("x");
                            std::string yCoord = elem1->Attribute("y");
                            std::string radius = elem1->Attribute("width");
                            float radiusf = stof(radius) / 2.0f;
                            float xCoordf = stof(xCoord) + radiusf;
                            float yCoordf = stof(yCoord) + radiusf;

                            physicalObjects_.push_back (new PhysicalCircle(sf::Vector2f(xCoordf, yCoordf), radiusf));
                        }
                        else if ( (polCircle == "polygon") || (polCircle == "polyline")){
                            std::string originX = elem1->Attribute("x");
                            std::string originY = elem1->Attribute("y");
                            float originXf = stof(originX);
                            float originYf = stof(originY);
                            std::string rawVector = objTest->Attribute("points");
                            physicalObjects_.push_back (new PhysicalPolygon(makePolygonVector(rawVector, originXf, originYf)));
                        }
                    }
                    else{ ///it must now be a box
                        std::string originX = elem1->Attribute("x");
                        std::string originY = elem1->Attribute("y");
                        std::string width   = elem1->Attribute("width");
                        std::string height  = elem1->Attribute("height");
                        float xCoordf = stof(originX);
                        float yCoordf = stof(originY);
                        float widthf = stof(width);
                        float heightf = stof(height);
                        physicalObjects_.push_back (new PhysicalAABox(sf::Vector2f(xCoordf, yCoordf), widthf, heightf));
                    }
                }
            }
        }
    }
}

void Map::draw(sf::RenderWindow* window){
    window->draw(mapSprite_);
}
