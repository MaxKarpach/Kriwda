#include <AbilitiesSystem.h>

AbilitiesSystem::AbilitiesSystem(Player& player,
                                 std::vector<Ability>& abilities,
                                 Renderer& renderer)
    : player_(player), abilities_(abilities), renderer_(renderer) {}

template <typename T>
T* AbilitiesSystem::findById(int id, std::vector<T>& vec) {
  for (auto& obj : vec) {
    if (obj.getId() == id) {
      return &obj;
    }
  }
  return nullptr;
}

void AbilitiesSystem::changeAbilities() {
  int inputAbilityIndex = -1;
  int replaceIndex = -1;

  while (true) {
    renderer_.printEndlineText("Все способности:");
    for (int i = 0; i < player_.getAbilities().size(); ++i) {
      Ability* ability =
          findById<Ability>(player_.getAbilities()[i], abilities_);
      if (ability != nullptr) {
        renderer_.printText(i + 1);
        renderer_.printText(": ");
        renderer_.printEndlineText(ability->getName());
      }
    }

    renderer_.printEndlineText("Выбранные способности:");
    for (int i = 0; i < player_.getAbilitiesCount(); ++i) {
      Ability* ability =
          findById<Ability>(player_.getChosenAbilities()[i], abilities_);
      if (ability != nullptr) {
        renderer_.printText(i + 1);
        renderer_.printText(": ");
        renderer_.printEndlineText(ability->getName());
      }
    }

    renderer_.printEndlineText("0: Выход");
    std::cin >> inputAbilityIndex;

    if (inputAbilityIndex == 0) break;

    if (inputAbilityIndex < 1 ||
        inputAbilityIndex > player_.getAbilities().size()) {
      renderer_.printEndlineText("Некорректный ввод. Попробуйте снова.");
      continue;
    }

    int selectedAbilityId = player_.getAbilities()[inputAbilityIndex - 1];

    bool alreadyChosen = false;
    for (int i = 0; i < player_.getAbilitiesCount(); ++i) {
      if (player_.getChosenAbilities()[i] == selectedAbilityId) {
        alreadyChosen = true;
        break;
      }
    }

    if (alreadyChosen) {
      renderer_.printEndlineText(
          "Эта способность уже выбрана. Выберите другую.");
      continue;
    }

    renderer_.printEndlineText(
        "Введите номер выбранной способности, которую хотите заменить: ");
    std::cin >> replaceIndex;

    if (replaceIndex < 1 || replaceIndex > player_.getAbilitiesCount()) {
      renderer_.printEndlineText("Некорректный выбор замены.");
      continue;
    }

    player_.getChosenAbilities()[replaceIndex - 1] = selectedAbilityId;
    renderer_.printEndlineText("Способность заменена!");
  }
}
