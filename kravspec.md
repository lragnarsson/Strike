# Kravspecifikation
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
## Sammanfattning

## Innehållsförteckning
1. [Sammanfattning](#sammanfattning)
2. [Innehållsförteckning](#innehållsförteckning)
3. [Inledning](#inledning)
4. [Dokumentkonventioner](#dokumentkonventioner)
5. [Användargränssnitt](#användargränssnitt)
6. [Systembeskrivning](#systembeskrivning)
..1. [Primära krav](#primära-krav)
..2. [Sekundära krav](#sekundära-krav)
..3. [Tertiära krav](#tertiära-krav)
7. [Begränsningar](#begränsningar)
8. [Lagring av permanent data](#lagring-av-permanent-data)

## Inledning


## Dokumentkonventioner
Begrepp:
*	Karta - En specifik spelvärld som en spelrunda utspelar sig på.
*	Kollisionsobjekt - Ett objekt i spelvärlden som påverkar spelarkaraktärens synfält, förmåga att skjuta eller förflytta sig.
*	Spelarkaraktär - Den karaktär spelaren styr under spelrundan.
* 	Spelrunda - Ett avskiljt tillstånd för spelet med väldefinierade start- och slutvillkor som specifiseras av spelläget.
*	Spelsession - Tillståndet från det att programmet startar till dess att det avslutas.
*	Spelläge - En uppsättning regler för en spelrunda.
*	Spelvärld - Den miljö spelarkaraktären rör sig i och interagerar med.
*	Top-down - Ovanifrånperspektiv

## Användargränssnitt
Spelaren ska styra sin spelarkaraktär med tangentbord och mus. 

Tangentbordet styr:
* Förflyttning.
* Eventuell interaktion med spelvärlden (t.ex. öppna dörrar).
* Eventuell meny.

Musen styr:
* Spelarkaraktärens riktning och därmed synfält samt sikte.
* Musknappen får spelarkaraktären att avfyra sitt vapen.

I första hand kommer både spel och server startas separat från en kommandotolk. När en spelare startar spelet får han ange vilken IP-adress han ska ansluta till. Eventuellt kan man ange vilket lag man ska vara med i när man ansluter. Spelaren som har startat servern får välja hur och när spelet startar. 

Om en grafisk meny implementeras ska den styras med tangentbordet. Den ska i så fall ge möjlighet att styra funktioner som definieras av sekundära och tertiära krav t.ex. spelläge och vilka vapen man ska börja spelrundan med. 

## Systembeskrivning
Spelet är en top-down-shooter där fokus ligger på taktik, samarbete och precision. För att uppnå detta ligger ett flerspelarläge samt diverse begränsningar för spelarkaraktären, till exempel i form av begränsat synfält, i grunden. Precision uppnås genom att spelaren använder både tangentbord och mus för att kommunicera med spelet.
Målsättningen är att göra spelet så utbyggbart som möjligt så att till exempel nya banor och spellägen kan läggas till med liten arbetsinsats.

Nedan listas de konkreta krav som projektet innefattar. Primära krav är de krav som krävs för att få ett fungerande spel och som därmed måste uppfyllas. Under sekundära krav faller sådant som vi vill genomföra för att få spelet som vi har tänkt oss. Tertiära krav är de som tillför mervärde för spelupplevelsen men genomförs i mån av tid.

### Primära krav
Användaren ska kunna:
*	Med tangentbordet röra sig i en 2D-värld med ”top-down”-perspektiv.
*	Interagera med olika typer av kollisionsobjekt i spelvärlden.
*	Sikta och skjuta med hjälp av musen.
*	Använda olika typer av vapen.
*	Spela med andra spelare, uppdelade i lag, över internet eller LAN.
* 	Minst 4 spelare ska kunna spela i samma match.
*	Spela minst ett spelläge.

### Sekundära krav
Användaren ska kunna:
*	Ha ett synfält som beror av spelarens orientering, position och omgivande objekt.
*	Starta och interagera med spelet från en grafisk meny.
*	Nyttja någon typ av system för att hantera olika spelföremål, så som vapen, före eller under spelrundan.
*	Se spelkaraktären genom en kameravy som följer spelarens rörelser.

### Tertiära krav
Användaren ska kunna:
*	Höra lämpliga ljudeffekter för olika händelser.
*	Se en visualisering av ljudkällors position eller relativa riktning.
*	Spela olika typer av spellägen.
*	Använda någon typ av dynamiska objekt, t.ex. dörrar.
*	Förstöra vissa föremål i spelvärlden.
*	Uppleva någon form av partikeleffekter.
*	Skjuta genom väggar av vissa material.

## Begränsningar
Spelet kommer att vara i 2D. Spelet kommer endast att ha ett multiplayer-läge. Ingen singleplayer-kampanj eller spel mot botar kommer att implementeras. Antalet spelare kommer att vara begränsat uppåt, men det ska vara möjligt att spela åtminstone 4 spelare samtidigt.

## Lagring av permanent data
En representation av kartan (inklusive kollisionshantering för kartan) kommer att lagras på separat fil. Denna ska vara trivialt utbytbar mot annan karta. Viss konfiguration kan komma att lagras på fil, t.ex. för att komma ihåg inställningar mellan spelsessioner. Lagring på fil under spelets gång ska hållas så minimal som möjligt av prestandaskäl.
