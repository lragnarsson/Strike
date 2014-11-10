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
#### Client
#### Server
#### Packet