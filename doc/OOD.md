# Objektorienterad design
## Strike: local defensive
### Projekt i kursen TDDC76, Linköpings Universitet
###### Projektmedlemmar:
*	Jesper Otterholm
*	Lage Ragnarsson
*	Erik Sköld
*	Rasmus Vilhelmsson
*	Isak Wiberg
*	Filip Östman

2014-XX-XX

<div style="page-break-after: always;"></div>
## Sammanfattning
Lorem ipsum dolor sit amet.

## Innehållsförteckning
1. [Sammanfattning](#Sammanfattning)
2. [Klassdiagram](#Klassdiagram)
3. [Klassbeskrivningar](#Klassbeskrivning)
4. [Användningsfall](#Användningsfall)

<div style="page-break-after: always;"></div>
## Klassdiagram
<img src="https://raw.githubusercontent.com/lragnarsson/Strike/master/doc/OOA.jpg"></img>

<div style="page-break-after: always;"></div>
## Klassbeskrivning

### Game

Datamedlem | Beskrivning
--- | ---
NetworkHandler networkHandler |
GameState gameState |

Funktion | Beskrivning
--- | ---
void gameLoop() = 0 |
void readNetwork() = 0 |
void writeNetwork() = 0 |


### Client : Game

Datamedlem | Beskrivning
--- | ---
int clientID |
string clientName |
sf::View view |
sf::RenderWindow renderWindow |
Controller |

Funktion | Beskrivning
--- | ---
void gameLoop() |
readNetwork() |
input() |
logic() |
writeNetwork() |
draw() |


### Server : Game

Datamedlem | Beskrivning
--- | ---
map<int, string> clients |

Funktion | Beskrivning
--- | ---
void gameLoop() |


### Controller

Datamedlem | Beskrivning
--- | ---
Player* player |
View* view |

Funktion | Beskrivning
--- | ---
movePlayer(vector<PhysicalObject*>* obstacles) |
bindPlayer() |
updateView() |
bindView() |


### Team

Datamedlem | Beskrivning
--- | ---
int teamID |
vector<Player*> players |
int score |

Funktion | Beskrivning
--- | ---
get*() |
set*() |


### GameState

Datamedlem | Beskrivning
--- | ---
vector<Team> teams |
vector<Shot> unhandledShots |
vector<Shot> handledShots |
Map map |

Funktion | Beskrivning
--- | ---
get*() |
set*() |


### Shot : sf::Drawable

Datamedlem | Beskrivning
--- | ---
int timestamp |
int clientID |
sf::vector2f origin |
sf::vector2f direction |
sf::vector2f end |
float damage |

Funktion | Beskrivning
--- | ---
void draw() |

### Map : sf::Drawable

Datamedlem | Beskrivning
--- | ---
vector<PhysicalObject*> physicalObjects |

Funktion | Beskrivning
--- | ---
void draw() |


### Player : sf::Drawable, sf::Transformable, PhysicalCircle

Datamedlem | Beskrivning
--- | ---
int clientID |
string playerName |
float health |
Weapon* weapon |

Funktion | Beskrivning
--- | ---
void move() |
void rotate() |
Shot* fire() |
void takeDamage(float amount) |


### Weapon

Datamedlem | Beskrivning
--- | ---
unsigned int ammo |
unsigned int additionalAmmo |
int fireRate |
int lastFired |
float reloadTime |
bool isReloading |

Funktion | Beskrivning
--- | ---
Shot* fire(string clientID) |


## NetworkHandler

Datamedlem | Beskrivning
--- | ---
int clientID |
vector<sf::IpAdress> connectedIP |

Funktion | Beskrivning
--- | ---
getNewPackets() | Returnerar de paket som har tagits emot från nätverket. Den kollar om det har kommit in nya paket från klienter och returnerar dem förutsatt att ett paket av samma typ och från samma klient med ett högre löpnummer inte redan har levererats. Network handler måste således hålla koll på vilka klienter som är anslutna, vilka pakettyper de har skickat och vilket löpnummer som är det högsta som har tagits emot. Detta för att motverka att t.ex. gamla positionsuppdateringar som har hamnat i oordning över nätverket uppdaterar spelet. 
sendUDPPacket() | Skickar ett paket till anslutna IP-adresser. NetworkHandler håller en lista med alla som är anslutna. För en klient är denna lista kort, den innehåller bara serverns IP. För servern innehåller denna lista alla klienters IP. Då ett (UDP) paket alltid ska skickas till alla blir logiken samma för Client och Server.


### sf::Packet


### PhysicalObject

Funktion | Beskrivning
--- | ---
bool intersectLine(Line line [, sf::vector2f* intersectionPoint [, sf::vector2f* intersectionNormal]]) = 0 |
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f* intersectionPoint [, sf::vector2f* intersectionNormal]]) = 0 |
bool intersectRay(Ray ray [, sf::vector2f* intersectionPoint [, sf::vector2f* intersectionNormal]]) = 0 |
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f  intersectionNormal]]]) = 0 |


### PhysicalCircle : PhysicalObject

Datamedlem | Beskrivning
--- | ---
sf::vector2f center |
float radius |

Funktion | Beskrivning
--- | ---
bool intersectLine(Line line [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0 |
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0 |
bool intersectRay(Ray ray [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0 |
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]]) = 0 |


### PhysicalPolygon : PhysicalObject

Datamedlem | Beskrivning
--- | ---
vector<sf::vector2f> vertices |

Funktion | Beskrivning
--- | ---
bool intersectLine(Line line [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0 |
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0 |
bool intersectRay(Ray ray [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0 |
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]]) = 0 |


### PhysicalAABox : PhysicalObject

Datamedlem | Beskrivning
--- | ---
vector<sf::vector2f> vertices |

Funktion | Beskrivning
--- | ---
bool intersectLine(Line line [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0 |
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0 |
bool intersectRay(Ray ray [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0 |
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]]) = 0 |
