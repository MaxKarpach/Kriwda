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
    
    LocationRegistry locationRegistry;
    locationRegistry.load(input);
    std::vector<LocationDef> locationDefs = locationRegistry.getLocations();
    std::vector<Location> locations;
    for (const LocationDef& def : locationDefs) {
    locations.push_back(Location(def));
    }

    EnemyRegistry enemyRegistry;
    enemyRegistry.load(input);
    std::vector<EnemyDef> enemyDefs = enemyRegistry.getEnemies();
    std::vector<Enemy> enemies;
    for (const EnemyDef& def : enemyDefs) {
    enemies.push_back(Enemy(def));
    }

    AbilityRegistry abilityRegistry;
    abilityRegistry.load(input);
    std::vector<AbilityDef> abilityDefs = abilityRegistry.getAbilities();
    std::vector<Ability> abilities;
    for (const AbilityDef& def : abilityDefs) {
        abilities.push_back(Ability(def));
    }

    ItemRegistry itemRegistry;
    itemRegistry.load(input);
    std::vector<ItemDef> itemDefs = itemRegistry.getItems();
    std::vector<Item> items;
    for (const ItemDef& def : itemDefs) {
        items.push_back(Item(def));
    }

    EffectRegistry effectRegistry;
    effectRegistry.load(input);
    std::vector<EffectDef> effectDefs = effectRegistry.getEffects();
    std::vector<Effect> effects;
    for (const EffectDef& def : effectDefs) {
        effects.push_back(Effect(def));
    }
    
    return 0;
}