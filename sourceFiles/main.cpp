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
#include "../headerFiles/DialogSystem.h"
#include "../headerFiles/InfoSystem.h"

template<typename T> T* findById(int id, std::vector<T>& vec) {
  for (auto& obj : vec) {
    if (obj.getId() == id) {
      return &obj;
    }
  }
  return nullptr;
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
      DialogSystem dialogSystem(dialogNodes, dialogChoices, dialogNodeId, currentLocation, renderer);
      dialogSystem.startDialog();
      resourceSystem.saveGame();
    } else if (selectedOption == "Показать оружие") {
      InventorySystem inventorySystem(player, items, renderer);
      inventorySystem.showChosenWeapon();
    } else if (selectedOption == "Показать описания") {
      InfoSystem infoSystem(player, enemies, abilities, items, renderer);
      infoSystem.showDescriptions();
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