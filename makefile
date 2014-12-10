#
# Makefile for Strike, GNU GCC (g++)
#

CCC = gccfilter -c -a g++

SRC = src
TINY = libraries/tinyxml
# Kompilatorflaggor, lägg till '-g' om kompilering för avlusning ska göras.
CCFLAGS = -I$(SRC) -std=c++11 -Wpedantic -Wall -Wextra #-fpermissive

LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio -ltinyxml

# Objektkodsmoduler som ingår i den kompletta kalkylatorn.
OBJECTS = ResourcePath.o PhysicalObject.o Map.o GameState.o Client.o Controller.o Player.o Server.o NetworkHandler.o Messages.o Shot.o Team.o Weapon.o Decal.o Strike.o


# Huvudmål - skapas med kommandot 'make' eller 'make kalkylator'.
strike: $(OBJECTS) makefile
	$(CCC) $(CCFLAGS) -o strike $(OBJECTS) $(LIBFLAGS)

# Delmål (flaggan -c avbryter innan länkning, objektkodsfil erhålls)
Client.o: $(SRC)/Client.h $(SRC)/Client.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Client.cpp

Controller.o: $(SRC)/Controller.h $(SRC)/Controller.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Controller.cpp

GameState.o: $(SRC)/GameState.h $(SRC)/GameState.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/GameState.cpp

Strike.o: $(SRC)/Strike.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Strike.cpp

Map.o: $(SRC)/Map.h $(SRC)/Map.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Map.cpp

Player.o: $(SRC)/Player.h $(SRC)/Player.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Player.cpp

ResourcePath.o: $(SRC)/ResourcePath.h $(SRC)/ResourcePath.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/ResourcePath.cpp

Server.o: $(SRC)/Server.h $(SRC)/Server.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Server.cpp

NetworkHandler.o: $(SRC)/NetworkHandler.h $(SRC)/NetworkHandler.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/NetworkHandler.cpp

Messages.o: $(SRC)/Messages.h $(SRC)/Messages.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Messages.cpp

Shot.o: $(SRC)/Shot.h $(SRC)/Shot.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Shot.cpp

Team.o: $(SRC)/Team.h $(SRC)/Team.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Team.cpp

Weapon.o: $(SRC)/Weapon.h $(SRC)/Weapon.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Weapon.cpp

PhysicalObject.o: $(SRC)/PhysicalObject.h $(SRC)/PhysicalObject.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/PhysicalObject.cpp

Decal.o: $(SRC)/Decal.h $(SRC)/Decal.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Decal.cpp
clean:
	@ \rm -rf *.o *.gch core
