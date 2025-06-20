#include "InventorySystem.h"

InventorySystem::InventorySystem(Player& player, std::vector<Item>& items, Renderer& renderer):
    player_(player), items_(items), renderer_(renderer){}

template<typename T> T* InventorySystem::findById(int id, std::vector<T>& vec) {
  for (auto& obj : vec) {
    if (obj.getId() == id) {
      return &obj;
    }
  }
  return nullptr;
}

void InventorySystem::showInventory() {
  std::vector<int> &inventory = player_.getInventory();
  while (true) {
    renderer_.printEndlineText("Ваш инвентарь:");

    if (inventory.empty()) {
      renderer_.printEndlineText("Инвентарь пуст.");
      return;
    }
    renderer_.printEndlineText("0: Выход");

    for (int i = 0; i < inventory.size(); i++) {
      Item* item = findById<Item>(inventory[i], items_);
      if (item != nullptr) {
        renderer_.printText(i + 1);
        renderer_.printText(": ");
        renderer_.printEndlineText(item->getName());
      }
    }
    int input;
    std::cin >> input;

    if (input == 0) break;

    if (input < 1 || input > inventory.size()) {
      renderer_.printEndlineText("Неверный выбор. Попробуйте снова.");
      continue;
    }

    int itemId = inventory[input - 1];
    Item* item = findById<Item>(itemId, items_);

    if (!item) {
      renderer_.printEndlineText("Ошибка: предмет не найден.");
      continue;
    }

    char type = item->getType();
    switch (type) {
      case 'f':
        player_.setHp(player_.getHp() + item->getFactor());
        renderer_.printText("Вы выбрали еду: ");
        renderer_.printEndlineText(item->getName());
        renderer_.printText("У вас теперь ");
        renderer_.printText(player_.getHp());
        renderer_.printEndlineText(" здоровья.");
        break;
      case 'w':
        player_.setChosenWeaponId(item->getId());
        renderer_.printText("Вы выбрали оружие: ");
        renderer_.printEndlineText(item->getName());
        player_.setDamage(item->getFactor());
        break;
      case 'n':
        renderer_.printText("Вы выбрали прочитать: ");
        renderer_.printEndlineText(item->getName());
        renderer_.printEndlineText(item->getDescription());
        break;
      case 's':
        player_.setShield(item->getFactor());
        renderer_.printText("Вы выбрали щит: ");
        renderer_.printEndlineText(item->getName());
        renderer_.printText("Ваш уровень защиты: ");
        renderer_.printEndlineText(player_.getShield());
        break;
      default:
        renderer_.printEndlineText("Предмет не может быть использован.");
        continue;
    }

    if (type == 'f') {
      inventory.erase(inventory.begin() + (input - 1));
    }
  }
}

void InventorySystem::showChosenWeapon() {
  Item* item = findById<Item>(player_.getChosenWeaponId(), items_);
  if (item != nullptr) {
    renderer_.printText("Вы используете оружие: ");
    renderer_.printEndlineText(item->getName());
    renderer_.printEndlineText(item->getDescription());
  }
}