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

2014-11-20

<div style="page-break-after: always;"></div>
## Sammanfattning
Detta dokument ger en utförlig beskrivning av klasstrukturen för projektet. Klasserna beskrivs dels i ett diagram samt senare kort i text. I diagrammet kan man också se hur klasserna relaterar till varandra. En lista över konstruktorer, funktioner och datamedlemmar finns för var klass. Vi kommer använda bibloteket SFML.

## Innehållsförteckning
1. [Sammanfattning](#sammanfattning)
2. [Klassdiagram](#klassdiagram)
3. [Klassbeskrivningar](#klassbeskrivning)
  1. [Game](#game)
  2. [Client](#client--game)
  3. [Server](#server--game)
  4. [Controller](#controller)
  5. [Team](#team)
  6. [GameState](#gamestate)
  7. [Shot](#shot--sfdrawable)
  8. [Map](#map--sfdrawable)
  9. [Player](#player--sfdrawable-sftransformable-physicalcircle)
  10. [Weapon](#weapon)
  11. [NetworkHandler](#networkhandler)
  12. [PhysicalObject](#physicalobject)
  13. [PhysicalCircle](#physicalcircle--physicalobject)
  14. [PhysicalPolygon](#physicalpolygon--physicalobject)
  15. [PhysicalAABox](#physicalaabox--physicalobject)
4. [Användningsfall](#användningsfall)

<div style="page-break-after: always;"></div>
## Klassdiagram
<img src="https://raw.githubusercontent.com/lragnarsson/Strike/develop/doc/OOD.jpg"></img>

<div style="page-break-after: always;"></div>
## Klassbeskrivning


### Game
Game är en abstrakt klass som innehåller en run-funktion för att starta, ett GameState-objekt för att hålla reda på spelets tillstånd och ett NetworkHandler-objekt för att kommunicera med nätverket.

Konstruktorer | Beskrivning
--- | ---
virtual ~Game() = default | Virtuell destruktor.
protected: Game() = default | Defaultkonstruktor.
protected: Game(Game&) = delete | Borttagen kopieringskonstruktor.
Game& operator=(const Game& rhs) = delete | Borttagen kopieringstilldelning.

Datamedlem | Beskrivning
--- | ---
NetworkHandler networkHandler | En instans av en NetworkHandler.
GameState gameState | En instans av en GameState.

Funktion | Beskrivning
--- | ---
virtual void run() = 0 | Virtuell funktion som ska innehålla gameloopen för server och klient.
virtual void readNetwork() = 0 | Virtuell funktion för att ta emot data från nätverket och behandla den.
virtual void writeNetwork() = 0 | Virtuell funktion för att skicka data på nätverket.
virtual void logic() = 0 | Virtuell funktion som sköter övrig spellogik.


### Client : Game
Client är en subklass till Game som skapas hos användaren när denne startar spelet. Här finns bland annat information för att unikt identifiera en klient och ett Controller-objekt som hanterar användarens input. Logik för utritning finns i Client.

Konstruktorer | Beskrivning
--- | ---
~Client() | Destruktor.
Client() = default | Defaultkonstruktor.
Client(Client&) = delete | Borttagen kopieringskonstruktor.
Client& operator=(const Client& rhs) = delete | Borttagen kopieringstilldelning.

Datamedlem | Beskrivning
--- | ---
int clientID | Unikt ID för klienten. Delas ut av servern.
string clientName | Namn för klienten.
sf::View view | En instans av en sf::view. Kontrollerar utsnittet på RenderWindow.
sf::RenderWindow renderWindow | En instans av en sf::RenderWindow. Här ritas allt ut.
Controller controller | En instans av en Controller. Styr den lokala spelaren. 

Funktion | Beskrivning
--- | ---
void run() | Gameloopen för en klient.
void readNetwork() | Läser data från nätverket och uppdeterar GameState därefter.
void input() | Hanterar input från användaren. Spelarens input och förflyttning hanteras genom anrop till Controller.
void logic() | Sköter övrig spellogik.
void writeNetwork() | Sköter all packetering av data för att skicka över nätverket. Anropar NetworkHandler för själva skickandet.
void draw() | Ritar ut spelvärlden.
void addUnhandledShots(vector<Shot*>) | Lägg till ohanterade skott. Från Controller.
void addHandledShots(vector<Shot*>) | Lägg till hanterade skott från nätverket. 


### Server : Game
Ärver från Game och skapas för att starta en server som klienter kan ansluta till. Server skiljer sig från Client då den till exempel inte behöver rita någon spelgrafik. Interaktionen med NetworkHandler-objektet kommer också att vara lite annolunda.

Konstruktorer | Beskrivning
--- | ---
~Server() | Destruktor.
protected: Server() = default | Defaultkonstruktor.
protected: Server(Game&) = delete | Borttagen kopieringskonstruktor.
Server& operator=(const Server& rhs) = delete | Borttagen kopieringstilldelning.

Funktion | Beskrivning
--- | ---
void run() | Gameloopen för en server.
void readNetwork() | Läser data från nätverket och uppdaterar GameState därefter.
void logic() | Sköter all spelogik på servern.
void writeNetwork() | Skickar det senaste GameStatet till var och en av anslutna klienter.


### Controller
Detta objekt hanterar användarens interaktion med sin spelarkaraktär. Input är uppdelad i flera funktioner för att skapa logiska segment i gameloopen. 

Konstruktorer | Beskrivning
--- | ---
Controller() = default | Man får se upp här så att pekarna verkligen sätts med bind* innan man använder objektet. 
~Controller() | Denna får kolla så att pekarmedlemmarna verkligen får tas bort. I så fall tas de bort. 

Datamedlem | Beskrivning
--- | ---
Player* player | Spelarkaraktären som styrs av detta objekt.
sf::View* view | Detta objekt styr vad användaren ser på sin skärm. 

Funktion | Beskrivning
--- | ---
void playerMove(vector\<PhysicalObject*\>& obstacles) | Läser input från tangentbordet och muspekarposition. Hanterar kollission med objekt i spelvärlden. 
vector\<Shot*\> playerFire() | Läser input från musen. Flera skott kan komma att skapas samtidigt. 
void bindPlayer(Player*) | Binder spelarkaraktären till detta objekt. Körs framförallt vid initiering. 
void updateView() | Uppdaterar view-objektet så att "kameran" följer spelarkaraktären. 
void bindView() | Binder ett view-objekt till detta objekt. Körs framförallt vid initiering. 



### Team
Klassen Team ska representera ett lag i spelet, med en lista över lagets spelare och lagets poäng. 

Konstruktorer | Beskrivning
--- | ---
Team(std::string teamName) | Initieringskonstruktor för Team.
~Team() = default | Defaultdestruktor.

Datamedlem | Beskrivning
--- | ---
int teamID | Varje lag ska ha en unik identifierare.
std::string teamName | Lagets namn.
vector\<Player*\> players | En vektor med pekare till alla spelare i laget.
int score | Lagets poäng.

Funktion | Beskrivning
--- | ---
* get*() | Allmänna funktioner för att få info.
void set*() | Allmänna funktioner för att bestämma saker om laget. 
std::vector<Player*> getPlayers() const | Vektor som innehåller lagets spelare.
void addPlayer(Player* player) | Lägg till en spelare i laget.
void removePlayer(int playerID) | Tar bort en spelare ur laget.
int getScore() const | Returnerar lagets poäng.
void setScore(int) | Ändrar lagets poäng.

### GameState
Detta objekt samordnar de olika delarna som beskriver spelsessionen. Den innehåller alla objekt som ska finnas i sessionen och alla objekt som skapas under sessionens gång.
Konstruktorer | Beskrivning
--- | ---
GameState() = default | När spelet startas är gamestate tom. Saker läggs till med add och set. 
~GameState() | Förstör allt på bra sätt. 

Datamedlem | Beskrivning
--- | ---
stateEnum state | Beskriver stadiet som spelet är i. T.ex. runda avslutad, lag x vann eller pågående spelläge. 
vector\<Team\> teams | En vektor med lagen. Observera att det inte finns något lista med spelare, den finns i respektive lag. 
vector\<Shot*\> unhandledShots | Skott som skapats av klienten men som ännu inte replikerats över nätverket. De kommer att få slutpunkt beräknad innan de läggs till i handledShots. 
vector\<Shot*\> handledShots | Här ligger alla skott som existerar och som är klara för utritning. De behöver inte skickas över nätverket. 
Map map | Ett objekt som representerar spelvärldens grundutseende och geometri. 

Funktion | Beskrivning
--- | ---
void setMap(string searchpath) | Funktion för att bestämma spelbana. 
add* | 
remove* |
* get*() | 
void set*() | 
void draw(sf::RenderTarget&) | Utritningsfunktion. Säger till alla objekt att rita ut sig. 


### Shot : sf::Drawable
Shotklassen ska hålla reda på position och rörelsevektor för avlossad projektil. Shot ärver från sf::Drawable och skapas av Weapon-objekt. Kollission kommer beräknas på klienten när skottet skapas men sedan kommer servern att räkna om det när den tar emot skottet. 

Konstruktorer | Beskrivning
--- | ---
~Shot() = default | Destruktor.
Shot(int timestamp, int clientID, sf::vector2f origin, sf::vector2f direction, sf::vector2f end, float damage) | Initieringskonstruktor.
Shot() = delete | Defaultkonstruktor.
Shot(const Shot& shot) | Kopieringskonstruktor.

Datamedlem | Beskrivning
--- | ---
int timestamp | Representerar när skottet skapades.
int clientID | Vem som skapade skottet. 
sf::Vector2f origin | Startpunkt. 
sf::Vector2f direction | Riktning. 
sf::Vector2f end | Slutpunkt. 
float damage | Skada som skottet orsakar vid träff. 

Funktion | Beskrivning
--- | ---
void draw() | Utritning av skottet. Det kommer vara ett linjesegment med en bestämd färg. 


### Map : sf::Drawable
Map ärver drawable för att den ska kunna rita ut sin bakgrundsbild. Den har en lista över physical objects som utgör banans geometri.

Konstruktorer | Beskrivning
--- | ---
~Map() | Destruktor.
Map() = default | Defaultkonstruktor.
Map(string filename) | Skapar en bana med kollisionsobjekt och bild från en kartfil.
Map(const Map& other) | Kopieringskonstruktor.

Datamedlem | Beskrivning
--- | ---
string filename | Kart-filens sökväg.
vector\<PhysicalObject*\> physicalObjects | En vektor med alla kollissionsobjekt i spelsessionen. 
sf::Sprite mapSprite | Bilden som är spelplanen representeras av detta objekt. 

Funktion | Beskrivning
--- | ---
void load(string filename) | Laddar in kollisionsobjekt och bild från en kartfil. 
void draw() | Utritning av bakgrundskartan. 


### Player : sf::Drawable, sf::Transformable, PhysicalCircle
Player är klassen som hanterar spelaren, alltså liv, position och rörelse. Player är hårt bunden till Team och Controller. Player känner till weapon. Ett Player-objekt kan identifieras genom dess clientID, detta är samma id som klienten som skapade Player-objektet har.

Konstruktorer | Beskrivning
--- | --- 
Player(int clientID) | För att skapa en spelarkaraktär måste man ange ett id.
~Player() = default | Destruktor till klassen Player

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
vector\<Shot*\> fire() | Säger till vapnet att skjuta. 
void takeDamage(float amount) | Uppdatera sitt liv.
int getClientID() const | Visa spelarkaraktärens identifierare.
void setWeapon(Weapon* weapon) | Ge spelaren ett vapen.
void removeWeapon() | Ta bort spelarens vapen.
float getSpeed() const | Returnera spelarens hastighet.


### Weapon
Weapon är en klass som hanterar spelarnas vapen. Det innefattar ammunition och hur mycket skada vapnet gör. Weapon är mjukt bunden till Player och känner till Shot. 

Konstruktorer | Beskrivning
--- | ---
~Weapon() = default | Destruktor till klassen Weapon.
Weapon(unsigned int ammo, unsigned int additionalAmmo, unsigned int magazineSize, int fireRate, int reloadTime) | Initieringskonstruktor.
Weapon(const Weapon& weapon) | Kopieringskonstruktor.
Weapon() = default | Defaultkonstruktor.

Datamedlem | Beskrivning
--- | ---
unsigned int ammo | Antal skott i magasinet.
unsigned int additionalAmmo | Extra ammunition utöver det i vapnet.
unsigned int magazineSize | Anger magasinstorlek.
int fireRate | Tid som anger hur många skott som kan avfyras per tidsenhet. 
int lastFired | Ett tal som representerar tiden då det senast avfyrades.
int reloadTime | Tid det tar att ladda om vapnet.
bool isReloading | Representerar att man laddar om. 

Funktion | Beskrivning
--- | ---
vector\<Shot*\> fire(int clientID, sf::Vector2f& pos, sf::Vector2f& dir) | Denna funktion skapar ett skott med position, riktningsvektor och information om vem som skapade det. 
void reloadWeapon() | Denna funktion laddar om spelarens vapen.


## NetworkHandler
En klass för att sköta kommunikation över nätverk. Innehåller främst metoder för att packetera och skicka data.

Konstruktorer | Beskrivning
--- | ---
~NetworkHandler() | Destruktor.
NetworkHandler() = default | Defaultkonstruktor.
NetworkHandler(NetworkHandler&) = delete | Borttagen kopieringskonstruktor.
NetworkHandler& operator=(const NetworkHandler& rhs) = delete | Borttagen kopieringstilldelning.

Datamedlem | Beskrivning
--- | ---
vector\<sf::IpAdress\> connectedIP | Lista över anslutna IP-adresser
vector\<sf::TcpSocket connection> TCPconnections | En struktur föratt lagra alla TCP-connections.
std::map\<int playerID, int counter\> playerLatestUpdate | En datastruktur för att spara löpnumret på den senaste spelaruppdateringen för en spelare. Används för att filtrera bort gamla paket som hamnat i oordning på vägen genom etern.  

Funktion | Beskrivning
--- | ---
vector\<sf::packets\>getNewPackets() | Returnerar de paket som har tagits emot från nätverket. Den kollar om det har kommit in nya paket från klienter och returnerar dem förutsatt att ett paket av samma typ och från samma klient med ett högre löpnummer inte redan har levererats. Network handler måste således hålla koll på vilka klienter som är anslutna, vilka pakettyper de har skickat och vilket löpnummer som är det högsta som har tagits emot. Detta för att motverka att t.ex. gamla positionsuppdateringar som har hamnat i oordning över nätverket uppdaterar spelet. 
sendUDPPacket() | Skickar ett paket till anslutna IP-adresser. NetworkHandler håller en lista med alla som är anslutna. För en klient är denna lista kort, den innehåller bara serverns IP. För servern innehåller denna lista alla klienters IP. Då ett (UDP) paket alltid ska skickas till alla blir logiken samma för Client och Server.
sendTCPPacket(sf::TcpSocket) | Skickar ett paket över TCP.

### PhysicalObject
Abstrakt basklass för geometriska former som diverse linjer och strålar kan kollidera med.

Konstruktorer | Beskrivning
--- | ---
virtual ~PbServer() | Destruktor.
protected: PhysicalObServer() = default | Defaultkonstruktor.
PhysicalObject& operaServer(const PhysicalObject& rhs) = delete | Borttagen kopieringstilldelning. Kopiering gServermed clone().

Funktion | Beskrivning
--- | ---
virtual PhysicalObject* clone() const = 0 | Pure virtual-funktion.
virtual bool intersectLine(Line line [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const = 0 | Pure virtual-funktion.
virtual bool intersectLineSegment(LineSegment lineSegment [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const = 0 | Pure virtual-funktion.
virtual bool intersectRay(Ray ray [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const = 0 | Pure virtual-funktion.
virtual bool intersectCircle(float radius, LineSegment displacement [, sf::Vector2f& centerAfterCollision [, sf::Vector2f& intersectionPoint [, sf::Vector2f&  intersectionNormal]]]) const = 0 | Pure virtual-funktion.


### PhysicalCircle : PhysicalObject
Håller den geometriska beskrivningen av en cirkel samt implementerar kollisionsalgoritmer för en sådan.

Konstruktorer etc. | Beskrivning
--- | ---
~PhysicalCircle() = default | Defaultad destruktor.
PhysicalCircle() = delete | Borttagen defaultkonstruktor.
PhysicalCircle(sf::Vector2f center, float radius) | Initieringskonstruktor.
private: PhysicalCircle(const PhysicalCircle& other) | Privat Kopieringskonstruktor. Används av clone().
PhysicalCircle& operator=(const PhysicalCircle& rhs) = delete | Borttagen kopieringstilldelning. Kopiering görs med clone().

Datamedlem | Beskrivning
--- | ---
sf::Vector2f center | Cirkelns centrum.
float radius | Cirkelns radie.    

Funktion | Beskrivning
--- | ---
PhysicalCircle* clone() const | Klonar objektet.
bool intersectLine(Line line [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const | Utför kollision mellan en given linje och den representerade cirkeln. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut kollisionspunkt samt + kollisionsnormal.
bool intersectLineSegment(LineSegment lineSegment [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const | Utför kollision mellan ett givet linjesegment och den representerade cirkeln. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut kollisionspunkt samt + kollisionsnormal.
bool intersectRay(Ray ray [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const | Utför kollision mellan en given stråle och den representerade cirkeln. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut kollisionspunkt samt + kollisionsnormal.
bool intersectCircle(float radius, LineSegment displacement [, sf::Vector2f& centerAfterCollision [, sf::Vector2f& intersectionPoint [, sf::Vector2f intersectionNormal]]]) const | Utför kollision mellan en given cirkel som rör sig längs ett givet linjesegment och den representerade cirkeln. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut den kolliderande cirkelns centrum vid kollision, + kollisionspunkt samt + kollisionsnormal.


### PhysicalPolygon : PhysicalObject
Håller den geometriska beskrivningen av en cirkel samt implementerar kollisionsalgoritmer för en sådan.

Konstruktorer etc. | Beskrivning
--- | ---
~PhysicalPolygon() | Destruktor.
PhysicalPolygon() = delete | Borttagen defaultkonstruktor.
PhysicalPolygon(vector\<sf::Vector2f\> vertices) | Initieringskonstruktor.
private: PhysicalPolygon(const PhysicalPolygon& other) | Privat kopieringskonstruktor. Används av clone().
PhysicalPolygon& operator=(const PhysicalPolygon& rhs) = delete | Borttagen kopieringstilldelning. Kopiering görs med clone().

Datamedlem | Beskrivning
--- | ---
vector\<sf::Vector2f\> vertices | En lista med punkter som defienierar polygonen.

Funktion | Beskrivning
--- | ---
PhysicalPolygon* clone() const | Klonar objektet.
bool intersectLine(Line line [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const | Utför kollision mellan en given linje och den representerade polygonen. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut kollisionspunkt samt + kollisionsnormal.
bool intersectLineSegment(LineSegment lineSegment [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const | Utför kollision mellan ett givet linjesegment och den representerade polygonen. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut kollisionspunkt samt + kollisionsnormal.
bool intersectRay(Ray ray [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const | Utför kollision mellan en given stråle och den representerade polygonen. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut kollisionspunkt samt + kollisionsnormal.
bool intersectCircle(float radius, LineSegment displacement [, sf::Vector2f& centerAfterCollision [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]]) const | Utför kollision mellan en given cirkel som rör sig längs ett givet linjesegment och den representerade polygonen. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut den kolliderande cirkelns centrum vid kollision, + kollisionspunkt samt + kollisionsnormal.


### PhysicalAABox : PhysicalObject
Håller den geometriska beskrivningen av en axeljusterad rektangel samt implementerar kollisionsalgoritmer för en sådan.

Konstruktorer etc. | Beskrivning
--- | ---
~PhysicalAABox() = default | Defaultad destruktor.
PhysicalAABox() = delete | Borttagen defaultkonstruktor.
PhysicalAABox(float origin, float width, float height) | Initieringskonstruktor.
private: PhysicalAABox(const PhysicalAABox& other) | Privat kopieringskonstruktor. Används av clone().
PhysicalAABox& operator=(const PhysicalAABox& rhs) = delete | Borttagen kopieringstilldelning. Kopiering görs med clone().

Datamedlem | Beskrivning
--- | ---
float origin | Rektangelns övre vänstra hörn.
float width | Rektangelns bredd.
float height | Rektangelns höjd.

Funktion | Beskrivning
--- | ---
PhysicalAABox* clone() const | Klonar objektet.
bool intersectLine(Line line [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const | Utför kollision mellan en given linje och den representerade rektangeln. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut kollisionspunkt samt + kollisionsnormal.
bool intersectLineSegment(LineSegment lineSegment [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const | Utför kollision mellan ett givet linjesegment och den representerade rektangeln. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut kollisionspunkt samt + kollisionsnormal.
bool intersectRay(Ray ray [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]) const | Utför kollision mellan en given stråle och den representerade rektangeln. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut kollisionspunkt samt + kollisionsnormal.
bool intersectCircle(float radius, LineSegment displacement [, sf::Vector2f& centerAfterCollision [, sf::Vector2f& intersectionPoint [, sf::Vector2f& intersectionNormal]]]) const | Utför kollision mellan en given cirkel som rör sig längs ett givet linjesegment och den representerade rektangeln. Returnerar sant om kollision skett, falkst annars. Överlagringar finns tillgängliga för att få ut den kolliderande cirkelns centrum vid kollision, + kollisionspunkt samt + kollisionsnormal.


## Användningsfall
#### En spelare skjuter ett skott
Spelloopen i Client hanterar genom input() alla knapptryckningar och anropar playerFire i Controller som hanterar fallet då skjutknappen är nedtryckt. Knappen var nedtryckt och Controller säger åt sin Player att skjuta. Player säger åt Weapon att det skall avfyras och av vilket clientID. Vapnet minskar då sin ammunition och skapar ett Shot med clientID, startposition, riktningsvektor, och möjligheten att rita ut sig själv eftersom det är en sf::Drawable. Skottet returneras från vapnets fire() i en vektor till spelaren och vidare från spelaren till Controller och vidare därifrån till input() metoden som då byter ut unhandledShots i GameState mot denna vektor.
#### Användaren startar en server och låter en annan spelare ansluta
När användaren kör terminalprogrammet för en server kan denne ange diverse egenskaper för den. Så som vilken bana som ska spelas och annat som definierar serverns ursprungliga GameState. Användaren som ska ansluta startar den exekverbara spelfilen och kan därefter genom ett terminalfönster ange klientnamn, vilket lag man vill vara i och detaljer för att ansluta till servern. När detta sker skickas en förfrågan från klienten till servern via TCP om att ansluta, när servern bearbetat informationen skickas ett svar till klienten på samma sätt som innehåller tillräckligt med information för att klienten ska kunna starta sitt spel. Övrig information så som spelarpositioner och skott skickas sedan kontinuerligt från server till alla klienter med UDP 