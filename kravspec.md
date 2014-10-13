## Primära krav
Användaren ska kunna:
*	Med tangentbordet röra sig i en 2D-värld med ”top-down”-perspektiv och kollisionshantering.
*	Sikta och skjuta på motståndare med hjälp av musen.
*	Spela mot andra spelare över internet eller LAN.

## Sekundära krav
Användaren ska kunna:
*	Ha ett synfält som beror av spelarens orientering och position.
*	Starta spelet och ansluta till andra spelare från en grafisk meny.
*	Nyttja någon typ av system för att hantera olika spelföremål, så som vapen.
*	Se spelkaraktären genom en kameravy som följer spelarens rörelser.

## Tertiära krav
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
