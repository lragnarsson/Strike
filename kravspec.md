# Strike: local defensive
#####Kravspecifikation
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
*	Primära krav - Krav som MÅSTE uppfyllas.
*	Sekundära krav - Krav som vi vill genomföra för att spelet ska bli bra.
*	Tertiära krav - Krav som vi genomför i mån av tid.	

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
