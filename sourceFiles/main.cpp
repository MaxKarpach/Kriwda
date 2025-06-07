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
#include "../headerFiles/BattleSystem.h"
#include "../headerFiles/Game.h" 
template<typename T> T* findById(int id, std::vector<T>& vec) {
    for (auto& obj : vec) {
        if (obj.getId() == id) {
            return &obj;
        }
    }
    return nullptr;
}

void startDialog(std::vector<DialogNode>& dialogNodes,std::vector<DialogChoice>& dialogChoices, int currentNodeId, Location* currentLocation, Renderer& renderer) {
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
            renderer.printEndlineText("Ошибка: узел диалога не найден.");
            break;
        }

        if (currentNode->getDescription() != ""){
            renderer.printEndlineText(currentNode->getDescription());
        }

        if (currentNode->getChoices().size() == 0){
            currentLocation->setDialogNodeId(0);
        }

        renderer.printText(currentNode->getName());
        renderer.printText(": ");
        renderer.printEndlineText(currentNode->getText());

        std::vector<DialogChoice*> currentChoices;
        for (int choiceId : currentNode->getChoices()) {
            for (auto& choice : dialogChoices) {
                if (choice.getId() == choiceId && !choice.getIsUsed()) {
                currentChoices.push_back(&choice);
                break;
                }
            }
        }

        if (currentChoices.empty()) {
            break;
        }

        for (int i = 0; i < currentChoices.size(); ++i) {
            renderer.printText(i + 1);
            renderer.printText(": ");
            renderer.printEndlineText(currentChoices[i]->getText());
        }

        int userChoice = 0;
        renderer.printText("Выберите вариант (0 — выход): ");
        std::cin >> userChoice;

        if (userChoice <= 0 || userChoice > currentChoices.size()) {
            renderer.printEndlineText("Диалог прерван.");
            break;
        }

        currentNodeId = currentChoices[userChoice - 1]->getNextNodeId();
        currentChoices[userChoice - 1]->setisUsed(1);
        if (currentChoices[userChoice - 1]->getNextNodeId() == 0){
            currentLocation->setDialogNodeId(0);
            break;
        }
    }
}

void downloadData(Player& player, std::vector<Location>& locations, std::vector<Enemy>& enemies, std::vector<Ability>& abilities, std::vector<Item>& items, std::vector<DialogNode>& dialogNodes, std::vector<DialogChoice>& dialogChoices, std::vector<Scene>& scenes, Game& game){
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

    GameRegistry gameRegistry;
    gameRegistry.load(input);
    game.setIsGameStarted(gameRegistry.getGameStats().isGameStarted);
    game.setIsGameLoopEnded(gameRegistry.getGameStats().isGameLoopEnded);
    game.setIsGameEnded(gameRegistry.getGameStats().isGameEnded);
}

void saveGame(Player& player, std::vector<Location>& locations, std::vector<Enemy>& enemies, std::vector<Ability>& abilities, std::vector<Item>& items, std::vector<DialogNode>& dialogNodes, std::vector<DialogChoice>& dialogChoices, Game& game, std::vector<Scene>& scenes) {
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

        SceneRegistry sceneRegistry;
        std::vector<SceneDef> sceneDefs = sceneRegistry.toSceneDefs(scenes);
        sceneRegistry.setScenes(sceneDefs);
        sceneRegistry.save(output);

        GameRegistry gameRegistry;
        GameStatsDef gameDef = gameRegistry.toGameStatsDef(game);
        gameRegistry.setGameStats(gameDef);
        gameRegistry.save(output);
}

template <typename T> void loot(std::vector<T>& dataPool, Player& player, Location* currentLocation, Renderer& renderer, std::vector<int>& (Location::*getLocationData)(), std::vector<int>& (Player::*getPlayerData)(),const std::string& title, const std::string& successMessage, const std::string& emptyMessage) {
    std::vector<int>& locationData = (currentLocation->*getLocationData)();
    std::vector<int>& playerData = (player.*getPlayerData)();

    while (!locationData.empty()) {
        renderer.printEndlineText(title + " на локации" + ":");
        renderer.printEndlineText("0: Выйти");

        for (int i = 0; i < locationData.size(); ++i) {
            T* item = findById<T>(locationData[i], dataPool);
            if (item) {
                renderer.printText(i + 1);
                renderer.printText(": ");
                renderer.printEndlineText(item->getName());
            }
        }

        int choice = -1;
        renderer.printEndlineText("Выберите элемент: ");
        std::cin >> choice;

        if (choice == 0) break;

        if (choice > 0 && choice <= locationData.size()) {
            int id = locationData[choice - 1];
            playerData.push_back(id);
            locationData.erase(locationData.begin() + (choice - 1));
            renderer.printEndlineText(successMessage);
        } else {
            renderer.printEndlineText("Неверный выбор, попробуйте снова.");
        }
    }

    if (locationData.empty()) {
        renderer.printEndlineText("На локации больше нет " + emptyMessage);
    }
}

void move(Player& player, std::vector<Location>& locations, int& enemiesCount, Renderer& renderer){
    while (true){
        Location *currentLocation = findById<Location>(player.getLocationId(), locations);
        renderer.printText("Ваше текущее местоположение: ");
        renderer.printEndlineText(currentLocation->getName());
        renderer.printEndlineText("Вы можете пойти в следующие места: ");
        std::vector<Location*> nearlyLocations;
        int finalBossLocationNum = 0;
        for (int i = 0; i < currentLocation->getChoices().size(); i++)
        {
            Location* nearlyLocation = findById<Location>(currentLocation->getChoices()[i], locations);
            if (nearlyLocation) {
                nearlyLocations.push_back(nearlyLocation);
                if (nearlyLocation->getIsFinalBossLocation() && player.getEnemiesCount() != (enemiesCount - 1)){
                    renderer.printText(i + 1);
                    renderer.printText(": ");
                    renderer.printText(nearlyLocation->getName());
                    renderer.printEndlineText("(вы еще не готовы)");
                    finalBossLocationNum = i + 1;
                }
                else
                {
                    renderer.printText(i + 1);
                    renderer.printText(": ");
                    renderer.printEndlineText(nearlyLocation->getName());
                }
            }
        }
        renderer.printText(currentLocation->getChoices().size() + 1);
        renderer.printEndlineText(": Показать меню");
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
            renderer.printEndlineText("Такого варианта нет");
        }
    }
}

void showInventory(std::vector<Item>& items, Player& player, Renderer& renderer) {
    std::vector<int> &inventory = player.getInventory();
    while (true)
    {
        renderer.printEndlineText("Ваш инвентарь:");

        if (inventory.empty()) {
            renderer.printEndlineText("Инвентарь пуст.");
            return;
        }

        for (int i = 0; i < inventory.size(); i++) {
            Item* item = findById<Item>(inventory[i], items);
            if (item != nullptr) {
                renderer.printText(i + 1);
                renderer.printText(": ");
                renderer.printEndlineText(item->getName());
            }
        }
        renderer.printText("Введите номер предмета, чтобы использовать (0 для выхода): ");
        int input;
        std::cin >> input;

        if (input == 0) break;

        if (input < 1 || input > inventory.size()) {
            renderer.printEndlineText("Неверный выбор. Попробуйте снова.");
            continue;
        }

        int itemId = inventory[input - 1];
        Item* item = findById<Item>(itemId, items);

        if (!item) {
            renderer.printEndlineText("Ошибка: предмет не найден.");
            continue;
        }

        char type = item->getType();
        switch (type) {
            case 'f':
                player.setHp(player.getHp() + item->getFactor());
                renderer.printText("Вы выбрали еду: ");
                renderer.printEndlineText(item->getName());
                renderer.printText("У вас теперь ");
                renderer.printText(player.getHp());
                renderer.printEndlineText(" здоровья.");
                break;
            case 'w':
                player.setChosenWeaponId(item->getId());
                renderer.printText("Вы выбрали оружие: ");
                renderer.printEndlineText(item->getName());
                break;
            default:
                renderer.printEndlineText("Предмет не может быть использован.");
                continue;
        }

        if (type != 'w'){
            inventory.erase(inventory.begin() + (input - 1));
        }
    }
}

void changeAbilities(std::vector<int>& playerAbilities, std::vector<Ability>& abilities, std::array<int, 3>& playerChosenAbilities, Renderer& renderer) {
    int inputAbilityIndex = -1;
    int replaceIndex = -1;

    while (true) {
        renderer.printEndlineText("Все способности:");
        for (int i = 0; i < playerAbilities.size(); i++) {
            Ability* ability = findById<Ability>(playerAbilities[i], abilities);
            if (ability != nullptr) {
                renderer.printText(i + 1);
                renderer.printText(": ");
                renderer.printEndlineText(ability->getName());
            }
        }
        renderer.printEndlineText("Выбранные способности:");
        for (int i = 0; i < playerChosenAbilities.size(); i++) {
            Ability* ability = findById<Ability>(playerChosenAbilities[i], abilities);
            if (ability != nullptr) {
                renderer.printText(i + 1);
                renderer.printText(": ");
                renderer.printEndlineText(ability->getName());
            }
        }
        renderer.printEndlineText("Введите номер способности для замены (0 для выхода): ");
        std::cin >> inputAbilityIndex;

        if (inputAbilityIndex == 0) break;

        if (inputAbilityIndex < 1 || inputAbilityIndex > playerAbilities.size()) {
            renderer.printEndlineText("Некорректный ввод. Попробуйте снова.");
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
            renderer.printEndlineText("Эта способность уже выбрана. Выберите другую.");
            continue;
        }
        renderer.printEndlineText("Введите номер выбранной способности, которую хотите заменить (1-3): ");
        std::cin >> replaceIndex;

        if (replaceIndex < 1 || replaceIndex > 3) {
            renderer.printEndlineText("Некорректный выбор замены.");
            continue;
        }

        playerChosenAbilities[replaceIndex - 1] = selectedAbilityId;
        renderer.printEndlineText("Способность заменена!");
    }
}

template <typename T> void showDataDescription(const std::vector<int>& playerData, std::vector<T>& data, Renderer& renderer, const std::string& description){
    while (true) {
        renderer.printText(description);
        renderer.printEndlineText(" Введите номер предмета для просмотра описания (0 для выхода):");
        for (int i = 0; i < playerData.size(); ++i) {
            const T* subject = findById<T>(playerData[i], data);
            if (subject != nullptr) {
                renderer.printText(i + 1);
                renderer.printText(": ");
                renderer.printEndlineText(subject->getName());
            }
        }

        int choice;
        std::cin >> choice;

        if (choice == 0) break;

        if (choice < 1 || choice > playerData.size()) {
            renderer.printEndlineText("Некорректный выбор. Попробуйте снова.");
            continue;
        }

        const T* selected = findById<T>(playerData[choice - 1], data);
        if (selected) {
            renderer.printText("Описание ");
            renderer.printText(selected->getName());
            renderer.printEndlineText(":");
            renderer.printEndlineText(selected->getDescription());
        }
    }
}

void showDescriptions(Player& player, std::vector<Item>& items, std::vector<Ability>& abilities, std::vector<Enemy>& enemies, Renderer& renderer){
    int userChoice = 0;
    while (true){
    std::vector<std::string> options;
    options.push_back("Показать описания способностей");
    options.push_back("Показать описания предметов");
    options.push_back("Показать описания побеждённых врагов");
    renderer.printEndlineText("Введите 0 для выхода");
    for (int i = 0; i < options.size(); i++){
        renderer.printText(i + 1);
        renderer.printText(": ");
        renderer.printEndlineText(options[i]);
    }
    std::cin >> userChoice;

    if (userChoice < 0 || userChoice > options.size()) {
            renderer.printEndlineText("Неверный ввод. Попробуйте снова.");
            continue;
    }

    if (userChoice == 0){
        break;
    }

    std::string selectedOption = options[userChoice - 1];
    if (selectedOption == "Показать описания способностей"){
        showDataDescription<Ability>(player.getAbilities(), abilities, renderer, "Ваши способности");
        break;
    }
    else if (selectedOption == "Показать описания предметов"){
        showDataDescription<Item>(player.getInventory(), items, renderer, "Ваши инвентарь");
        break;
    }
    else if (selectedOption == "Показать описания побеждённых врагов"){
        showDataDescription<Enemy>(player.getEnemies(), enemies, renderer, "Ваши враги");
        break;
    }
    }
}

void fight(Player& player, int enemyId, std::vector<Enemy>& enemies, std::vector<Ability>& abilities, Location* currentLocation, Renderer& renderer){
    Enemy* enemy = findById<Enemy>(enemyId, enemies);
    std::vector<Ability*> playerAbilities;
    std::vector<Ability*> enemyAbilities;

    for (int i = 0; i < player.getAbilitiesCount(); i++) {
        playerAbilities.push_back(findById<Ability>(player.getChosenAbilities()[i], abilities));
        enemyAbilities.push_back(findById<Ability>(enemy->getAbilities()[i], abilities));
    }
    BattleSystem battleSystem(player, enemy, renderer, currentLocation, playerAbilities, enemyAbilities);
    battleSystem.battle();
}

void showChosenWeapon(Player& player, std::vector<Item>& items, Renderer& renderer){
    Item* item = findById<Item>(player.getChosenWeaponId(), items);
    if (item != nullptr){
        renderer.printText("Вы используете оружие: ");
        renderer.printEndlineText(item->getName());
        renderer.printEndlineText(item->getDescription());
    } 
}

void showMenu(Player& player, std::vector<Location>& locations, std::vector<Enemy>& enemies, std::vector<Ability>& abilities, std::vector<Item>& items, std::vector<DialogNode>& dialogNodes, std::vector<DialogChoice>& dialogChoices, Renderer& renderer, Game& game, std::vector<Scene>& scenes) {
    int userChoice = 0;

    while (player.getEnemiesCount() != enemies.size()) {
        Location* currentLocation = findById<Location>(player.getLocationId(), locations);
        int enemyId = currentLocation->getEnemyId();
        int dialogNodeId = currentLocation->getDialogNodeId();
        std::vector<int>& locationItems = currentLocation->getItems();
        std::vector<int>& locationAbilities = currentLocation->getAbilities();
        std::vector<int>& playerAbilities = player.getAbilities();
        std::array<int, 3>& playerChosenAbilities = player.getChosenAbilities();
        renderer.printEndlineText(currentLocation->getDescription());

        std::vector<std::string> options;
        options.push_back("Сменить локацию");
        options.push_back("Показать инвентарь");
        options.push_back("Выбрать способности");
        options.push_back("Показать описания");
        if (player.getChosenWeaponId() != 0){
        options.push_back("Показать оружие");
        }
        if (enemyId != 0)
        {
            options.push_back("Вступить в бой");
            renderer.printText("На локации присутсвтует враг ");
            renderer.printEndlineText(findById<Enemy>(enemyId, enemies)->getName());
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
            renderer.printText(i + 1);
            renderer.printText(": ");
            renderer.printEndlineText(options[i]);
        }

        std::cin >> userChoice;

        if (userChoice < 1 || userChoice > options.size()) {
            renderer.printEndlineText("Неверный ввод. Попробуйте снова.");
            continue;
        }
        std::string selectedOption = options[userChoice - 1];
        int enemiesCount = enemies.size();
        if (selectedOption == "Сменить локацию")
        {
            move(player, locations, enemiesCount, renderer);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, game, scenes);
        }
        else if (selectedOption == "Показать инвентарь")
        {
            showInventory(items, player, renderer);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, game, scenes);
        }
        else if (selectedOption == "Выбрать способности")
        {
            changeAbilities(playerAbilities, abilities, playerChosenAbilities, renderer);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, game, scenes);
        }
        else if (selectedOption == "Вступить в бой")
        {
            fight(player, enemyId, enemies, abilities, currentLocation, renderer);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, game, scenes);
        }
        else if (selectedOption == "Осмотреть предметы на локации")
        {
            loot<Item>(items,player,currentLocation,renderer,&Location::getItems,&Player::getInventory,"Предметы","Предмет подобран!", "предметов.");
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, game, scenes);
        }  else if (selectedOption == "Осмотреть способности на локации"){
            loot<Ability>(abilities,player,currentLocation,renderer,&Location::getAbilities,&Player::getAbilities,"Способности","Появилась новая способность!",  "способностей.");
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, game, scenes);
        } else if (selectedOption == "Поговорить") {
            startDialog(dialogNodes, dialogChoices, dialogNodeId, currentLocation, renderer);
            saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, game, scenes);
        } else if (selectedOption == "Показать оружие") {
            showChosenWeapon(player, items, renderer);
        } else if (selectedOption == "Показать описания") {
            showDescriptions(player, items, abilities, enemies, renderer);
        }
    }
    game.setIsGameLoopEnded(1);
    saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, game, scenes);
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
    Renderer renderer;
    Game game(scenes, dialogNodes, dialogChoices, renderer);
    downloadData(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, scenes, game);
    if (!game.getIsGameStarted())
    {
        game.initNewGame(scenes, dialogNodes, dialogChoices, renderer);
        saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, game, scenes);
    }
    if (!game.getIsGameLoopEnded())
    {
        showMenu(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, renderer, game, scenes);
    }
    if (!game.getIsGameEnded()){
        game.endGame(scenes, dialogNodes, dialogChoices, renderer);
        saveGame(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, game, scenes);
    }
    return 0;
}