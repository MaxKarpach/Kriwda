#include <iostream>
#include <fstream>
#include "../headerFiles/Player.h" 
#include "../headerFiles/Enemy.h" 
#include "../headerFiles/Ability.h" 
#include "../headerFiles/Item.h" 
#include "../headerFiles/Effect.h" 
#include "../headerFiles/Renderer.h" 
#include "../headerFiles/Location.h" 
#include "../headerFiles/Dialog.h" 
#include "../headerFiles/DialogNode.h" 
#include "../headerFiles/DialogChoice.h" 
#include "../headerFiles/Game.h" 

int main(int argc, char* argv[]){
    std::ifstream input("data.txt");
    Game game;
    game.initNewGame();
    PlayerRegistry playerRegistry;
    playerRegistry.load(input);
    Player player(playerRegistry.getPlayer());
    return 0;
}