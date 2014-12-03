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

Map::~Map(){
    for(auto pObj : physicalObjects_)
        delete pObj;
}

std::vector<sf::Vector2f> Map::makePolygonVector(std::string rawVector, float xpos, float ypos){
    std::vector<sf::Vector2f> pointPairVector;

    int tempNum = xpos; /// first iterate will be x-position

    for(int i=0; i < rawVector.length(); ++i){
            char c = rawVector.at(i);

            int x{0};
            int y{0};

            if (isdigit(c)){

                int counter;
                char c1 = c;

                for(counter=0; (!ispunct(c1) && !isspace(c1) && ((counter + i + 1)<rawVector.length())); ++counter){
                    c1 = rawVector.at(i + counter + 1);
                }
                for(int j = 0; j < counter; ++j){
                    c1 = rawVector.at(i + j);
                    tempNum += (pow(10, (counter - j - 1))) * (c1 - '0');
                }
                if (!(counter == 0))
                    i += counter - 1;
            }
            if (ispunct(c)){
                x = tempNum;    /// x-point is done
                tempNum = ypos; /// after a comma it's y-position
            }

            if ((isspace(c)) || (i == (rawVector.length() - 1)) ){
                y = tempNum;    ///y-point is done
                tempNum = xpos;
            }
            if (!(x==0) && !(y==0)){
                sf::Vector2f newPair{static_cast<float>(x),static_cast<float>(y)};
                pointPairVector.push_back(newPair);
                x = 0;
                y = 0;
            }
    }
    return pointPairVector;
}

void Map::load(std::string filename){

    TiXmlDocument doc;

    if(!doc.LoadFile(filename.c_str())) {
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

        if(elemName == "background"){
            std::string mapfile = elem->Attribute("src");
            if (!mapTexture_.loadFromFile(resourcePath("res/images/") + mapfile))
                std::cerr << "Failed to load background file.";
            mapSprite_.setTexture(mapTexture_);
        }
        else if(elemName == "objectgroup")
        {
            for (TiXmlElement* elem1 = elem->FirstChildElement(); elem1 != nullptr; elem1 = elem1->NextSiblingElement()){
                std::string elemName1 = elem1->Value();
                if (TiXmlElement* objTest = elem1->FirstChildElement()){ //Polygon or circle

                    std::string polCircle = objTest->Value();

                    if (polCircle == "ellipse"){ ///in this case it's a circle
                        std::string xCoord = elem1->Attribute("x");
                        std::string yCoord = elem1->Attribute("y");
                        std::string radius = elem1->Attribute("width");
                        float xCoordf = stof(xCoord);
                        float yCoordf = stof(yCoord);
                        float radiusf = stof(radius) / 2.0f;
                        physicalObjects_.push_back (new PhysicalCircle(sf::Vector2f(xCoordf, yCoordf), radiusf));
                    }
                    else if (polCircle == "polygon"){
                        std::string originX = elem1->Attribute("x");
                        std::string originY = elem1->Attribute("y");
                        float originXf = stof(originX);
                        float originYf = stof(originY);
                        std::string rawVector = objTest->Attribute("points");
                        makePolygonVector(rawVector, originXf, originYf);
                        physicalObjects_.push_back (new PhysicalPolygon(makePolygonVector(rawVector, originXf, originYf)));
                    }
                    else{ ///now it must be a box
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

void Map::draw(sf::RenderTarget& window){
    window.draw(mapSprite_);
}

