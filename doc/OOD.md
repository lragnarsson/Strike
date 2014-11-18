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

## NetworkHandler
getNewPackets() | Returnerar de paket som har tagits emot från nätverket. Den kollar om det har kommit in nya paket från klienter och returnerar dem förutsatt att ett paket av samma typ och från samma klient med ett högre löpnummer inte redan har levererats. Network handler måste således hålla koll på vilka klienter som är anslutna, vilka pakettyper de har skickat och vilket löpnummer som är det högsta som har tagits emot. Detta för att motverka att t.ex. gamla positionsuppdateringar som har hamnat i oordning över nätverket uppdaterar spelet. 
sendUDPPacket() | Skickar ett paket till anslutna IP-adresser. NetworkHandler håller en lista med alla som är anslutna. För en klient är denna lista kort, den innehåller bara serverns IP. För servern innehåller denna lista alla klienters IP. Då ett (UDP) paket alltid ska skickas till alla blir logiken samma för Client och Server.

int clientID
vector<sf::IpAdress> connectedIP
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
