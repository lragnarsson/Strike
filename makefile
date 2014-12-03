#
# Makefile for Strike, GNU GCC (g++)
#

CCC = g++

SRC = src
# Kompilatorflaggor, lägg till '-g' om kompilering för avlusning ska göras.
CCFLAGS = -I$(SRC) -std=c++11 -Wpedantic -Wall -Wextra #-fpermissive

LIBFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

# Objektkodsmoduler som ingår i den kompletta kalkylatorn.
OBJECTS = ResourcePath.o PhysicalObject.o Map.o GameState.o Client.o Controller.o Player.o Server.o Shot.o Team.o Weapon.o main.o

# Huvudmål - skapas med kommandot 'make' eller 'make kalkylator'.
startClient: $(OBJECTS) makefile
	$(CCC) $(CCFLAGS) -o startClient $(OBJECTS) $(LIBFLAGS)

# Delmål (flaggan -c avbryter innan länkning, objektkodsfil erhålls)
Client.o: $(SRC)/Client.h $(SRC)/Client.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Client.cpp

Controller.o: $(SRC)/Controller.h $(SRC)/Controller.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Controller.cpp

GameState.o: $(SRC)/GameState.h $(SRC)/GameState.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/GameState.cpp

main.o: $(SRC)/main.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/main.cpp

Map.o: $(SRC)/Map.h $(SRC)/Map.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Map.cpp

Player.o: $(SRC)/Player.h $(SRC)/Player.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Player.cpp

ResourcePath.o: $(SRC)/ResourcePath.h $(SRC)/ResourcePath.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/ResourcePath.cpp

Server.o: $(SRC)/Server.h $(SRC)/Server.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Server.cpp

Shot.o: $(SRC)/Shot.h $(SRC)/Shot.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Shot.cpp

Team.o: $(SRC)/Team.h $(SRC)/Team.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Team.cpp

Weapon.o: $(SRC)/Weapon.h $(SRC)/Weapon.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/Weapon.cpp

PhysicalObject.o: $(SRC)/PhysicalObject.h $(SRC)/PhysicalObject.cpp
	$(CCC) $(CCFLAGS) -c $(SRC)/PhysicalObject.cpp

clean:
	@ \rm -rf *.o *.gch core
