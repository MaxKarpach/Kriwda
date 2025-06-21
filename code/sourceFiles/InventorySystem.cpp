#include "InventorySystem.h"

InventorySystem::InventorySystem(Player& player,
                                 std::vector<Item>& items,
                                 Renderer& renderer)
    : player_(player), items_(items), renderer_(renderer) {}

template <typename T>
T* InventorySystem::find_by_id(int id, std::vector<T>& vec) {
  for (auto& obj : vec) {
    if (obj.get_id() == id) {
      return &obj;
    }
  }
  return nullptr;
}

void InventorySystem::item_effect(char& type, Item* item, int& input, std::vector<int>& inventory){
      switch (type) {
      case 'f':
        player_.set_hp(player_.get_hp() + item->get_factor());
        renderer_.print_text("Вы выбрали еду: ");
        renderer_.print_endline_text(item->get_name());
        renderer_.print_text("У вас теперь ");
        renderer_.print_text(player_.get_hp());
        renderer_.print_endline_text(" здоровья.");
        break;

      case 'w':
        player_.set_chosen_weapon_id(item->get_id());
        renderer_.print_text("Вы выбрали оружие: ");
        renderer_.print_endline_text(item->get_name());
        player_.set_damage(item->get_factor());
        break;

      case 'n':
        renderer_.print_text("Вы выбрали прочитать: ");
        renderer_.print_endline_text(item->get_name());
        renderer_.print_endline_text(item->get_description());
        break;

      case 's':
        player_.set_shield(item->get_factor());
        renderer_.print_text("Вы выбрали щит: ");
        renderer_.print_endline_text(item->get_name());
        renderer_.print_text("Ваш уровень защиты: ");
        renderer_.print_endline_text(player_.get_shield());
        break;

      default:
        renderer_.print_endline_text("Предмет не может быть использован.");
    }

    if (type == 'f') {
      inventory.erase(inventory.begin() + (input - 1));
    }
}

void InventorySystem::show_inventory() {
  std::vector<int>& inventory = player_.get_inventory();

  while (true) {
    renderer_.print_endline_text("Ваш инвентарь:");

    if (inventory.empty()) {
      renderer_.print_endline_text("Инвентарь пуст.");
      return;
    }

    renderer_.print_endline_text("0: Выход");

    for (int i = 0; i < inventory.size(); ++i) {
      Item* item = find_by_id<Item>(inventory[i], items_);
      if (item != nullptr) {
        renderer_.print_text(i + 1);
        renderer_.print_text(": ");
        renderer_.print_endline_text(item->get_name());
      }
    }

    int input;
    std::cin >> input;

    if (input == 0) {
      break;
    }

    if (input < 1 || input > inventory.size()) {
      renderer_.print_endline_text("Неверный выбор. Попробуйте снова.");
      continue;
    }

    int item_id = inventory[input - 1];
    Item* item = find_by_id<Item>(item_id, items_);

    if (!item) {
      renderer_.print_endline_text("Ошибка: предмет не найден.");
      continue;
    }

    char type = item->get_type();

    item_effect(type, item, input, inventory);
  }
}

void InventorySystem::show_chosen_weapon() {
  Item* item = find_by_id<Item>(player_.get_chosen_weapon_id(), items_);
  if (item != nullptr) {
    renderer_.print_text("Вы используете оружие: ");
    renderer_.print_endline_text(item->get_name());
    renderer_.print_endline_text(item->get_description());
  }
}

