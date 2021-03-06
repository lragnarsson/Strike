/***************************************
Map.cpp

Representation of a map. Can parse a map from a (somewhat) modified .tmx-file

Written by
Rasmus Vilhelmsson
Lage Ragnarsson
***************************************/

#include "./WeaponFactory.h"
#include "./Map.h"
#include "./ResourcePath.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <sstream>

#define TIXML_USE_STL

Map::Map() {
    renderTexture_.create(3200, 3200);
    renderTexture_.clear();
    renderTexture_.display();
}

Map::~Map(){
    for(auto pObj : physicalObjects_)
        delete pObj;
}
std::vector<PhysicalObject*> Map::getPhysicalObjects() const {
    return physicalObjects_;
}

std::vector<sf::Vector2f> Map::makePolygonVector(std::string rawVector, float xpos, float ypos, bool forceClosedShape){
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

	if (forceClosedShape)
	    pointPairVector.push_back(pointPairVector.front());

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
            if (!mapTexture_.loadFromFile(resourcePath("res/maps/") + mapfile))
                std::cerr << "Failed to load background file ";
            mapSprite_.setTexture(mapTexture_);
            renderTexture_.draw(mapSprite_);
            renderTexture_.display();
            mapSprite_.setTexture(renderTexture_.getTexture());
        }
        else if(elemName == "objectgroup"){
            std::string whatobject = elem->Attribute("name");

            if(whatobject == "Collision"){
                for (TiXmlElement* elem1 = elem->FirstChildElement(); elem1 != nullptr; elem1 = elem1->NextSiblingElement()){
                    std::string elemName1 = elem1->Value();
                    if (TiXmlElement* objTest = elem1->FirstChildElement()){ ///Polygon or circle

                        std::string polCircle = objTest->Value();

                        if (polCircle == "ellipse"){ ///in this case it's a circle
                            std::string xCoord = elem1->Attribute("x");
                            std::string yCoord = elem1->Attribute("y");
                            std::string diameter = elem1->Attribute("width");
                            float radiusf = stof(diameter) / 2.0f;
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
                            physicalObjects_.push_back (new PhysicalPolygon(makePolygonVector(rawVector, originXf, originYf, (polCircle == "polygon"))));
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
            else if(whatobject == "Spawnpoint"){
                for(TiXmlElement* elem1 = elem->FirstChildElement(); elem1 != nullptr; elem1 = elem1->NextSiblingElement()){
                    std::string TorCT = elem1->Attribute("name");
                    std::string spawnX = elem1->Attribute("x");
                    std::string spawnY = elem1->Attribute("y");
                    float spawnXf = stof(spawnX);
                    float spawnYf = stof(spawnY);
                    sf::Vector2f points{spawnXf, spawnYf};
                    if(TorCT == "Tspawn")
                        Tspawnpoints_.push_back (points);
                    else if(TorCT == "CTspawn")
                        CTspawnpoints_.push_back (points);
                    else
                        std::cerr << "can't find: " << TorCT << std::endl;
                }
            }
            else if (whatobject == "Gameobject"){
                for (TiXmlElement* elem1 = elem->FirstChildElement(); elem1 != nullptr; elem1 = elem1->NextSiblingElement()){
                    std::string whatWeapon = elem1->Attribute("name");
                    std::string weaponspawnX = elem1->Attribute("x");
                    std::string weaponspawnY = elem1->Attribute("y");
                    float weaponspawnXf = stof (weaponspawnX);
                    float weaponspawnYf = stof (weaponspawnY);
                    sf::Vector2f weaponCoords{weaponspawnXf, weaponspawnYf};
                    WeaponFactory w;
                    if (whatWeapon == "AK47")
                        spawnedObjects_.push_back (w.createAK47(weaponCoords));
                    else if (whatWeapon == "M4")
                        spawnedObjects_.push_back (w.createM4(weaponCoords));
                    else if (whatWeapon == "Nova")
                        spawnedObjects_.push_back (w.createNova(weaponCoords));
                    else if (whatWeapon == "Frag")
                        spawnedObjects_.push_back (w.createFrag(weaponCoords));
                    else if (whatWeapon == "PPK")
                        spawnedObjects_.push_back (w.createPPK(weaponCoords));
                    else if (whatWeapon == "Awp")
                        spawnedObjects_.push_back (w.createAwp(weaponCoords));
                    else
                        std::cerr << "can't find: " << whatWeapon << std::endl;
                }
            }
        }
    }
}

void Map::draw(sf::RenderWindow* window){
    window->draw(mapSprite_);
}

std::vector<sf::Vector2f> Map::getTspawnpoints() const {
    return Tspawnpoints_;
}

std::vector<sf::Vector2f> Map::getCTspawnpoints() const {
    return CTspawnpoints_;
}

std::vector<GameObject*> Map::getSpawnedObjects() const{
    return spawnedObjects_;
}

void Map::drawToMap(const sf::Drawable& drawable) {
    renderTexture_.draw(drawable);
    renderTexture_.display();
    mapSprite_.setTexture(renderTexture_.getTexture());
}
