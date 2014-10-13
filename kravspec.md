# Kravspecifikation
## Strike: local defensive
### Projekt i kursen TDDC76, Linköpings Universitet
###### Projektmedlemmar:
*	Jesper Otterholm
*	Lage Ragnarsson
*	Erik Sköld
*	Rasmus Vilhelmsson
*	Isak Viberg
*	Filip Östman

2014-10-13


## Dokumentkonventioner
Begrepp:
*	Spelarkaraktär – Den ”gubbe” du styr i spelet

## Användargränssnitt
Spelaren ska styra sin spelarkaraktär med tangentbord och mus. 
Tangentbordet styr:
* förflyttning
* eventuell interaktion med spelvärlden (t.ex. öppna dörrar)
* eventuell meny.
Musen styr:
* spelarkaraktärens riktning och därmed synfält samt sikte
* musknappen får spelarkaraktären att avfyra sitt vapen.
I första hand kommer både spel och server startas separat från en kommandotolk. När en spelare startar spelet får han ange vilken IP-adress han ska ansluta till. Eventuellt kan man ange vilket lag man ska vara med i när man ansluter. Spelaren som har startat servern får välja hur och när spelet startar. 
Om en grafisk meny implementeras ska den styras med tangentbordet. Den ska i så fall innehålla 

## Systembeskrivning
Den grundläggande idén är att med en enkel uppsättning regler skapa ett spel som är så roligt som möjligt att spela. På så sätt maximeras glädjen medan arbetsinsatsen minimeras. Det hela påminner lite om Schack, där ett få antal regler gör en stor sport.

Spelet är en topp-down-shooter där fokus ligger på taktik, samarbete och precision. För att uppnå detta ligger ett flerspelarläge samt diverse begränsningar för spelkaraktären, till exempel i form av begränsat synfält, i grunden. Precision uppnås genom att spelaren använder både tangentbord och mus för att kommunicera med spelet.
Målsättningen är att göra spelet så utbyggbart som möjligt så att till exempel nya banor och spellägen kan läggas till med liten arbetsinsats.

Nedan listas de konkreta krav som projektet innefattar. Primära krav är de krav som krävs för att få ett fungerande spel och som därmed MÅSTE uppfyllas. Under sekundära krav faller sådant som vi vill genomföra för att få spelet som vi har tänkt oss. Tertiära krav är de som tillför mervärde för spelupplevelsen men genomförs i mån av tid.

### Primära krav
Användaren ska kunna:
*	Med tangentbordet röra sig i en 2D-värld med ”top-down”-perspektiv och kollisionshantering.
*	Sikta och skjuta på motståndare med hjälp av musen.
*	Spela med och mot andra spelare över internet eller LAN med fördefinierade regler. 

### Sekundära krav
Användaren ska kunna:
*	Ha ett synfält som beror av spelarens orientering och position.
*	Starta spelet och ansluta till andra spelare från en grafisk meny.
*	Nyttja någon typ av system för att hantera olika spelföremål, så som vapen.
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
Spelet kommer att vara i 2D. Spelet kommer endast att vara multiplayer. Ingen singleplayerkampanj eller spel mot botar kommer implementeras. Antalet spelare kommer vara begränsat uppåt, men det ska vara möjligt att spela åtminstone 4 spelare samtidigt.

## Lagring av permanent data
Filer för att representera kartan (inklusive kollisionshantering för kartan) kommer att lagras på separat fil. Denna ska vara utbytbar mot annan karta enkelt. Viss konfiguration kan komma att lagras på fil, t.ex. för att komma ihåg inställningar mellan spel. Lagring på fil under spel ska hållas så minimal som möjligt av prestationsskäl.
