SRC_DIR = sourceFiles
INC_DIR = headerFiles
OBJ_DIR = oFiles

SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/Player.cpp $(SRC_DIR)/Enemy.cpp $(SRC_DIR)/Ability.cpp $(SRC_DIR)/Item.cpp $(SRC_DIR)/Renderer.cpp $(SRC_DIR)/Location.cpp $(SRC_DIR)/DialogNode.cpp $(SRC_DIR)/DialogChoice.cpp $(SRC_DIR)/Scene.cpp $(SRC_DIR)/BattleSystem.cpp $(SRC_DIR)/Game.cpp $(SRC_DIR)/ResourceSystem.cpp $(SRC_DIR)/InventorySystem.cpp $(SRC_DIR)/LocationSystem.cpp $(SRC_DIR)/AbilitiesSystem.cpp $(SRC_DIR)/DialogSystem.cpp $(SRC_DIR)/InfoSystem.cpp

OBJ = $(addprefix $(OBJ_DIR)/, main.o Player.o Enemy.o Ability.o Item.o Renderer.o Location.o DialogNode.o DialogChoice.o Scene.o BattleSystem.o Game.o ResourceSystem.o InventorySystem.o LocationSystem.o AbilitiesSystem.o DialogSystem.o InfoSystem.o)
EXEC = main

CC = g++
CFLAGS = -I$(INC_DIR)

all: $(OBJ_DIR) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) -c $(SRC_DIR)/main.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/Player.o: $(SRC_DIR)/Player.cpp
	$(CC) -c $(SRC_DIR)/Player.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/Enemy.o: $(SRC_DIR)/Enemy.cpp
	$(CC) -c $(SRC_DIR)/Enemy.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/Ability.o: $(SRC_DIR)/Ability.cpp
	$(CC) -c $(SRC_DIR)/Ability.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/Item.o: $(SRC_DIR)/Item.cpp
	$(CC) -c $(SRC_DIR)/Item.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/Renderer.o: $(SRC_DIR)/Renderer.cpp
	$(CC) -c $(SRC_DIR)/Renderer.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/Location.o: $(SRC_DIR)/Location.cpp
	$(CC) -c $(SRC_DIR)/Location.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/DialogNode.o: $(SRC_DIR)/DialogNode.cpp
	$(CC) -c $(SRC_DIR)/DialogNode.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/DialogChoice.o: $(SRC_DIR)/DialogChoice.cpp
	$(CC) -c $(SRC_DIR)/DialogChoice.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/Scene.o: $(SRC_DIR)/Scene.cpp
	$(CC) -c $(SRC_DIR)/Scene.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/BattleSystem.o: $(SRC_DIR)/BattleSystem.cpp
	$(CC) -c $(SRC_DIR)/BattleSystem.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/Game.o: $(SRC_DIR)/Game.cpp
	$(CC) -c $(SRC_DIR)/Game.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/ResourceSystem.o: $(SRC_DIR)/ResourceSystem.cpp
	$(CC) -c $(SRC_DIR)/ResourceSystem.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/InventorySystem.o: $(SRC_DIR)/InventorySystem.cpp
	$(CC) -c $(SRC_DIR)/InventorySystem.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/LocationSystem.o: $(SRC_DIR)/LocationSystem.cpp
	$(CC) -c $(SRC_DIR)/LocationSystem.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/AbilitiesSystem.o: $(SRC_DIR)/AbilitiesSystem.cpp
	$(CC) -c $(SRC_DIR)/AbilitiesSystem.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/DialogSystem.o: $(SRC_DIR)/DialogSystem.cpp
	$(CC) -c $(SRC_DIR)/DialogSystem.cpp $(CFLAGS) -o $@

$(OBJ_DIR)/InfoSystem.o: $(SRC_DIR)/InfoSystem.cpp
	$(CC) -c $(SRC_DIR)/InfoSystem.cpp $(CFLAGS) -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC)