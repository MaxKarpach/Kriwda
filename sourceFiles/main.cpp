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

void abilityEffect(Ability* ability, Enemy* enemy, Player& player, bool flag){
    char type = ability->getType();
    if (flag){
        switch (type)
        {
        case 'p':
            break; 
        case 'd':
            if (enemy->getIsDodgeOn()){
                std::cout << "Вы промахнулись" << std::endl;
                break;
            } else if (enemy->getIsShieldOn()){
                enemy->setShield(enemy->getShield() - player.getDamage());
                if (enemy->getShield() > 0){
                    std::cout << "Вы ударили в блок" << std::endl;
                } else {
                    std::cout << "Вы пробили щит" << std::endl;
                    enemy->setHp(enemy->getHp() + enemy->getShield());
                }
            } else {
            enemy->setHp(enemy->getHp() - ability->getFactor());
            std::cout << "Вы попали" << std::endl;  
            }
            break;
        case 'h':
            player.setHp(player.getHp() + ability->getFactor());
            break;
        case 'n':
            break; 
        default:
            break;
        }
    } else {
        switch (type)
        {
        case 'p':
            break; 
        case 'd':
            if (player.getIsDodgeOn()){
                std::cout << "Враг промахнулся" << std::endl;
                break;
            } else if (player.getIsShieldOn()){
                player.setShield(player.getShield() - enemy->getDamage());
                if (player.getShield() > 0){
                    std::cout << "Враг ударил в блок" << std::endl;
                } else {
                    std::cout << "Враг пробил щит" << std::endl;
                    player.setHp(player.getHp() + player.getShield());
                }
            } else {
                player.setHp(player.getHp() - ability->getFactor());
                std::cout << "Враг попал" << std::endl;   
            }
            break;
        case 'h':
            enemy->setHp(enemy->getHp() + ability->getFactor());
            break;
        case 'n':
            break; 
        default:
            break;
        }
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
    std::cout << "Ваш враг: " << enemy->getName() << std::endl;
    do
    {
        if (player.getIsDodgeOn() == 1){
            if (player.getDodgeCount() == player.getMaxDodgeCount()){
                player.setIsDodgeOn(0);
                player.setDodgeCount(0);
            }
            else
            {
                std::cout << "До уклонения осталось: " << player.getMaxDodgeCount() - player.getDodgeCount()<< " хода(/ов)" << std::endl;
                player.setDodgeCount(player.getDodgeCount() + 1);
            }
        }
        if (enemy->getIsDodgeOn() == 1){
            if (enemy->getDodgeCount() == enemy->getMaxDodgeCount()){
                enemy->setIsDodgeOn(0);
                enemy->setDodgeCount(0);
            } else {
                enemy->setDodgeCount(enemy->getDodgeCount() + 1);
            }
        }
        std::cout << "Введите" << std::endl;
        std::cout << "1: Атака" << std::endl;
        std::cout << "2: Защита" << std::endl;
        std::cout << "3: Уклонение" << std::endl;
        std::cout << "4: " << player1Ability->getName() << std::endl;
        std::cout << "5: " << player2Ability->getName() << std::endl;
        std::cout << "6: " << player3Ability->getName() << std::endl;
        int userChoice = 0;
        srand(time(0));
        int enemyChoice = rand() % 6 + 1;
        std::cin >> userChoice;
        if (userChoice == 1 && enemyChoice == 2 && enemy->getShield() > 0 && player.getStamina() > 0){
            enemy->setIsShieldOn(1);
            enemy->setShield(enemy->getShield() - player.getDamage());
            player.setStamina(player.getStamina() - player.getStaminaFactor());
            if (enemy->getShield() > 0){
                std::cout << "Враг поставил блок" << std::endl;
                std::cout << "Вы ударили в блок" << std::endl;
            } else {
                std::cout << "Вы пробили щит" << std::endl;
                enemy->setHp(enemy->getHp() + enemy->getShield());
            }
        } else if (userChoice == 1 && enemyChoice == 3 && enemy->getIsDodgeOn() == 0 && player.getStamina() > 0){
            enemy->setIsDodgeOn(1);            std::cout << "Враг уклонился" << std::endl;
            player.setStamina(player.getStamina() - player.getStaminaFactor());
            std::cout << "Вы промахнулись" << std::endl;
        } else if (userChoice == 2 && enemyChoice == 1 && player.getShield() > 0 && enemy->getStamina() > 0){
            player.setIsShieldOn(1);
            player.setShield(player.getShield() - enemy->getDamage());
            enemy->setStamina(enemy->getStamina() - enemy->getStaminaFactor());
            if (player.getShield() > 0){
                std::cout << "Вы поставили блок" << std::endl;
                std::cout << "Враг ударил в блок" << std::endl;
            } else {
                std::cout << "Враг пробил щит" << std::endl;
                player.setHp(player.getHp() + player.getShield());
            }
        } else if (userChoice == 3 && enemyChoice == 1 && player.getIsDodgeOn() == 0 && enemy->getStamina() > 0) {
            player.setIsDodgeOn(1);
            std::cout << "Вы уклонились" << std::endl;
            enemy->setStamina(enemy->getStamina() - enemy->getStaminaFactor());
            std::cout << "Враг промахнулся" << std::endl;
        } else if (userChoice >= 4 && userChoice <= 6 && (enemy->getIsDodgeOn() == 0 || enemy->getShield() > 0)) {
            switch (userChoice)
            {
                case 4:
                if (player1Ability->getMovesCount() == player1Ability->getMaxMovesCount()){
                    abilityEffect(player1Ability, enemy, player, 1);
                    std::cout << "Вы использовали способность " << player1Ability->getName() << std::endl;
                    player1Ability->setMovesCount(player1Ability->getMovesCount() - 1);
                    break;
                }
            case 5:
            if (player2Ability->getMovesCount() == player2Ability->getMaxMovesCount()){
                abilityEffect(player2Ability, enemy, player, 1);
                std::cout << "Вы использовали способность " << player2Ability->getName() << std::endl;
                player2Ability->setMovesCount(player2Ability->getMovesCount() - 1);
                break;
            }
            case 6:
            if (player3Ability->getMovesCount() == player3Ability->getMaxMovesCount()){
                abilityEffect(player3Ability, enemy, player, 1);
                std::cout << "Вы использовали способность " << player3Ability->getName() << std::endl;
                player3Ability->setMovesCount(player3Ability->getMovesCount() - 1);
                break;
            }
            
            default:
                break;
            }
        }else {
            switch (userChoice)
            {
            case 1:
                if (player.getStamina() > 0)
                {
                    player.setStamina(player.getStamina() - player.getStaminaFactor());
                    std::cout << "Вы попали" << std::endl;
                    enemy->setHp(enemy->getHp() - player.getDamage());
                }
                break;
            case 2:
                if (player.getShield() > 0)
                {
                    player.setIsShieldOn(1);
                    std::cout << "Вы поставили блок" << std::endl;
                }
                break;
            case 3:
                if (player.getIsDodgeOn() == 0)
                {
                    std::cout << "Вы уклонились" << std::endl;
                    player.setIsDodgeOn(1);
                }
                break;
            case 4:
                if (player1Ability->getMovesCount() == player1Ability->getMaxMovesCount()){
                    abilityEffect(player1Ability, enemy, player, 1);
                    std::cout << "Вы использовали способность " << player1Ability->getName() << std::endl;
                    player1Ability->setMovesCount(player1Ability->getMovesCount() - 1);
                    break;
                }
            case 5:
            if (player2Ability->getMovesCount() == player2Ability->getMaxMovesCount()){
                abilityEffect(player2Ability, enemy, player, 1);
                std::cout << "Вы использовали способность " << player2Ability->getName() << std::endl;
                player2Ability->setMovesCount(player2Ability->getMovesCount() - 1);
                break;
            }
            case 6:
            if (player3Ability->getMovesCount() == player3Ability->getMaxMovesCount()){
                abilityEffect(player3Ability, enemy, player, 1);
                std::cout << "Вы использовали способность " << player3Ability->getName() << std::endl;
                player3Ability->setMovesCount(player3Ability->getMovesCount() - 1);
                break;
            }
            default:
                std::cout << "Такой опции нет" << std::endl;
                break;
            }
            switch (enemyChoice)
            {
                case 1:
                    if (enemy->getStamina() > 0){
                        enemy->setStamina(enemy->getStamina() - enemy->getStaminaFactor());
                            player.setHp(player.getHp() - enemy->getDamage());
                            std::cout << "Враг попал" << std::endl;
                    }
                    break;
                case 2:
                    if (enemy->getShield() > 0){
                        enemy->setIsShieldOn(1);
                        std::cout << "Враг поставил блок" << std::endl;
                    }
                    break;
                case 3:
                    if (enemy->getIsDodgeOn() == 0){
                        enemy->setIsDodgeOn(1);
                        std::cout << "Враг уклонился" << std::endl;
                    }
                    break;
                    case 4:
                    if (enemy1Ability->getMovesCount() == enemy1Ability->getMaxMovesCount()){
                        abilityEffect(enemy1Ability, enemy, player, 0);
                        std::cout << "Враг использовали способность " << enemy1Ability->getName() << std::endl;
                        enemy1Ability->setMovesCount(enemy1Ability->getMovesCount() - 1);
                        break;
                    }
                case 5:
                if (enemy2Ability->getMovesCount() == enemy2Ability->getMaxMovesCount()){
                    abilityEffect(enemy2Ability, enemy, player, 0);
                    std::cout << "Враг использовал способность " << enemy2Ability->getName() << std::endl;
                    enemy2Ability->setMovesCount(enemy2Ability->getMovesCount() - 1);
                    break;
                }
                case 6:
                if (enemy3Ability->getMovesCount() == enemy3Ability->getMaxMovesCount()){
                    abilityEffect(enemy3Ability, enemy, player, 0);
                    std::cout << "Враг использовал способность " << enemy3Ability->getName() << std::endl;
                    enemy3Ability->setMovesCount(enemy3Ability->getMovesCount() - 1);
                    break;
                }
                default:
                    break;
                }
        }
        if (player.getStamina() < 0){
            player.setStamina(0);
        }
        if (player.getShield() < 0){
            player.setShield(0);
        }
        if (enemy->getStamina() < 0){
            enemy->setStamina(0);
        }
        if (enemy->getShield() < 0){
            enemy->setShield(0);
        }
            enemy->setIsShieldOn(0);
            player.setIsShieldOn(0);
            if (enemy->getStamina() + enemy->getStaminaFactor() < enemy->getMaxStamina())
            {
                enemy->setStamina(enemy->getStamina() + enemy->getStaminaRecoveryFactor());
            }
            if (enemy->getShield() + enemy->getShieldFactor() < enemy->getMaxShield()){
                enemy->setShield(enemy->getShield() + enemy->getShieldFactor());
            }
            if (enemy1Ability->getMaxMovesCount() != enemy1Ability->getMovesCount()){
                if (enemy1Ability->getMovesCount() == -1){
                    enemy1Ability->setMovesCount(enemy1Ability->getMaxMovesCount());
                } else {
                    enemy1Ability->setMovesCount(enemy1Ability->getMovesCount() - 1);
                }
            }
            if (enemy2Ability->getMaxMovesCount() != enemy2Ability->getMovesCount()){
                if (enemy2Ability->getMovesCount() == -1){
                    enemy2Ability->setMovesCount(enemy2Ability->getMaxMovesCount());
                } else {
                    enemy2Ability->setMovesCount(enemy2Ability->getMovesCount() - 1);
                }
            }
            if (enemy3Ability->getMaxMovesCount() != enemy3Ability->getMovesCount()){
                if (enemy3Ability->getMovesCount() == -1){
                    enemy3Ability->setMovesCount(enemy3Ability->getMaxMovesCount());
                } else {
                    enemy3Ability->setMovesCount(enemy3Ability->getMovesCount() - 1);
                }
            }
            if (player.getStamina() + player.getStaminaFactor() < player.getMaxStamina()){
                player.setStamina(player.getStamina() + player.getStaminaRecoveryFactor());
            }
            if (player.getShield() + player.getShieldFactor() < player.getMaxShield()){
                player.setShield(player.getShield() + player.getShieldFactor());
            }
            if (player1Ability->getMaxMovesCount() != player1Ability->getMovesCount()){
                if (player1Ability->getMovesCount() == -1){
                    player1Ability->setMovesCount(player1Ability->getMaxMovesCount());
                } else {
                    player1Ability->setMovesCount(player1Ability->getMovesCount() - 1);
                }
            }
            if (player2Ability->getMaxMovesCount() != player2Ability->getMovesCount()){
                if (player2Ability->getMovesCount() == -1){
                    player2Ability->setMovesCount(player2Ability->getMaxMovesCount());
                } else {
                    player2Ability->setMovesCount(player2Ability->getMovesCount() - 1);
                }
            }
            if (player3Ability->getMaxMovesCount() != player3Ability->getMovesCount()){
                if (player3Ability->getMovesCount() == -1){
                    player3Ability->setMovesCount(player3Ability->getMaxMovesCount());
                } else {
                    player3Ability->setMovesCount(player3Ability->getMovesCount() - 1);
                }
            }
            if (enemy->getHp() <= 0)
            {
                std::cout << "Вы победили" << std::endl;
            }
            else if (player.getHp() <= 0)
            {
                std::cout << "Вы проиграли" << std::endl;
            }
            else
            {
                std::cout << "Здоровье игрока: " << player.getHp() << std::endl;
                std::cout << "Щит игрока: " << player.getShield() << std::endl;
                std::cout << "Выносливость игрока: " << player.getStamina() << std::endl;
                std::cout << "Здоровье врага: " << enemy->getHp() << std::endl;
                if (player1Ability->getMaxMovesCount() != player1Ability->getMovesCount())
                {
                    std::cout << "До возможности использовать способность " << player1Ability->getName() << " осталось " << player1Ability->getMovesCount() + 2 << " хода(ов)" << std::endl;
                }
                if (player2Ability->getMaxMovesCount() != player2Ability->getMovesCount())
                {
                    std::cout << "До возможности использовать способность " << player2Ability->getName() << " осталось " << player2Ability->getMovesCount() + 2 << " хода(ов)" << std::endl;
                }
                if (player3Ability->getMaxMovesCount() != player3Ability->getMovesCount())
                {
                    std::cout << "До возможности использовать способность " << player3Ability->getName() << " осталось " << player3Ability->getMovesCount() + 2 << " хода(ов)" << std::endl;
                }
            }

    } while (enemy->getHp() > 0 && player.getHp() > 0);
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
