#
# Makefile för kalkylatorn, GNU GCC (g++)
#

# Diagnosmeddelanden från kompilatorn (g++) filtreras av gccfilter.
CCC = gccfilter -c -a g++

# Kompilatorflaggor, lägg till '-g' om kompilering för avlusning ska göras.
CCFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system #-fpermissive

# Objektkodsmoduler som ingår i den kompletta kalkylatorn.
OBJECTS = Client.o Controller.o Game.o GameState.o main.o Map.o Player.o ResourcePath.o Server.o Shot.o Team.o Weapon.o

# Huvudmål - skapas med kommandot 'make' eller 'make kalkylator'.
client: $(OBJECTS) makefile
	$(CCC) $(CCFLAGS) -o startClient $(OBJECTS)

# Delmål (flaggan -c avbryter innan länkning, objektkodsfil erhålls)
Client.o: Client.h Client.cpp
	$(CCC) $(CCFLAGS) -c Client.cpp

Controller.o: Controller.h Controller.cpp
	$(CCC) $(CCFLAGS) -c Controller.cpp

Game.o: Game.h Game.cpp
	$(CCC) $(CCFLAGS) -c Game.cpp

GameState.o: GameState.h GameState.cpp
	$(CCC) $(CCFLAGS) -c GameState.cpp

main.o: main.cpp
	$(CCC) $(CCFLAGS) -c main.cpp

Map.o: Map.h Map.cpp
	$(CCC) $(CCFLAGS) -c Map.cpp

Player.o: Player.h Player.cpp
	$(CCC) $(CCFLAGS) -c Player.cpp

ResourcePath.o: ResourcePath.h ResourcePath.cpp
	$(CCC) $(CCFLAGS) -c ResourcePath.cpp

Server.o: Server.h Server.cpp
	$(CCC) $(CCFLAGS) -c Server.cpp

Shot.o: Shot.h Shot.cpp
	$(CCC) $(CCFLAGS) -c Shot.cpp

Team.o: Team.h Team.cpp
	$(CCC) $(CCFLAGS) -c Team.cpp

Weapon.o: Weapon.h Weapon.cpp
	$(CCC) $(CCFLAGS) -c Weapon.cpp

clean:
	@ \rm -rf *.o *.gch core
