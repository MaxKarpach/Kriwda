#include "AbilitiesSystem.h"

AbilitiesSystem::AbilitiesSystem(Player& player,
                                 std::vector<Ability>& abilities,
                                 Renderer& renderer)
    : player_(player), abilities_(abilities), renderer_(renderer) {}

template <typename T>
T* AbilitiesSystem::find_by_id(int id, std::vector<T>& vec) {
  for (auto& obj : vec) {
    if (obj.get_id() == id) {
      return &obj;
    }
  }
  return nullptr;
}

void AbilitiesSystem::change_abilities() {
  int input_ability_index = -1;
  int replace_index = -1;

  while (true) {
    renderer_.print_endline_text("Все способности:");
    for (int i = 0; i < player_.get_abilities().size(); ++i) {
      Ability* ability =
          find_by_id<Ability>(player_.get_abilities()[i], abilities_);
      if (ability != nullptr) {
        renderer_.print_text(i + 1);
        renderer_.print_text(": ");
        renderer_.print_endline_text(ability->get_name());
      }
    }

    renderer_.print_endline_text("Выбранные способности:");
    for (int i = 0; i < player_.get_abilities_count(); ++i) {
      Ability* ability =
          find_by_id<Ability>(player_.get_chosen_abilities()[i], abilities_);
      if (ability != nullptr) {
        renderer_.print_text(i + 1);
        renderer_.print_text(": ");
        renderer_.print_endline_text(ability->get_name());
      }
    }

    renderer_.print_endline_text("0: Выход");
    std::cin >> input_ability_index;

    if (input_ability_index == 0) {
      break;
    }

    if (input_ability_index < 1 ||
        input_ability_index > player_.get_abilities().size()) {
      renderer_.print_endline_text("Некорректный ввод. Попробуйте снова.");
      continue;
    }

    int selected_ability_id = player_.get_abilities()[input_ability_index - 1];

    bool already_chosen = false;
    for (int i = 0; i < player_.get_abilities_count(); ++i) {
      if (player_.get_chosen_abilities()[i] == selected_ability_id) {
        already_chosen = true;
        break;
      }
    }

    if (already_chosen) {
      renderer_.print_endline_text(
          "Эта способность уже выбрана. Выберите другую.");
      continue;
    }

    renderer_.print_endline_text(
        "Введите номер выбранной способности, которую хотите заменить: ");
    std::cin >> replace_index;

    if (replace_index < 1 || replace_index > player_.get_abilities_count()) {
      renderer_.print_endline_text("Некорректный выбор замены.");
      continue;
    }

    player_.get_chosen_abilities()[replace_index - 1] = selected_ability_id;
    renderer_.print_endline_text("Способность заменена!");
  }
}
