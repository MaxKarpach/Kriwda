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

Item* findItemById(int itemId, std::vector<Item>& items) {
    for (auto& item : items) {
        if (item.getId() == itemId) {
            return &item;
        }
    }
    return nullptr;
}

void startDialog(int dialogId,std::vector<DialogNode>& dialogNodes,std::vector<DialogChoice>& dialogChoices, int currentNodeId) {
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

void loot(std::vector<int>& locationItems, std::vector<Item>& items, std::vector<int>& playerInventory) {
    while (!locationItems.empty()) {
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

void showInventory(std::vector<int>& inventory, std::vector<Item>& items, Player& player) {
    while (true) {
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

void showMenu(Player& player, std::vector<Location>& locations, std::vector<Enemy>& enemies, std::vector<Ability>& abilities, std::vector<Item>& items, std::vector<DialogNode>& dialogNodes, std::vector<DialogChoice>& dialogChoices) {
    int userChoice = 0;

    while (true) {
        Location* currentLocation = findLocationById(player.getLocationId(), locations);
        int enemyId = currentLocation->getEnemyId();
        int dialogNodeId = currentLocation->getDialogNodeId();
        std::vector<int> locationItems = currentLocation->getItems();
        std::vector<int> inventory = player.getInventory();
        std::vector<int> playerAbilities = player.getAbilities();
        std::array<int, 3> playerChosenAbilities = player.getChosenAbilities();

        std::cout << "Меню:" << std::endl;

        std::vector<std::string> options;
        options.push_back("Сменить локацию");
        options.push_back("Показать инвентарь");
        options.push_back("Выбрать способности");
        options.push_back("Показать описания способностей");
        options.push_back("Показать описания предметов");
        if (enemyId != 0)
        {
            options.push_back("Вступить в бой");
        }
        if (dialogNodeId != 0)
        {
            options.push_back("Поговорить");
        }
        if (!locationItems.empty()) {
            options.push_back("Осмотреть предметы на локации");
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

        if (selectedOption == "Сменить локацию") {
            move(player, locations);
        } else if (selectedOption == "Показать инвентарь") {
            showInventory(inventory, items, player);
        } else if (selectedOption == "Выбрать способности") {
            changeAbilities(playerAbilities, abilities, playerChosenAbilities);
        }
        else if (selectedOption == "Вступить в бой")
        {
            fight(player, enemyId, enemies, abilities);
        }
        else if (selectedOption == "Осмотреть предметы на локации")
        {
            loot(locationItems, items, inventory);
            player.setInventory(inventory);
        } else if (selectedOption == "Поговорить") {
            startDialog(1, dialogNodes, dialogChoices, dialogNodeId);
        } else if (selectedOption == "Показать описания способностей") {
            showAbilityDescriptions(playerAbilities, abilities);
        } else if (selectedOption == "Показать описания предметов") {
            showItemDescriptions(playerAbilities, items);
        } 
    }
}

void saveGame(Player& player, std::vector<Location>& locations, std::vector<Enemy>& enemies, std::vector<Ability>& abilities, std::vector<Item>& items, std::vector<DialogNode>& dialogNodes, std::vector<DialogChoice>& dialogChoices){

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

    DialogNodeRegistry dialogNodeRegistry;
    dialogNodeRegistry.load(input);
    std::vector<DialogNodeDef> dialogNodeDefs = dialogNodeRegistry.getDialogNodes();
    std::vector<DialogNode> dialogNodes;
    for (const DialogNodeDef& def : dialogNodeDefs) {
        dialogNodes.push_back(DialogNode(def));
    }

    DialogChoiceRegistry dialogChoiceRegistry;
    dialogChoiceRegistry.load(input);
    std::vector<DialogChoiceDef> dialogChoiceDefs = dialogChoiceRegistry.getDialogChoices();
    std::vector<DialogChoice> dialogChoices;
    for (const DialogChoiceDef& def : dialogChoiceDefs) {
        dialogChoices.push_back(DialogChoice(def));
    }

    Game game;
    game.initNewGame();
    showMenu(player, locations, enemies, abilities, items, dialogNodes, dialogChoices);
    return 0;
}
