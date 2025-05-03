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
Location* findLocationById(int locationId, std::vector<Location>& locations) {
    for (auto& loc : locations) {
        if (loc.getId() == locationId) {
            return &loc;
        }
    }
    return nullptr;
}

Enemy* findEnemyById(int enemyId, std::vector<Enemy>& enemies) {
    for (auto& enemy : enemies) {
        if (enemy.getId() == enemyId) {
            return &enemy;
        }
    }
    return nullptr;
}

Ability* findAbilityById(int abilityId, std::vector<Ability>& abilities) {
    for (auto& ability : abilities) {
        if (ability.getId() == abilityId) {
            return &ability;
        }
    }
    return nullptr;
}

void move(Player& player, std::vector<Location>& locations){
    while (true){
        Location *currentLocation = findLocationById(player.getLocationId(), locations);
        std::cout << "Ваше текущее местоположение: " << currentLocation->getName() << std::endl;
        std::cout << "Вы можете пойти в следующие места: " << std::endl;
        std::vector<Location*> nearlyLocations;
        for (int i = 0; i < currentLocation->getChoices().size(); i++)
        {
            Location* nearlyLocation = findLocationById(currentLocation->getChoices()[i], locations);
            if (nearlyLocation) {
                nearlyLocations.push_back(nearlyLocation);
                std::cout << i + 1 << ": " << nearlyLocation->getName() << std::endl;
            }
        }
        std::cout << currentLocation->getChoices().size()+1 << ": Показать меню" << std::endl;
        int userChoice = 0;
        std::cin >> userChoice;
        if (userChoice == currentLocation->getChoices().size()+1){
            return;
        }
        else if (userChoice <= currentLocation->getChoices().size() && userChoice > 0)
        {
            player.setLocationId(nearlyLocations[userChoice-1]->getId());
        }
        else
        {
            std::cout << "Такого варианта нет" << std::endl;
        }
    }
}

void abilityEffect(Ability* ability, Enemy* enemy, Player& player){
    char type = ability->getType();
    switch (type)
    {
    case 'p':
        break; 
    case 'd':
        enemy->setHp(enemy->getHp() - ability->getFactor());
        break;
    case 'h':
        player.setHp(player.getHp() + ability->getFactor());
        break;
    case 'n':
        break; 
    default:
        break;
    }
}

void fight(Player& player, int enemyId, std::vector<Enemy>& enemies, std::vector<Ability>& abilities){
    Enemy* enemy = findEnemyById(enemyId, enemies);
    Ability *player1Ability = findAbilityById(player.getChosenAbilities()[0], abilities);
    Ability *player2Ability = findAbilityById(player.getChosenAbilities()[1], abilities);
    Ability *player3Ability = findAbilityById(player.getChosenAbilities()[2], abilities);
    Ability *enemy1Ability = findAbilityById(enemy->getAbilities()[0], abilities);
    Ability *enemy2Ability = findAbilityById(enemy->getAbilities()[1], abilities);
    Ability *enemy3Ability = findAbilityById(enemy->getAbilities()[2], abilities);
    int movesCount = 6;
    std::cout << "Ваш враг: " << enemy->getName() << std::endl;
    std::cout << "Введите 6 цифр" << std::endl;
    std::cout << "1: Атака" << std::endl;
    std::cout << "2: Защита" << std::endl;
    std::cout << "3: Уклонение" << std::endl;
    std::cout << "4: " << player1Ability->getName() << std::endl;
    std::cout << "5: " << player2Ability->getName() << std::endl;
    std::cout << "6: " << player3Ability->getName() << std::endl;
    int userChoice = 0;
    std::array<int, 6> playerMovesValues;
    std::array<int, 6> enemyMovesValues;
    for (int i = 0; i < movesCount; i++){
        std::cin >> playerMovesValues[i];
        enemyMovesValues[i] = rand() % 6 + 1;
    }
    do {
        for (int i = 0; i < movesCount; i++){
            switch (playerMovesValues[i])
            {
            case 1:
                if (player.getStamina() > 0){
                    player.setStamina(player.getStamina() - player.getStaminaFactor());
                    if (enemy->getIsDodgeOn()){
                        break;
                    } else if (enemy->getIsShieldOn()){
                        enemy->setShield(enemy->getShield() - player.getDamage());
                    } else {
                        enemy->setHp(enemy->getHp() - player.getDamage());
                    }
                }
                break;
            case 2:
                player.setIsShieldOn(1);
                break;
            case 3:
                player.setIsDodgeOn(1);
                break;
            case 4:
                abilityEffect(player1Ability, enemy, player);
                break;
            case 5:
                abilityEffect(player2Ability, enemy, player);
                break;
            case 6:
                abilityEffect(player3Ability, enemy, player); 
                break;
            default:
                break;
            }
        }
        player.setIsShieldOn(0);
        player.setIsDodgeOn(0);
    } while (enemy->getHp() <= 0);
}

void showMenu(Player& player, std::vector<Location>& locations, std::vector<Enemy>& enemies, std::vector<Ability>& abilities){
    int userChoice = 0;
    while (true)
    {
        int enemyId = findLocationById(player.getLocationId(), locations)->getEnemyId();
        std::cout << "Меню: " << std::endl;
        std::cout << "1: Сменить локацию" << std::endl;
        if (enemyId != 0){
            std::cout << "2: Вступить в бой" << std::endl;
        }
        std::cin >> userChoice;

        switch (userChoice)
        {
        case 1:
            move(player, locations);
            break;
        case 2:
            if (enemyId != 0){
                fight(player, enemyId, enemies, abilities);
                break;
            } else {
                std::cout << "Неверный ввод" << std::endl;
                return;
            }
        default:
            std::cout << "Неверный ввод" << std::endl;
            return;
        }
        }
}

int main(int argc, char* argv[]){
    std::ifstream input("data.txt");

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

    Game game;
    game.initNewGame();
    showMenu(player, locations, enemies, abilities);
    return 0;
}
