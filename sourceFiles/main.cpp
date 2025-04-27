#include <iostream>
#include <fstream>
#include "../headerFiles/Player.h" 
#include "../headerFiles/Enemy.h" 
#include "../headerFiles/Ability.h" 
#include "../headerFiles/Item.h" 
#include "../headerFiles/Effect.h" 
#include "../headerFiles/Renderer.h" 

int main(int argc, char* argv[]){
    std::ifstream input("data.txt");
    ItemRegistry r;
    r.load(input);
    std::cout << r.getItem().name;
    return 0;
}