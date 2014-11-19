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
Game är en abstrakt klass som har innehåller en run-funktion för att stara, ett GameState-objekt för att hålla reda på spelets tillstånd och ett NetworkHandler-objekt för att kommunicera med nätverket.

Datamedlem | Beskrivning
--- | ---
NetworkHandler networkHandler | 
GameState gameState |

Funktion | Beskrivning
--- | ---
void run() = 0 |
void readNetwork() = 0 |
void writeNetwork() = 0 |


### Client : Game
Client är en subklass till Game som skapas hos användaren när denne startar spelet. Här finns bland annat information för att unikt identifiera en klient och ett Controller-objekt som hanterar användarens input. Logik för utritning finns i Client.

Datamedlem | Beskrivning

--- | ---
int clientID |
string clientName |
sf::View view |
sf::RenderWindow renderWindow |
Controller |

Funktion | Beskrivning
--- | ---
void run() |
readNetwork() |
input() |
logic() |
writeNetwork() |
draw() |


### Server : Game
Ärver från Game och skapas för att starta en server som klienter kan ansluta till. Server skiljer sig från Client då den till exempel inte behöver rita någon spelgrafik. Interaktionen med NetworkHandler-objektet kommer också att vara lite annolunda.

Datamedlem | Beskrivning
--- | ---
map<int, string> clients |

Funktion | Beskrivning
--- | ---
void run() |


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
Klassen Team ska representera ett lag i spelet, med en lista över lagets spelare och lagets poäng. 

Datamedlem | Beskrivning
--- | ---
int teamID | Varje lag ska ha en unik identifierare.
vector<Player*> players | En vektor med pekare till alla spelare i laget.
int score | Lagets poäng.

Funktion | Beskrivning
--- | ---
get*() | Allmänna funktioner för att få info.
set*() | Allmänna funktioner för att bestämma saker om laget. 


### GameState
Detta objekt samordnar de olika delarna som beskriver spelsessionen. Den innehåller alla objekt som ska finnas i sessionen och alla objekt som skapas under sessionens gång.

Datamedlem | Beskrivning
--- | ---
stateEnum state | 
vector<Team> teams |
vector<Shot> unhandledShots |
vector<Shot> handledShots |
Map map |

Funktion | Beskrivning
--- | ---
get*() |
set*() |


### Shot : sf::Drawable
Shotklassen ska hålla reda på position och rörelsevektor för avlossad projektil. Shot ärver från sf::Drawable och skapas av Weapon-objekt.

Datamedlem | Beskrivning
--- | ---
int timestamp | Representerar när skottet skapades.
int clientID | Vem som skapade skottet. 
sf::vector2f origin | Startpunkt. 
sf::vector2f direction | Riktning. 
sf::vector2f end | Slutpunkt. 
float damage | Skada som skottet orsakar vid träff. 

Funktion | Beskrivning
--- | ---
void draw() | Utritning av skottet. Det kommer vara ett linjesegment med en bestämd färg. 

### Map : sf::Drawable
Map ärver drawable för att den ska kunna rita ut sin bakgrundsbild. Den har en lista över physical objects som utgör banans geometri.

Datamedlem | Beskrivning
--- | ---
vector<PhysicalObject*> physicalObjects | En vektor med alla kollissionsobjekt i spelsessionen. 

Funktion | Beskrivning
--- | ---
void draw() | Utritning av bakgrundskartan. 


### Player : sf::Drawable, sf::Transformable, PhysicalCircle
Player är klassen som hanterar spelaren, alltså liv, position och rörelse. Player är hårt bunden till Team och Controller. Player känner till weapon. Player ärver från sf:Transformable, sf:Drawable och PhysicalCircle. Ett Player-objekt kan identifieras genom dess clientID, detta är samma id som klienten som skapade Player-objektet har,

Datamedlem | Beskrivning
--- | ---
int clientID | Identifierare för varje spelarkaraktär.
string playerName | Spelarkaraktärens namn. Kan tänkas användas om man vill ha en poänglista. 
float health | Hur mycket liv spelarkaraktären har.
Weapon* weapon | En spelarkaraktär kan ha ett vapen.  

Funktion | Beskrivning
--- | ---
void move(const Vector2f &offset) | Relativ förflyttning med offset angiven som vektor eller koordinater. Det finns fler varianter specifierade i sf::Transformable. 
void rotate(float angle) | Relativ rotation. 
Shot* fire() | Säger till vapnet att skjuta. 
void takeDamage(float amount) | Uppdatera sitt liv.


### Weapon
Weapon är en klass som hanterar spelarnas vapen. Det innefattar ammunition och hur mycket skada vapnet gör. Weapon är mjukt bunden till Player och känner till Shot.

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
En klass för att sköta kommunikation över nätverk. Innehåller främst metoder för att packetera och skicka data.

Datamedlem | Beskrivning
--- | ---
int clientID |
vector<sf::IpAdress> connectedIP |

Funktion | Beskrivning
--- | ---
getNewPackets() | Returnerar de paket som har tagits emot från nätverket. Den kollar om det har kommit in nya paket från klienter och returnerar dem förutsatt att ett paket av samma typ och från samma klient med ett högre löpnummer inte redan har levererats. Network handler måste således hålla koll på vilka klienter som är anslutna, vilka pakettyper de har skickat och vilket löpnummer som är det högsta som har tagits emot. Detta för att motverka att t.ex. gamla positionsuppdateringar som har hamnat i oordning över nätverket uppdaterar spelet. 
sendUDPPacket() | Skickar ett paket till anslutna IP-adresser. NetworkHandler håller en lista med alla som är anslutna. För en klient är denna lista kort, den innehåller bara serverns IP. För servern innehåller denna lista alla klienters IP. Då ett (UDP) paket alltid ska skickas till alla blir logiken samma för Client och Server.

### PhysicalObject
Abstrakt basklass för geometriska former som diverse linjer och strålar kan kollidera med.

Funktion | Beskrivning
--- | ---
bool intersectLine(Line line [, sf::vector2f* intersectionPoint [, sf::vector2f* intersectionNormal]]) = 0 |
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f* intersectionPoint [, sf::vector2f* intersectionNormal]]) = 0 |
bool intersectRay(Ray ray [, sf::vector2f* intersectionPoint [, sf::vector2f* intersectionNormal]]) = 0 |
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f  intersectionNormal]]]) = 0 |


### PhysicalCircle : PhysicalObject
Håller den geometriska beskrivningen av en cirkel samt implementerar kollisionsalgoritmer för en sådan.

Datamedlem | Beskrivning
--- | ---
sf::vector2f center |
float radius |

Funktion | Beskrivning
--- | ---
bool intersectLine(Line line [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) |
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) |
bool intersectRay(Ray ray [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) |
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]]) |


### PhysicalPolygon : PhysicalObject
Håller den geometriska beskrivningen av en cirkel samt implementerar kollisionsalgoritmer för en sådan.

Datamedlem | Beskrivning
--- | ---
vector<sf::vector2f> vertices |

Funktion | Beskrivning
--- | ---
bool intersectLine(Line line [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) |
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) |
bool intersectRay(Ray ray [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) |
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]]) |


### PhysicalAABox : PhysicalObject
Håller den geometriska beskrivningen av en axeljusterad rektangel samt implementerar kollisionsalgoritmer för en sådan.

Datamedlem | Beskrivning
--- | ---
vector<sf::vector2f> vertices |

Funktion | Beskrivning
--- | ---
bool intersectLine(Line line [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) |
bool intersectLineSegment(LineSegment lineSegment [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) |
bool intersectRay(Ray ray [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]) |
bool intersectCircle(float radius, LineSegment lineSegment [, sf::vector2f centerAfterCollision [, sf::vector2f intersectionPoint [, sf::vector2f intersectionNormal]]]) |
