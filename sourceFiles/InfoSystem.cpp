#include <InfoSystem.h>

InfoSystem::InfoSystem(Player& player, std::vector<Enemy>& enemies,
    std::vector<Ability>& abilities, std::vector<Item>& items,
    Renderer& renderer):
    player_(player), enemies_(enemies),  abilities_(abilities),
    items_(items), renderer_(renderer){}

template<typename T>
T* InfoSystem::findById(int id, std::vector<T>& vec) {
  for (auto& obj : vec) {
    if (obj.getId() == id) {
      return &obj;
    }
  }
  return nullptr;
}

void InfoSystem::showDescriptions() {
  int userChoice = 0;
  while (true) {
    std::vector<std::string> options;
    options.push_back("Показать описания способностей");
    options.push_back("Показать описания предметов");
    options.push_back("Показать описания побеждённых врагов");
    renderer_.printEndlineText("Введите 0 для выхода");
    for (int i = 0; i < options.size(); i++) {
      renderer_.printText(i + 1);
      renderer_.printText(": ");
      renderer_.printEndlineText(options[i]);
    }
    std::cin >> userChoice;

    if (userChoice < 0 || userChoice > options.size()) {
      renderer_.printEndlineText("Неверный ввод. Попробуйте снова.");
      continue;
    }

    if (userChoice == 0) {
      break;
    }

    std::string selectedOption = options[userChoice - 1];
    if (selectedOption == "Показать описания способностей") {
      showDataDescription<Ability>(player_.getAbilities(), abilities_, renderer_, "Ваши способности");
      break;
    } else if (selectedOption == "Показать описания предметов") {
      showDataDescription<Item>(player_.getInventory(), items_, renderer_, "Ваши инвентарь");
      break;
    } else if (selectedOption == "Показать описания побеждённых врагов") {
      showDataDescription<Enemy>(player_.getEnemies(), enemies_, renderer_, "Ваши враги");
      break;
    }
  }
}

template <typename T>
void InfoSystem::showDataDescription(std::vector<int>& playerData, std::vector<T>& data,
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