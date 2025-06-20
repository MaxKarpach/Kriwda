#include <InfoSystem.h>

InfoSystem::InfoSystem(Player& player,
                       std::vector<Enemy>& enemies,
                       std::vector<Ability>& abilities,
                       std::vector<Item>& items,
                       Renderer& renderer)
    : player_(player),
      enemies_(enemies),
      abilities_(abilities),
      items_(items),
      renderer_(renderer) {}

template <typename T>
T* InfoSystem::find_by_id(int id, std::vector<T>& vec) {
  for (auto& obj : vec) {
    if (obj.get_id() == id) {
      return &obj;
    }
  }
  return nullptr;
}

void InfoSystem::show_descriptions() {
  int user_choice = 0;
  while (true) {
    std::vector<std::string> options;
    options.push_back("Показать описания способностей");
    options.push_back("Показать описания предметов");
    options.push_back("Показать описания побеждённых врагов");

    renderer_.print_endline_text("Введите 0 для выхода");
    for (int i = 0; i < options.size(); ++i) {
      renderer_.print_text(i + 1);
      renderer_.print_text(": ");
      renderer_.print_endline_text(options[i]);
    }

    std::cin >> user_choice;

    if (user_choice < 0 || user_choice > options.size()) {
      renderer_.print_endline_text("Неверный ввод. Попробуйте снова.");
      continue;
    }

    if (user_choice == 0) {
      break;
    }

    std::string selected_option = options[user_choice - 1];

    if (selected_option == "Показать описания способностей") {
      show_data_description<Ability>(player_.get_abilities(), abilities_,
                                     renderer_, "Ваши способности");
      break;
    } else if (selected_option == "Показать описания предметов") {
      show_data_description<Item>(player_.get_inventory(), items_,
                                  renderer_, "Ваш инвентарь");
      break;
    } else if (selected_option == "Показать описания побеждённых врагов") {
      show_data_description<Enemy>(player_.get_enemies(), enemies_,
                                   renderer_, "Ваши враги");
      break;
    }
  }
}

template <typename T>
void InfoSystem::show_data_description(std::vector<int>& player_data,
                                       std::vector<T>& data,
                                       Renderer& renderer,
                                       const std::string& description) {
  while (true) {
    renderer.print_text(description);
    renderer.print_endline_text(
        " Введите номер предмета для просмотра описания (0 для выхода):");

    for (int i = 0; i < player_data.size(); ++i) {
      const T* subject = find_by_id<T>(player_data[i], data);
      if (subject != nullptr) {
        renderer.print_text(i + 1);
        renderer.print_text(": ");
        renderer.print_endline_text(subject->get_name());
      }
    }

    int choice;
    std::cin >> choice;

    if (choice == 0) break;

    if (choice < 1 || choice > player_data.size()) {
      renderer.print_endline_text("Некорректный выбор. Попробуйте снова.");
      continue;
    }

    const T* selected = find_by_id<T>(player_data[choice - 1], data);
    if (selected) {
      renderer.print_text("Описание ");
      renderer.print_text(selected->get_name());
      renderer.print_endline_text(":");
      renderer.print_endline_text(selected->get_description());
    }
  }
}
