SRC_DIR = sourceFiles
INC_DIR = headerFiles

SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/Player.cpp $(SRC_DIR)/Enemy.cpp/Ability.cpp/Item.cpp/Renderer.cpp/Location.cpp/Dialog.cpp/DialogNode.cpp/DialogChoice.cpp/Game.cpp

OBJ = main.o Player.o Enemy.o Ability.o Item.o Renderer.o Location.o Dialog.o DialogNode.o DialogChoice.o Game.o
EXEC = main

CC = g++
CFLAGS = -I$(INC_DIR)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o: $(SRC_DIR)/main.cpp
	$(CC) -c $(SRC_DIR)/main.cpp $(CFLAGS)

Player.o: $(SRC_DIR)/Player.cpp
	$(CC) -c $(SRC_DIR)/Player.cpp $(CFLAGS)

Enemy.o: $(SRC_DIR)/Enemy.cpp
	$(CC) -c $(SRC_DIR)/Enemy.cpp $(CFLAGS)

Ability.o: $(SRC_DIR)/Ability.cpp
	$(CC) -c $(SRC_DIR)/Ability.cpp $(CFLAGS)

Item.o: $(SRC_DIR)/Item.cpp
	$(CC) -c $(SRC_DIR)/Item.cpp $(CFLAGS)

Renderer.o: $(SRC_DIR)/Renderer.cpp
	$(CC) -c $(SRC_DIR)/Renderer.cpp $(CFLAGS)

Location.o: $(SRC_DIR)/Location.cpp
	$(CC) -c $(SRC_DIR)/Location.cpp $(CFLAGS)

Dialog.o: $(SRC_DIR)/Dialog.cpp
	$(CC) -c $(SRC_DIR)/Dialog.cpp $(CFLAGS)

DialogNode.o: $(SRC_DIR)/DialogNode.cpp
	$(CC) -c $(SRC_DIR)/DialogNode.cpp $(CFLAGS)


DialogChoice.o: $(SRC_DIR)/DialogChoice.cpp
	$(CC) -c $(SRC_DIR)/DialogChoice.cpp $(CFLAGS)

Game.o: $(SRC_DIR)/Game.cpp
	$(CC) -c $(SRC_DIR)/Game.cpp $(CFLAGS)

clean:
	rm -f $(OBJ) $(EXEC)
