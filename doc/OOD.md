## Game
NetworkHandler networkHandler
GameState gameState
void gameLoop() = 0
void readNetwork() = 0
void writeNetwork() = 0

## Client : Game
sf::View view
sf::RenderWindow renderWindow
Controller
void gameLoop()
void draw()

## Server : Game
vector<> peers
void gameLoop()

## Controller
Player* player
View* view
movePlayer(vector<PhysicalObject*>* obstacles)
bindPlayer()
updateView()
bindView()

## Team
vector<Player*> players
int score

## GameState
vector<Team> teams
vector<Shot> shots
Map map
get*()
set*()

## Shot : sf::Drawable
float2 origin
float2 direction
float2 damage

## Map : sf::Drawable
vector<PhysicalObject*> physicalObjects
draw()

## Player : sf::Drawable, sf::Transformable, PhysicalCircle
float health
Weapon* weapon
void move()
void rotate()
Shot* fire()
void die()
void takeDamage(float amount)

## Weapon
Shot* fire()
unsigned int ammo
unsigned int additionalAmmo
float fireRate
float lastFired
float reloadTime
bool isReloading

## NetworkHandler
getNewPackets()

## Packet
