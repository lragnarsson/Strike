# Objektorienterad analys
## Strike: local defensive
### Projekt i kursen TDDC76, Linköpings Universitet
###### Projektmedlemmar:
*	Jesper Otterholm
*	Lage Ragnarsson
*	Erik Sköld
*	Rasmus Vilhelmsson
*	Isak Wiberg
*	Filip Östman

2014-11-11

<div style="page-break-after: always;"></div>
## Sammanfattning
Detta dokument ger en översiktlig klasstruktur för projektet. Klasserna beskrivs dels i ett diagram samt senare kort i text. I diagrammet kan man också se hur klasserna relaterar till varandra. 

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
NetworkHandler networkHandler
GameState gameState
void gameLoop() = 0
void readNetwork() = 0
void writeNetwork() = 0

### Client : Game
int clientID
string clientName
sf::View view
sf::RenderWindow renderWindow
Controller
void gameLoop()
readNetwork()
input()
logic()
writeNetwork()
draw()

### Server : Game
map<int, string> clients
void gameLoop()

### Controller
Player* player
View* view
movePlayer(vector<PhysicalObject*>* obstacles)
bindPlayer()
updateView()
bindView()

### Team
int teamID
vector<Player*> players
int score

### GameState
vector<Team> teams
vector<Shot> unhandledShots
vector<Shot> handledShots
Map map
get*()
set*()

### Shot : sf::Drawable
int timestamp
int clientID
sf::vector2f origin
sf::vector2f direction
sf::vector2f end
float damage

### Map : sf::Drawable
vector<PhysicalObject*> physicalObjects
draw()

### Player : sf::Drawable, sf::Transformable, PhysicalCircle
int clientID
string playerName
float health
Weapon* weapon
void move()
void rotate()
Shot* fire()
void die()
void takeDamage(float amount)

### Weapon
Shot* fire(string clientID)
unsigned int ammo
unsigned int additionalAmmo
int fireRate
int lastFired
float reloadTime
bool isReloading

### NetworkHandler
int clientID
vector<sf::IpAddress> connectedIPs
getNewPackets()

### sf::Packet

### PhysicalObject
bool intersectLine(Line line [, sf::vector2f* intersectionPoint [, sf::vector2f* intersectionNormal]]) = 0
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f* intersectionPoint [, sf::vector2f* intersectionNormal]]) = 0
bool intersectRay(Ray ray [, sf::vector2f* intersectionPoint [, sf::vector2f* intersectionNormal]]) = 0
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]]) = 0

### PhysicalCircle : PhysicalObject
sf::vector2f center
float radius
bool intersectLine(Line line [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0
bool intersectRay(Ray ray [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]]) = 0

### PhysicalPolygon : PhysicalObject
vector<sf::vector2f> vertices
bool intersectLine(Line line [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0
bool intersectRay(Ray ray [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]]) = 0

### PhysicalAABox : PhysicalObject
vector<sf::vector2f> vertices
bool intersectLine(Line line [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0
bool intersectRay(Ray ray [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) = 0
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]]) = 0
