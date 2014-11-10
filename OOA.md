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
#### GameState
#### Team
 Klassen Team ska ha hand om spelare, deras lag och eventuellt ett poängsystem. Den är hårt knuten till GameState och Player är hårt bunden till Team.
#### Player
 Player är klassen som hanterar spelaren, alltså liv, position och rörelse. Player är hårt bunden till Team och Controller. Player känner till weapon. Player ärver från sf:Transformable, sf:Drawable och PhysicalCircle.
#### Weapon
 Weapon är en klass som hanterar spelarnas vapen. Det innefattar antal skott och hur mycket skada vapnet gör. Weapon är mjukt bunden till Player och känner till Shot.
#### Shot
 Shotklassen ska hålla reda på position och rörelsevektor för avlossad projektil. Shot ärver från sf::Drawable och kommunicerar med Weapon.
#### sf::Drawable
#### sf:Transformable
#### Map
#### PhysicalObject
#### PhysicalPolygon
#### PhysicalCircle
#### PhysicalAABox
#### Client
#### Server
#### Packet