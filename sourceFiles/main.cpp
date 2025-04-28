#include <iostream>
#include <fstream>
#include "../headerFiles/Player.h" 
#include "../headerFiles/Enemy.h" 
#include "../headerFiles/Ability.h" 
#include "../headerFiles/Item.h" 
#include "../headerFiles/Effect.h" 
#include "../headerFiles/Renderer.h" 
#include "../headerFiles/Location.h" 

int main(int argc, char* argv[]){
    std::ifstream input("data.txt");
    LocationRegistry l;
    l.load(input);
    for (int i = 0; i < l.getLocation().choices.size();i++){
        std::cout << l.getLocation().choices[i] << std::endl;
    }
    return 0;
}