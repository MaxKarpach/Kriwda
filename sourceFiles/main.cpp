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
#include "../headerFiles/ResourceSystem.h"
#include "../headerFiles/InventorySystem.h"
#include "../headerFiles/LocationSystem.h"
#include "../headerFiles/AbilitiesSystem.h"

template<typename T> T* findById(int id, std::vector<T>& vec) {
  for (auto& obj : vec) {
    if (obj.getId() == id) {
      return &obj;
    }
  }
  return nullptr;
}

void startDialog(std::vector<DialogNode>& dialogNodes, std::vector<DialogChoice>& dialogChoices,
    int currentNodeId, Location* currentLocation, Renderer& renderer) {
  while (true) {
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

    if (currentNode->getDescription() != "") {
      renderer.printEndlineText(currentNode->getDescription());
    }

    if (currentNode->getChoices().size() == 0) {
      currentLocation->setDialogNodeId(0);
    }

    if (currentNode->getName() != "") {
      renderer.printText(currentNode->getName());
      renderer.printText(": ");
      renderer.printEndlineText(currentNode->getText());
    }

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

    renderer.printEndlineText("0: выход");
    for (int i = 0; i < currentChoices.size(); ++i) {
      renderer.printText(i + 1);
      renderer.printText(": ");
      renderer.printEndlineText(currentChoices[i]->getText());
    }

    int userChoice = 0;
    std::cin >> userChoice;

    if (userChoice <= 0 || userChoice > currentChoices.size()) {
      renderer.printEndlineText("Диалог прерван.");
      break;
    }

    currentNodeId = currentChoices[userChoice - 1]->getNextNodeId();
    currentChoices[userChoice - 1]->setisUsed(1);
    if (currentChoices[userChoice - 1]->getNextNodeId() == 0) {
      currentLocation->setDialogNodeId(0);
      break;
    }
  }
}

template <typename T> void loot(std::vector<T>& dataPool, Player& player, Location* currentLocation,
    Renderer& renderer, std::vector<int>& (Location::*getLocationData)(), std::vector<int>& (Player::*getPlayerData)(),
    const std::string& title, const std::string& successMessage, const std::string& emptyMessage) {
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

template <typename T> void showDataDescription(const std::vector<int>& playerData, std::vector<T>& data,
    Renderer& renderer, const std::string& description) {
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

void showDescriptions(Player& player, std::vector<Item>& items, std::vector<Ability>& abilities,
    std::vector<Enemy>& enemies, Renderer& renderer) {
  int userChoice = 0;
  while (true) {
    std::vector<std::string> options;
    options.push_back("Показать описания способностей");
    options.push_back("Показать описания предметов");
    options.push_back("Показать описания побеждённых врагов");
    renderer.printEndlineText("Введите 0 для выхода");
    for (int i = 0; i < options.size(); i++) {
      renderer.printText(i + 1);
      renderer.printText(": ");
      renderer.printEndlineText(options[i]);
    }
    std::cin >> userChoice;

    if (userChoice < 0 || userChoice > options.size()) {
      renderer.printEndlineText("Неверный ввод. Попробуйте снова.");
      continue;
    }

    if (userChoice == 0) {
      break;
    }

    std::string selectedOption = options[userChoice - 1];
    if (selectedOption == "Показать описания способностей") {
      showDataDescription<Ability>(player.getAbilities(), abilities, renderer, "Ваши способности");
      break;
    } else if (selectedOption == "Показать описания предметов") {
      showDataDescription<Item>(player.getInventory(), items, renderer, "Ваши инвентарь");
      break;
    } else if (selectedOption == "Показать описания побеждённых врагов") {
      showDataDescription<Enemy>(player.getEnemies(), enemies, renderer, "Ваши враги");
      break;
    }
  }
}

void fight(Player& player, int enemyId, std::vector<Enemy>& enemies, std::vector<Ability>& abilities,
    Location* currentLocation, Renderer& renderer) {
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

void showMenu(Player& player, std::vector<Location>& locations, std::vector<Enemy>& enemies,
    std::vector<Ability>& abilities, std::vector<Item>& items, std::vector<DialogNode>& dialogNodes,
    std::vector<DialogChoice>& dialogChoices, Renderer& renderer, Game& game, std::vector<Scene>& scenes, ResourceSystem& resourceSystem) {
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
    if (player.getChosenWeaponId() != 0) {
      options.push_back("Показать оружие");
    }
    if (enemyId != 0) {
      options.push_back("Вступить в бой");
      renderer.printText("На локации присутствует враг ");
      renderer.printEndlineText(findById<Enemy>(enemyId, enemies)->getName());
    }
    if (dialogNodeId != 0) {
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
    if (selectedOption == "Сменить локацию") {
      LocationSystem locationSystem(player, locations, enemiesCount, renderer);
      locationSystem.move();
      resourceSystem.saveGame();
    } else if (selectedOption == "Показать инвентарь") {
      InventorySystem inventorySystem(player, items, renderer);
      inventorySystem.showInventory();
      resourceSystem.saveGame();
    } else if (selectedOption == "Выбрать способности") {
      AbilitiesSystem abilitiesSystem(player, abilities, renderer);
      abilitiesSystem.changeAbilities();
      resourceSystem.saveGame();
    } else if (selectedOption == "Вступить в бой") {
      fight(player, enemyId, enemies, abilities, currentLocation, renderer);
      resourceSystem.saveGame();
    } else if (selectedOption == "Осмотреть предметы на локации") {
      loot<Item>(items, player, currentLocation, renderer,
          &Location::getItems, &Player::getInventory,
          "Предметы", "Предмет подобран!", "предметов.");
      resourceSystem.saveGame();
    } else if (selectedOption == "Осмотреть способности на локации") {
      loot<Ability>(abilities, player, currentLocation, renderer,
          &Location::getAbilities, &Player::getAbilities,
          "Способности", "Появилась новая способность!", "способностей.");
      resourceSystem.saveGame();
    } else if (selectedOption == "Поговорить") {
      startDialog(dialogNodes, dialogChoices, dialogNodeId, currentLocation, renderer);
      resourceSystem.saveGame();
    } else if (selectedOption == "Показать оружие") {
      InventorySystem inventorySystem(player, items, renderer);
      inventorySystem.showChosenWeapon();
    } else if (selectedOption == "Показать описания")
    {
      showDescriptions(player, items, abilities, enemies, renderer);
    }
  }
  game.setIsGameLoopEnded(1);
  resourceSystem.saveGame();
}

int main(int argc, char* argv[]) {
  std::string fileName = "data.txt";
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
  ResourceSystem resourceSystem(player, locations, enemies, abilities, items,
                                dialogNodes, dialogChoices, scenes, game, fileName);
  resourceSystem.downloadData();
  if (!game.getIsGameStarted()) {
    game.initNewGame(scenes, dialogNodes, dialogChoices, renderer);
    resourceSystem.saveGame();
  }
  if (!game.getIsGameLoopEnded()) {
    showMenu(player, locations, enemies, abilities, items, dialogNodes, dialogChoices, renderer, game, scenes, resourceSystem);
  }
  if (!game.getIsGameEnded()) {
    game.endGame(scenes, dialogNodes, dialogChoices, renderer);
    resourceSystem.saveGame();
  }
  return 0;
}