//
//  Client.cpp
//  Strike
//
//  Created by Isak Wiberg on 2014-11-25.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#include "Client.h"
#include "Game.h"

/* Implementation av Client
 */

void Client::run(){
    readNetwork();
    logic();
    writeNetwork();
    
}

void Client::readNetwork(){
    // tomt här med
}

void Client::writeNetwork(){
    // fan nu börjar det bli löjligt
}

void Client::logic(){

    // asså har du ens gjort något eller?
}

void Client::input(){
    controller.updatePlayerMoveVector();
    controller.playerRotate(renderWindow);
    gameState.addUnhandledShots(controller.playerFire()); // adds the shots that were created by player (if there were any).
    
    
}


void Client::draw(){
    controller.updateView();
    
    gameState.draw(renderWindow);
}
