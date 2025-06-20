#include "LocationSystem.h"

LocationSystem::LocationSystem(Player& player,
                               std::vector<Location>& locations,
                               int& enemies_count,
                               Renderer& renderer,
                               std::vector<Ability>& abilities,
                               std::vector<Item>& items,
                               Location* current_location)
    : player_(player),
      locations_(locations),
      enemies_count_(enemies_count),
      renderer_(renderer),
      abilities_(abilities),
      items_(items),
      current_location_(current_location) {}

template <typename T>
T* LocationSystem::find_by_id(int id, std::vector<T>& vec) {
  for (auto& obj : vec) {
    if (obj.get_id() == id) {
      return &obj;
    }
  }
  return nullptr;
}

void LocationSystem::move() {
  while (true) {
    Location* current_location = find_by_id<Location>(player_.get_location_id(), locations_);
    renderer_.print_text("Ваше текущее местоположение: ");
    renderer_.print_endline_text(current_location->get_name());

    renderer_.print_endline_text("Вы можете пойти в следующие места: ");
    std::vector<Location*> nearly_locations;
    int final_boss_location_num = 0;

    for (int i = 0; i < current_location->get_choices().size(); ++i) {
      Location* nearly_location = find_by_id<Location>(current_location->get_choices()[i], locations_);
      if (nearly_location) {
        nearly_locations.push_back(nearly_location);
        renderer_.print_text(i + 1);
        renderer_.print_text(": ");
        if (nearly_location->is_final_boss_location() &&
            player_.get_enemies_count() != (enemies_count_ - 1)) {
          renderer_.print_text(nearly_location->get_name());
          renderer_.print_endline_text(" (вы еще не готовы)");
          final_boss_location_num = i + 1;
        } else {
          renderer_.print_endline_text(nearly_location->get_name());
        }
      }
    }

    renderer_.print_text(current_location->get_choices().size() + 1);
    renderer_.print_endline_text(": Остановиться на локации");

    int user_choice = 0;
    std::cin >> user_choice;

    if (user_choice == current_location->get_choices().size() + 1) {
      return;
    } else if (user_choice > 0 && user_choice <= current_location->get_choices().size()) {
      if (final_boss_location_num == user_choice &&
          player_.get_enemies_count() != (enemies_count_ - 1)) {
        return;
      } else {
        player_.set_location_id(nearly_locations[user_choice - 1]->get_id());
      }
    } else {
      renderer_.print_endline_text("Такого варианта нет");
    }
  }
}

void LocationSystem::loot_abilities() {
  std::vector<int>& location_abilities = current_location_->get_abilities_ref();
  std::vector<int>& player_abilities = player_.get_abilities();

  while (!location_abilities.empty()) {
    renderer_.print_endline_text("Способности на локации:");
    renderer_.print_endline_text("0: Выйти");

    for (int i = 0; i < location_abilities.size(); ++i) {
      Ability* ability = find_by_id<Ability>(location_abilities[i], abilities_);
      if (ability) {
        renderer_.print_text(i + 1);
        renderer_.print_text(": ");
        renderer_.print_endline_text(ability->get_name());
      }
    }

    int choice = -1;
    renderer_.print_endline_text("Выберите предмет для подбора: ");
    std::cin >> choice;

    if (choice == 0) {
      break;
    } else if (choice > 0 && choice <= location_abilities.size()) {
      int ability_id = location_abilities[choice - 1];
      player_abilities.push_back(ability_id);
      location_abilities.erase(location_abilities.begin() + (choice - 1));
      renderer_.print_endline_text("Способность подобрана!");
    } else {
      renderer_.print_endline_text("Неверный выбор, попробуйте снова.");
    }
  }

  if (location_abilities.empty()) {
    renderer_.print_endline_text("На локации больше нет способностей.");
  }
}

void LocationSystem::loot_items() {
  std::vector<int>& location_items = current_location_->get_items_ref();
  std::vector<int>& player_inventory = player_.get_inventory();

  while (!location_items.empty()) {
    renderer_.print_endline_text("Предметы на локации:");
    renderer_.print_endline_text("0: Выйти");

    for (int i = 0; i < location_items.size(); ++i) {
      Item* item = find_by_id<Item>(location_items[i], items_);
      if (item) {
        renderer_.print_text(i + 1);
        renderer_.print_text(": ");
        renderer_.print_endline_text(item->get_name());
      }
    }

    int choice = -1;
    renderer_.print_endline_text("Выберите предмет для подбора: ");
    std::cin >> choice;

    if (choice == 0) {
      break;
    } else if (choice > 0 && choice <= location_items.size()) {
      int item_id = location_items[choice - 1];
      player_inventory.push_back(item_id);
      location_items.erase(location_items.begin() + (choice - 1));
      renderer_.print_endline_text("Предмет подобран!");
    } else {
      renderer_.print_endline_text("Неверный выбор, попробуйте снова.");
    }
  }

  if (location_items.empty()) {
    renderer_.print_endline_text("На локации больше нет предметов.");
  }
}
