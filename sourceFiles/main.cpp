#include <iostream>
#include <fstream>
#include "../headerFiles/Player.h" 
#include "../headerFiles/Enemy.h" 
#include "../headerFiles/Ability.h" 
#include "../headerFiles/Item.h" 
#include "../headerFiles/Renderer.h" 
#include "../headerFiles/Location.h" 
#include "../headerFiles/DialogNode.h" 
#include "../headerFiles/DialogChoice.h" 
#include "../headerFiles/Scene.h"
void initNewGame(){
    std::cout << "Начало игры" << std::endl;
}
void gameOver(){
    std::cout << "Вы проиграли" << std::endl;
}
void endGame( std::vector<Scene>& scenes){
    std::vector<Scene> endings;
    for (Scene scene : scenes){
        if (scene.getType() == 'e'){
            endings.push_back(scene);
        }
    }
    for (int i = 0; i < endings.size(); i++){
        std::cout << i + 1 << ": " << endings[i].getText() << std::endl;
    }
        int choice = 0;
    while (true) {
        std::cin >> choice;

        if (choice >= 1 && choice <= endings.size()) {
            break;
        } else {
            std::cout << "Неверный выбор. Пожалуйста, введите число от 1 до " << endings.size() << "." << std::endl;
        }
    }

    // Выводим выбранную концовку
    std::cout << "Выбранная концовка:" << std::endl;;
    std::cout << endings[choice - 1].getText() << std::endl;
    std::cout << "Конец игры" << std::endl;
}
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

Item* findItemById(int itemId, std::vector<Item>& items) {
    for (auto& item : items) {
        if (item.getId() == itemId) {
            return &item;
        }
    }
    return nullptr;
}

void startDialog(int dialogId,std::vector<DialogNode>& dialogNodes,std::vector<DialogChoice>& dialogChoices, int currentNodeId, Location* currentLocation) {
    while (true)
    {

        DialogNode* currentNode = nullptr;
        for (auto& node : dialogNodes) {
            if (node.getId() == currentNodeId) {
                currentNode = &node;
                break;
            }
        }
        if (!currentNode) {
            std::cout << "Ошибка: узел диалога не найден." << std::endl;
            break;
        }

        if (currentNode->getChoices().size() == 0){
            currentLocation->setDialogNodeId(0);
        }

        std::cout << currentNode->getName() << ": " << currentNode->getText() << std::endl;

        std::vector<DialogChoice*> currentChoices;
        for (auto& choice : dialogChoices) {
            if (choice.getNodeId() == currentNodeId) {
                currentChoices.push_back(&choice);
            }
        }

        if (currentChoices.empty()) {
            std::cout << "Диалог завершён." << std::endl;
            break;
        }

        for (int i = 0; i < currentChoices.size(); ++i) {
            std::cout << i + 1 << ": " << currentChoices[i]->getText() << std::endl;
        }

        int userChoice = 0;
        std::cout << "Выберите вариант (0 — выход): ";
        std::cin >> userChoice;

        if (userChoice <= 0 || userChoice > currentChoices.size()) {
            std::cout << "Диалог прерван." << std::endl;
            break;
        }

        currentNodeId = currentChoices[userChoice - 1]->getNextNodeId();
    }
}

void downloadData(Player & player, std::vector<Location> & locations, std::vector<Enemy> & enemies, std::vector<Ability> & abilities, std::vector<Item> & items, std::vector<DialogNode> & dialogNodes, std::vector<DialogChoice> & dialogChoices, std::vector<Scene> & scenes){
   std::ifstream input("data.txt");

    PlayerRegistry playerRegistry;
    playerRegistry.load(input);
    player = playerRegistry.getPlayer();

    locations.clear();
    enemies.clear();
    abilities.clear();
    items.clear();
    dialogNodes.clear();
    dialogChoices.clear();
    scenes.clear();

    LocationRegistry locationRegistry;
    locationRegistry.load(input);
    std::vector<LocationDef> locationDefs = locationRegistry.getLocations();
    for (const LocationDef& def : locationDefs) {
    locations.push_back(Location(def));
    }

    EnemyRegistry enemyRegistry;
    enemyRegistry.load(input);
    std::vector<EnemyDef> enemyDefs = enemyRegistry.getEnemies();
    for (const EnemyDef& def : enemyDefs) {
    enemies.push_back(Enemy(def));
    }

    AbilityRegistry abilityRegistry;
    abilityRegistry.load(input);
    std::vector<AbilityDef> abilityDefs = abilityRegistry.getAbilities();
    for (const AbilityDef& def : abilityDefs) {
        abilities.push_back(Ability(def));
    }

    ItemRegistry itemRegistry;
    itemRegistry.load(input);
    std::vector<ItemDef> itemDefs = itemRegistry.getItems();
    for (const ItemDef& def : itemDefs) {
        items.push_back(Item(def));
    }

    DialogNodeRegistry dialogNodeRegistry;
    dialogNodeRegistry.load(input);
    std::vector<DialogNodeDef> dialogNodeDefs = dialogNodeRegistry.getDialogNodes();
    for (const DialogNodeDef& def : dialogNodeDefs) {
        dialogNodes.push_back(DialogNode(def));
    }

    DialogChoiceRegistry dialogChoiceRegistry;
    dialogChoiceRegistry.load(input);
    std::vector<DialogChoiceDef> dialogChoiceDefs = dialogChoiceRegistry.getDialogChoices();
    for (const DialogChoiceDef& def : dialogChoiceDefs) {
        dialogChoices.push_back(DialogChoice(def));
    }

    SceneRegistry sceneRegistry;
    sceneRegistry.load(input);
    std::vector<SceneDef> sceneDefs = sceneRegistry.getScenes();
    for (const SceneDef& def : sceneDefs) {
        scenes.push_back(Scene(def));
    }
}

void saveGame(Player & player, std::vector<Location> & locations, std::vector<Enemy> & enemies, std::vector<Ability> & abilities, std::vector<Item> & items, std::vector<DialogNode> & dialogNodes, std::vector<DialogChoice> & dialogChoices) {
        std::ofstream output("data.txt");
        PlayerRegistry playerRegistry;
        PlayerDef playerDef = playerRegistry.toPlayerDef(player);
        playerRegistry.setPlayer(playerDef);
        playerRegistry.save(output);

        LocationRegistry locationRegistry;
        std::vector<LocationDef> locationDefs = locationRegistry.toLocationDefs(locations);
        locationRegistry.setLocations(locationDefs);
        locationRegistry.save(output);

        EnemyRegistry enemyRegistry;
        std::vector<EnemyDef> enemyDefs = enemyRegistry.toEnemyDefs(enemies);
        enemyRegistry.setEnemies(enemyDefs);
        enemyRegistry.save(output);

        AbilityRegistry abilityRegistry;
        std::vector<AbilityDef> abilityDefs = abilityRegistry.toAbilityDefs(abilities);
        abilityRegistry.setAbilities(abilityDefs);
        abilityRegistry.save(output);

        ItemRegistry itemRegistry;
        std::vector<ItemDef> itemDefs = itemRegistry.toItemDefs(items);
        itemRegistry.setItems(itemDefs);
        itemRegistry.save(output);

        DialogNodeRegistry dialogNodeRegistry;
        std::vector<DialogNodeDef> dialogNodeDefs = dialogNodeRegistry.toDialogNodeDefs(dialogNodes);
        dialogNodeRegistry.setDialogNodes(dialogNodeDefs);
        dialogNodeRegistry.save(output);

        DialogChoiceRegistry dialogChoiceRegistry;
        std::vector<DialogChoiceDef> dialogChoiceDefs = dialogChoiceRegistry.toDialogChoiceDefs(dialogChoices);
        dialogChoiceRegistry.setDialogChoices(dialogChoiceDefs);
        dialogChoiceRegistry.save(output);
    }

void lootItems(std::vector<Item>& items, Player& player, Location* currentLocation) {
  std::vector<int>& locationItems = currentLocation->getItems();
    std::vector<int>& playerInventory = player.getInventory(); 
    while (!locationItems.empty())
    {
        std::cout << "Предметы на локации:" << std::endl;
        std::cout << "0: Выйти" << std::endl;
        for (int i = 0; i < locationItems.size(); ++i) {
            Item* item = findItemById(locationItems[i], items);
            if (item) {
                std::cout << i + 1 << ": " << item->getName() << std::endl;
            }
        }

        int choice = -1;
        std::cout << "Выберите предмет для подбора: " << std::endl;
        std::cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice > 0 && choice <= locationItems.size()) {
            int itemId = locationItems[choice - 1];
            playerInventory.push_back(itemId); 
            locationItems.erase(locationItems.begin() + (choice - 1));
            std::cout << "Предмет подобран!" << std::endl;
        } else {
            std::cout << "Неверный выбор, попробуйте снова." << std::endl;
        }
    }

    if (locationItems.empty()) {
        std::cout << "На локации больше нет предметов." << std::endl;
    }
}

void lootAbilities(std::vector<Ability>& abilities, Player& player, Location* currentLocation) {
  std::vector<int>& locationAbilities= currentLocation->getAbilities();
    std::vector<int>& playerAbilities = player.getAbilities(); 
    while (!locationAbilities.empty())
    {
        std::cout << "Способности на локации:" << std::endl;
        std::cout << "0: Выйти" << std::endl;
        for (int i = 0; i < locationAbilities.size(); ++i) {
            Ability* ability = findAbilityById(locationAbilities[i], abilities);
            if (ability) {
                std::cout << i + 1 << ": " << ability->getName() << std::endl;
            }
        }

        int choice = -1;
        std::cout << "Выберите способность: " << std::endl;
        std::cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice > 0 && choice <= locationAbilities.size()) {
            int itemId = locationAbilities[choice - 1];
            playerAbilities.push_back(itemId); 
            locationAbilities.erase(locationAbilities.begin() + (choice - 1));
            std::cout << "Появилась новая способность!" << std::endl;
        } else {
            std::cout << "Неверный выбор, попробуйте снова." << std::endl;
        }
    }

    if (locationAbilities.empty()) {
        std::cout << "На локации больше нет способностей." << std::endl;
    }
}

void move(Player& player, std::vector<Location>& locations, int& enemiesCount){
    while (true){
        Location *currentLocation = findLocationById(player.getLocationId(), locations);
        std::cout << "Ваше текущее местоположение: " << currentLocation->getName() << std::endl;
        std::cout << "Вы можете пойти в следующие места: " << std::endl;
        std::vector<Location*> nearlyLocations;
        int finalBossLocationNum = 0;
        for (int i = 0; i < currentLocation->getChoices().size(); i++)
        {
            Location* nearlyLocation = findLocationById(currentLocation->getChoices()[i], locations);
            if (nearlyLocation) {
                nearlyLocations.push_back(nearlyLocation);
                if (nearlyLocation->getIsFinalBossLocation() && player.getEnemiesCount() != (enemiesCount - 1)){
                    std::cout << i + 1 << ": " << nearlyLocation->getName() << "(вы еще не готовы)" << std::endl;
                    finalBossLocationNum = i + 1;
                }
                else
                {
                    std::cout << i + 1 << ": " << nearlyLocation->getName() << std::endl;
                }
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
            if (finalBossLocationNum == userChoice && player.getEnemiesCount() != (enemiesCount - 1)){
                return;
            }
            else
            {
                player.setLocationId(nearlyLocations[userChoice - 1]->getId());
            }
        }
        else
        {
            std::cout << "Такого варианта нет" << std::endl;
        }
    }
}

void showInventory(std::vector<Item>& items, Player& player) {
    std::vector<int> &inventory = player.getInventory();
    while (true)
    {
        std::cout << "Ваш инвентарь:" << std::endl;

        if (inventory.empty()) {
            std::cout << "Инвентарь пуст." << std::endl;
            return;
        }

        for (int i = 0; i < inventory.size(); i++) {
            Item* item = findItemById(inventory[i], items);
            if (item != nullptr) {
                std::cout << i + 1 << ": " << item->getName() << std::endl;
            }
        }

        std::cout << "Введите номер предмета, чтобы использовать (0 для выхода): ";
        int input;
        std::cin >> input;

        if (input == 0) break;

        if (input < 1 || input > inventory.size()) {
            std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
            continue;
        }

        int itemId = inventory[input - 1];
        Item* item = findItemById(itemId, items);

        if (!item) {
            std::cout << "Ошибка: предмет не найден." << std::endl;
            continue;
        }

        char type = item->getType();
        switch (type) {
            case 'f':
                player.setHp(player.getHp() + item->getFactor());
                std::cout << "Вы выбрали еду: " << item->getName() << std::endl;
                std::cout << "Вы восстановили " << item->getFactor() << " здоровья." << std::endl;
                break;
            case 'w':
                player.setChosenWeaponId(item->getId());
                std::cout << "Вы выбрали оружие: " << item->getName() << std::endl;
                break;
            default:
                std::cout << "Предмет не может быть использован." << std::endl;
                continue;
        }

        if (type != 'w'){
            inventory.erase(inventory.begin() + (input - 1));
        }
    }
}

void changeAbilities(std::vector<int>& playerAbilities, std::vector<Ability>& abilities, std::array<int, 3>& playerChosenAbilities) {
    int inputAbilityIndex = -1;
    int replaceIndex = -1;

    while (true) {
        std::cout << "Все способности:" <<std::endl;
        for (int i = 0; i < playerAbilities.size(); i++) {
            Ability* ability = findAbilityById(playerAbilities[i], abilities);
            if (ability != nullptr) {
                std::cout << i + 1 << ": " << ability->getName() << std::endl;
            }
        }

        std::cout << "Выбранные способности:" <<std::endl;
        for (int i = 0; i < playerChosenAbilities.size(); i++) {
            Ability* ability = findAbilityById(playerChosenAbilities[i], abilities);
            if (ability != nullptr) {
                std::cout << i + 1 << ": " << ability->getName() << std::endl;
            }
        }

        std::cout << "Введите номер способности для замены (0 для выхода): ";
        std::cin >> inputAbilityIndex;

        if (inputAbilityIndex == 0) break;

        if (inputAbilityIndex < 1 || inputAbilityIndex > playerAbilities.size()) {
            std::cout << "Некорректный ввод. Попробуйте снова." << std::endl;
            continue;
        }

        int selectedAbilityId = playerAbilities[inputAbilityIndex - 1];

        bool alreadyChosen = false;
        for (int i = 0; i < playerChosenAbilities.size(); i++) {
            if (playerChosenAbilities[i] == selectedAbilityId) {
                alreadyChosen = true;
                break;
            }
        }

        if (alreadyChosen) {
            std::cout << "Эта способность уже выбрана. Выберите другую."<<std::endl;
            continue;
        }

        std::cout << "Введите номер выбранной способности, которую хотите заменить (1-3): ";
        std::cin >> replaceIndex;

        if (replaceIndex < 1 || replaceIndex > 3) {
            std::cout << "Некорректный выбор замены." << std::endl;
            continue;
        }

        playerChosenAbilities[replaceIndex - 1] = selectedAbilityId;
        std::cout << "Способность заменена!" <<std::endl;
    }
}

void showItemDescriptions(const std::vector<int>& inventory, std::vector<Item>& items) {
    while (true) {
        std::cout << "Ваш инвентарь. Введите номер предмета для просмотра описания (0 для выхода):" << std::endl;
        for (int i = 0; i < inventory.size(); ++i) {
            const Item* item = findItemById(inventory[i], items);
            if (item != nullptr) {
                std::cout << i + 1 << ": " << item->getName() << std::endl;
            }
        }

        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        if (choice < 1 || choice > inventory.size()) {
            std::cout << "Некорректный выбор. Попробуйте снова." << std::endl;
            continue;
        }

        const Item* selected = findItemById(inventory[choice - 1], items);
        if (selected) {
            std::cout << "Описание предмета " << selected->getName() << ":" << std::endl;
            std::cout << selected->getDescription()<< std::endl;
        }
    }
}

void showAbilityDescriptions(const std::vector<int>& playerAbilities, std::vector<Ability>& abilities) {
    while (true) {
        std::cout << "Выберите способность для просмотра описания (0 для выхода):" << std::endl;
        for (int i = 0; i < playerAbilities.size(); ++i) {
            const Ability* ability = findAbilityById(playerAbilities[i], abilities);
            if (ability != nullptr) {
                std::cout << i + 1 << ": " << ability->getName() << std::endl;
            }
        }

        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        if (choice < 1 || choice > playerAbilities.size()) {
            std::cout << "Некорректный выбор. Попробуйте снова." << std::endl;
            continue;
        }

        const Ability* selected = findAbilityById(playerAbilities[choice - 1], abilities);
        if (selected) {
            std::cout << "Описание способности " << selected->getName() << ":" << std::endl;
            std::cout << selected->getDescription() << std::endl;
        }
    }
}

void showEnemiesDescriptions(const std::vector<int>& playerEnemies, std::vector<Enemy>& enemies) {
    std::cout << "Ваши побежденные враги" << std::endl;
    while (true)
    {
        std::cout << "Выберите врага для просмотра описания (0 для выхода):" << std::endl;
        for (int i = 0; i < playerEnemies.size(); ++i) {
            const Enemy* enemy = findEnemyById(playerEnemies[i], enemies);
            if (enemy != nullptr) {
                std::cout << i + 1 << ": " << enemy->getName() << std::endl;
            }
        }

        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        if (choice < 1 || choice > playerEnemies.size()) {
            std::cout << "Некорректный выбор. Попробуйте снова." << std::endl;
            continue;
        }

        const Enemy* selected = findEnemyById(playerEnemies[choice - 1], enemies);
        if (selected) {
            std::cout << "Описание способности " << selected->getName() << ":" << std::endl;
            std::cout << selected->getDescription() << std::endl;
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
                enemy->setShield(enemy->getShield() - ability->getFactor());
                if (enemy->getShield() > 0)
                {
                    std::cout << "Вы ударили в блок" << std::endl;
                }
                else
                {
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
                player.setShield(player.getShield() - ability->getFactor());
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

void fight(Player& player, int enemyId, std::vector<Enemy>& enemies, std::vector<Ability>& abilities, Location* currentLocation){
    Enemy* enemy = findEnemyById(enemyId, enemies);
    Ability *player1Ability = findAbilityById(player.getChosenAbilities()[0], abilities);
    Ability *player2Ability = findAbilityById(player.getChosenAbilities()[1], abilities);
    Ability *player3Ability = findAbilityById(player.getChosenAbilities()[2], abilities);
    Ability *enemy1Ability = findAbilityById(enemy->getAbilities()[0], abilities);
    Ability *enemy2Ability = findAbilityById(enemy->getAbilities()[1], abilities);
    Ability *enemy3Ability = findAbilityById(enemy->getAbilities()[2], abilities);
    int playerHp = player.getHp();
    int enemyHp = enemy->getHp();
    std::cout << "Ваш враг: " << enemy->getName() << std::endl;
    do
    {
        player.initDodgeCount();
        enemy->initDodgeCount();
        std::cout << "Введите" << std::endl;
        std::cout << "1: Атака" << std::endl;
        std::cout << "2: Защита" << std::endl;
        std::cout << "3: Уклонение" << std::endl;
        std::cout << "4: " << player1Ability->getName() << std::endl;
        std::cout << "5: " << player2Ability->getName() << std::endl;
        std::cout << "6: " << player3Ability->getName() << std::endl;
        int userChoice = 0;
        srand(time(0));
        int enemyChoice = 3;
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
            enemy->setIsDodgeOn(1);            
            std::cout << "Враг уклонился" << std::endl;
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
        } else if (userChoice >= 4 && userChoice <= 6 && (enemyChoice <= 3 || enemyChoice >= 2)) {
            if (enemyChoice == 2 && enemy->getShield() > 0){
                enemy->setIsShieldOn(1);
            } 
            if (enemyChoice == 3 && enemy->getIsDodgeOn() == 0){
                enemy->setIsDodgeOn(1);          
            }
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
        } else {
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
        player.refreshStatsAfterRound();
        enemy->refreshStatsAfterRound();
        enemy1Ability->refreshMovesCount();
        enemy2Ability->refreshMovesCount();
        enemy3Ability->refreshMovesCount();
        player1Ability->refreshMovesCount();
        player2Ability->refreshMovesCount();
        player3Ability->refreshMovesCount();  
        if (enemy->getHp() <= 0)
        {
            std::cout << "Вы победили" << std::endl;
            player.addToEnemies(enemyId);
            currentLocation->setItems(enemy->getItems());
            currentLocation->setEnemyId(0);
            currentLocation->setDialogNodeId(0);
        }
            else if (player.getHp() <= 0)
            {
                std::cout << "Вы проиграли" << std::endl;
                player.loseRound(playerHp);
                enemy->winRound(enemyHp);
                return;
            }
            else
            {
                player.afterRoundInfo();
                enemy->afterRoundInfo();
                player1Ability->countMoves();
                player2Ability->countMoves();
                player3Ability->countMoves();
            }

    } while (enemy->getHp() > 0 && player.getHp() > 0);
}

void showChosenWeapon(Player& player, std::vector<Item>& items){
    Item* item = findItemById(player.getChosenWeaponId(), items);
    if (item != nullptr){
    std::cout << "Вы используете оружие: " << item->getName() << std::endl;
    std::cout << item->getDescription() << std::endl;
    } 
}

void showMenu(Player& player, std::vector<Location>& locations, std::vector<Enemy>& enemies, std::vector<Ability>& abilities, std::vector<Item>& items, std::vector<DialogNode>& dialogNodes, std::vector<DialogChoice>& dialogChoices) {
    int userChoice = 0;

    while (player.getEnemiesCount() != enemies.size()) {
        Location* currentLocation = findLocationById(player.getLocationId(), locations);
        int enemyId = currentLocation->getEnemyId();
        int dialogNodeId = currentLocation->getDialogNodeId();
        std::vector<int>& locationItems = currentLocation->getItems();
        std::vector<int>& locationAbilities = currentLocation->getAbilities();
        std::vector<int>& playerAbilities = player.getAbilities();
        std::array<int, 3>& playerChosenAbilities = player.getChosenAbilities();

        std::cout << currentLocation->getDescription() << std::endl;

        std::cout << "Меню:" << std::endl;

        std::vector<std::string> options;
        options.push_back("Сменить локацию");
        options.push_back("Показать инвентарь");
        options.push_back("Выбрать способности");
        options.push_back("Показать описания способностей");
        options.push_back("Показать описания предметов");
        options.push_back("Показать описания побеждённых врагов");
        if (player.getChosenWeaponId() != 0){
        options.push_back("Показать оружие");
        }
        if (enemyId != 0)
        {
            options.push_back("Вступить в бой");
            std::cout << "На локации присутсвтует враг " << findEnemyById(enemyId, enemies)->getName() << std::endl;
        }
        if (dialogNodeId != 0)
        {
            options.push_back("Поговорить");
        }
        if (!locationItems.empty()) {
            options.push_back("Осмотреть предметы на локации");
        }
        if (!locationAbilities.empty()) {
            options.push_back("Осмотреть способности на локации");
        }

        for (int i = 0; i < options.size(); i++) {
            std::cout << (i + 1) << ": " << options[i] << std::endl;
        }

        std::cin >> userChoice;

        if (userChoice < 1 || userChoice > options.size()) {
            std::cout << "Неверный ввод. Попробуйте снова." << std::endl;
            continue;
        }
        std::string selectedOption = options[userChoice - 1];
        int enemiesCount = enemies.size();
        if (selectedOption == "Сменить локацию")
        {
            move(player, locations, enemiesCount);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices);
        }
        else if (selectedOption == "Показать инвентарь")
        {
            showInventory(items, player);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices);
        }
        else if (selectedOption == "Выбрать способности")
        {
            changeAbilities(playerAbilities, abilities, playerChosenAbilities);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices);
        }
        else if (selectedOption == "Вступить в бой")
        {
            fight(player, enemyId, enemies, abilities, currentLocation);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices);
        }
        else if (selectedOption == "Осмотреть предметы на локации")
        {
            lootItems(items, player, currentLocation);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices);
        }  else if (selectedOption == "Осмотреть способности на локации"){
            lootAbilities(abilities, player, currentLocation);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices);
        } else if (selectedOption == "Поговорить") {
            startDialog(1, dialogNodes, dialogChoices, dialogNodeId, currentLocation);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices);
        } else if (selectedOption == "Показать описания способностей") {
            showAbilityDescriptions(playerAbilities, abilities);
        } else if (selectedOption == "Показать описания предметов") {
            showItemDescriptions(playerAbilities, items);
        } else if (selectedOption == "Показать оружие") {
            showChosenWeapon(player, items);
        } else if (selectedOption == "Показать описания побеждённых врагов") {
            showEnemiesDescriptions(player.getEnemies(), enemies);
        }
    }
}

int main(int argc, char* argv[]){
    std::ifstream input("data.txt");

    Player player;
    std::vector<Location> locations;
    std::vector<Enemy> enemies;
    std::vector<Ability> abilities;
    std::vector<Item> items;
    std::vector<DialogNode> dialogNodes;
    std::vector<DialogChoice> dialogChoices;
    std::vector<Scene> scenes;
    downloadData(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, scenes);
    initNewGame();
    showMenu(player, locations, enemies, abilities, items, dialogNodes, dialogChoices);
    endGame(scenes);
    return 0;
}