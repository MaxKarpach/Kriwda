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

template <typename T>
T* find_by_id(int id, std::vector<T>& vec) {
  for (auto& obj : vec) {
    if (obj.get_id() == id) {
      return &obj;
    }
  }
  return nullptr;
}

void fight(Player& player, int enemy_id, std::vector<Enemy>& enemies,
           std::vector<Ability>& abilities, Location* current_location,
           Renderer& renderer) {
  Enemy* enemy = find_by_id<Enemy>(enemy_id, enemies);
  std::vector<Ability*> player_abilities;
  std::vector<Ability*> enemy_abilities;

  for (int i = 0; i < player.get_abilities_count(); i++) {
    player_abilities.push_back(find_by_id<Ability>(player.get_chosen_abilities()[i], abilities));
    enemy_abilities.push_back(find_by_id<Ability>(enemy->get_abilities()[i], abilities));
  }

  BattleSystem battle_system(player, enemy, renderer, current_location,
                             player_abilities, enemy_abilities);
  battle_system.battle();
}

void show_menu(Player& player, std::vector<Location>& locations,
               std::vector<Enemy>& enemies, std::vector<Ability>& abilities,
               std::vector<Item>& items, std::vector<DialogNode>& dialog_nodes,
               std::vector<DialogChoice>& dialog_choices, Renderer& renderer,
               Game& game, std::vector<Scene>& scenes,
               ResourceSystem& resource_system) {
  int user_choice = 0;

  while (player.get_enemies_count() != enemies.size()) {
    Location* current_location = find_by_id<Location>(player.get_location_id(), locations);
    int enemy_id = current_location->get_enemy_id();
    int dialog_node_id = current_location->get_dialog_node_id();
    std::vector<int>& location_items = current_location->get_items_ref();
    std::vector<int>& location_abilities = current_location->get_abilities_ref();

    renderer.print_endline_text(current_location->get_description());

    std::vector<std::string> options = {
      "Сменить локацию",
      "Показать инвентарь",
      "Выбрать способности",
      "Показать описания"
    };

    if (player.get_chosen_weapon_id() != 0)
      options.push_back("Показать оружие");

    if (enemy_id != 0) {
      options.push_back("Вступить в бой");
      renderer.print_text("На локации присутствует враг ");
      renderer.print_endline_text(find_by_id<Enemy>(enemy_id, enemies)->get_name());
    }

    if (dialog_node_id != 0)
      options.push_back("Поговорить");

    if (!location_items.empty())
      options.push_back("Осмотреть предметы на локации");

    if (!location_abilities.empty())
      options.push_back("Осмотреть способности на локации");

    for (int i = 0; i < options.size(); i++) {
      renderer.print_text(i + 1);
      renderer.print_text(": ");
      renderer.print_endline_text(options[i]);
    }

    std::cin >> user_choice;

    if (user_choice < 1 || user_choice > options.size()) {
      renderer.print_endline_text("Неверный ввод. Попробуйте снова.");
      continue;
    }

    std::string selected_option = options[user_choice - 1];
    int enemies_count = enemies.size();

    if (selected_option == "Сменить локацию") {
      LocationSystem location_system(player, locations, enemies_count, renderer,
                                     abilities, items, current_location);
      location_system.move();
      resource_system.save_game();
    } else if (selected_option == "Показать инвентарь") {
      InventorySystem inventory_system(player, items, renderer);
      inventory_system.show_inventory();
      resource_system.save_game();
    } else if (selected_option == "Выбрать способности") {
      AbilitiesSystem abilities_system(player, abilities, renderer);
      abilities_system.change_abilities();
      resource_system.save_game();
    } else if (selected_option == "Вступить в бой") {
      fight(player, enemy_id, enemies, abilities, current_location, renderer);
      resource_system.save_game();
    } else if (selected_option == "Осмотреть предметы на локации") {
      LocationSystem location_system(player, locations, enemies_count, renderer,
                                     abilities, items, current_location);
      location_system.loot_items();
      resource_system.save_game();
    } else if (selected_option == "Осмотреть способности на локации") {
      LocationSystem location_system(player, locations, enemies_count, renderer,
                                     abilities, items, current_location);
      location_system.loot_abilities();
      resource_system.save_game();
    } else if (selected_option == "Поговорить") {
      DialogSystem dialog_system(dialog_nodes, dialog_choices, dialog_node_id,
                                 current_location, renderer);
      dialog_system.start_dialog();
      resource_system.save_game();
    } else if (selected_option == "Показать оружие") {
      InventorySystem inventory_system(player, items, renderer);
      inventory_system.show_chosen_weapon();
    } else if (selected_option == "Показать описания") {
      InfoSystem info_system(player, enemies, abilities, items, renderer);
      info_system.show_descriptions();
    }
  }

  game.set_is_game_loop_ended(1);
  resource_system.save_game();
}

void run(Player& player,
         std::vector<Location>& locations,
         std::vector<Enemy>& enemies,
         std::vector<Ability>& abilities,
         std::vector<Item>& items,
         std::vector<DialogNode>& dialog_nodes,
         std::vector<DialogChoice>& dialog_choices,
         std::vector<Scene>& scenes,
         Game& game,
         ResourceSystem& resource_system,
         Renderer& renderer) {
  if (!game.get_is_game_started()) {
    game.init_new_game(scenes, dialog_nodes, dialog_choices, renderer);
    resource_system.save_game();
  }

  if (!game.get_is_game_loop_ended()) {
    show_menu(player, locations, enemies, abilities, items, dialog_nodes,
              dialog_choices, renderer, game, scenes, resource_system);
  }

  if (!game.get_is_game_ended()) {
    game.end_game(scenes, dialog_nodes, dialog_choices, renderer);
    resource_system.save_game();
  }
}

int main(int argc, char* argv[]) {
  std::string file_name = "data.txt";
  Player player;
  std::vector<Location> locations;
  std::vector<Enemy> enemies;
  std::vector<Ability> abilities;
  std::vector<Item> items;
  std::vector<DialogNode> dialog_nodes;
  std::vector<DialogChoice> dialog_choices;
  std::vector<Scene> scenes;
  Renderer renderer;
  Game game(scenes, dialog_nodes, dialog_choices, renderer);

  ResourceSystem resource_system(player, locations, enemies, abilities, items,
                                 dialog_nodes, dialog_choices, scenes, game, file_name);

  resource_system.download_data();

  run(player, locations, enemies, abilities, items, dialog_nodes,
      dialog_choices, scenes, game, resource_system, renderer);

  return 0;
}
