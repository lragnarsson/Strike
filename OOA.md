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

2014-10-13

<div style="page-break-after: always;"></div>
## Sammanfattning

<div style="page-break-after: always;"></div>
## Innehållsförteckning
1. [Sammanfattning](#sammanfattning)
2. [Klassbeskrivningar](#Klassbeskrivning)

<div style="page-break-after: always;"></div>
## Klassbeskrivningar
#### Game
Game är en abstrakt klass som har en gameloop och ett GameState-objekt. 

#### GameState

#### Team
#### Player
#### Weapon
#### Shot
#### sf::Drawable
#### sf:Transformable
#### Map
#### PhysicalObject
Abstrakt basklass för geometriska former som diverse linjer och strålar kan kollidera med.
#### PhysicalPolygon
Håller den geometriska beskrivningen av en godtycklig månghörning samt implementerar kollisionsalgoritmer för en sådan.
#### PhysicalCircle
Håller den geometriska beskrivningen av en cirkel samt implementerar kollisionsalgoritmer för en sådan.
#### PhysicalAABox
Håller den geometriska beskrivningen av en axeljusterad rektangel samt implementerar kollisionsalgoritmer för en sådan.
#### NetworkHandler
En klass för att sköta kommunikation över nätverk. Innehåller mest metoder för att packetera och skicka data.
#### Client
Client är en subklass till game som skapas hos spelaren när han startar spelet. Den har en controller som hanterar användarens input. Dessutom har den samma networkhandler-objekt som server har. Detta objekt hanterar nätverkskommunikationen. 
#### Server
Ärver från Game. I denna klass finns logiken för att köra en servers game-loop. Denna skiljer sig från Client då den till exempel inte behöver rita någon spelgrafik. Kommunikationen över nätverket kommer också att vara lite annolunda.
#### Packet
En klass för att kapsla in meddelanden för att skicka över nätverket. Kan skilja på packet av olika typ, t.ex positionsuppdateringar, skott, mm. 

