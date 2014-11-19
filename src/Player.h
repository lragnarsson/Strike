//
//  Player.h
//  Strike
//
//  Created by Isak Wiberg on 2014-11-16.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#ifndef __Strike__Player__
#define __Strike__Player__

#include <stdio.h>
#include <SFML/Graphics.hpp>



class Player: public sf::Sprite //PhysicalCircle, this will handle collissions.
{
public:
    Player(int ClientID);
    Player() = delete;
    ~Player() = default;
    float getSpeed() const;
    //float getRotateSpeed() const;
    int getClientID() const;
private:
    //virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    int clientID_;
    sf::Texture texture_;
    //sf::Sprite weapon_;
    float speed_ = 0.2f;
    //float rotateSpeed_ = 1.0f;
    
};


#endif /* defined(__Strike__Player__) */
