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



class Player: public sf::Drawable, sf::Transformable //PhysicalCircle, this will handle collissions.
{
public:
    Player();
    ~Player() = default;
    float getSpeed() const;
    
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    
    sf::Texture texture_;
    sf::Sprite sprite_;
    
    float speed_ = 0.5f;
    
};


#endif /* defined(__Strike__Player__) */
