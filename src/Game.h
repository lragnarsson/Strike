//
//  Game.h
//  Strike
//
//  Created by Isak Wiberg on 2014-11-20.
//  Copyright (c) 2014 Isak Wiberg. All rights reserved.
//

#ifndef __Strike__Game__
#define __Strike__Game__

#include <stdio.h>
#include "ResourcePath.h"
#include "Player.h"
#include "GameState.h"
#include "Controller.h"
#include "Team.h"
#include "Weapon.h"


/*  Game är en abstrakt klass som innehåller en run-funktion för att starta,
 *  ett GameState-objekt för att hålla reda på spelets tillstånd och ett 
 *  NetworkHandler-objekt för att kommunicera med nätverket.
 */

class Game{
 public:
  virtual ~Game() = default;
    // NetworkHandler NetworkHandler; lägg till detta när NetworkHandler är implementerad.
  GameState gameState_;

  virtual void run() = 0;  // gameloopen för server och klient.
  virtual void readNetwork() = 0;  // ta emot data från nätverket och behandla den.
  virtual void writeNetwork() = 0;  // skicka data på nätverket.
  virtual void handleGameLogic() = 0;  // sköter logiken hos klient resp. server.
  virtual void handleCollisions() = 0;  // beräknar kollissioner.

 protected:
  Game() = default;
  Game(const Game&) = delete;             // borttagen kopieringskonstruktor
  Game& operator=(const Game&) = delete;  // borttagen kopieringstilldelning
};

#endif /* defined(__Strike__Game__) */
