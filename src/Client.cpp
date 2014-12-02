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

void Client::run() {
    readNetwork();
    handleInput();
    handleCollisions();
    handleGameLogic();
    writeNetwork();
    draw();
    
}

void Client::readNetwork() {
    // tomt här med
}

void Client::writeNetwork() {
    // fan nu börjar det bli löjligt
}

void Client::handleCollisions() {
    handleShots();
}

void Client::handleGameLogic() {

    // asså har du ens gjort något eller?
}


void Client::handleInput() {
    controller.updatePlayerMoveVector();
    controller.playerRotate(renderWindow);
    gameState_.addUnhandledShots(controller.playerFire()); // adds the shots that were created by player (if there were any).
    controller.playerRotate(renderWindow);
    controller.reloadWeapon();
    controller.isSprinting();
    

    
    
}


void Client::draw() {
    controller.updateView();
    
    gameState_.draw(renderWindow);
}


void Client::handleShots() {
    std::vector<Shot*> shots {gameState_.takeUnhandledShots()};
    if (!shots.empty()) {
        for (std::vector<Shot*>::iterator it = shots.begin(); it != shots.end(); ++it) {
            // Calculate newEndPoint with proper collision later
            sf::Vector2f newEndPoint {(*it)->getOrigin() + 100.0f * (*it)->getDirection()};
        
            // --- finished :D
                (*it)->setEndPoint(newEndPoint);
        }
        
    }
    gameState_.addHandledShots(shots);
}