#include "LocationSystem.h"

LocationSystem::LocationSystem(Player& player, std::vector<Location>& locations, int& enemiesCount, 
    Renderer& renderer, std::vector<Ability>& abilities, std::vector<Item>& items, Location* currentLocation):
    player_(player), locations_(locations), enemiesCount_(enemiesCount),
    renderer_(renderer), abilities_(abilities), items_(items), currentLocation_(currentLocation){}

template<typename T> T* LocationSystem::findById(int id, std::vector<T>& vec) {
  for (auto& obj : vec) {
    if (obj.getId() == id) {
      return &obj;
    }
  }
  return nullptr;
}

void LocationSystem::move() {
  while (true) {
    Location *currentLocation = findById<Location>(player_.getLocationId(), locations_);
    renderer_.printText("Ваше текущее местоположение: ");
    renderer_.printEndlineText(currentLocation->getName());
    renderer_.printEndlineText("Вы можете пойти в следующие места: ");
    std::vector<Location*> nearlyLocations;
    int finalBossLocationNum = 0;
    for (int i = 0; i < currentLocation->getChoices().size(); i++) {
      Location* nearlyLocation = findById<Location>(currentLocation->getChoices()[i], locations_);
      if (nearlyLocation) {
        nearlyLocations.push_back(nearlyLocation);
        if (nearlyLocation->getIsFinalBossLocation() && player_.getEnemiesCount() != (enemiesCount_ - 1)) {
          renderer_.printText(i + 1);
          renderer_.printText(": ");
          renderer_.printText(nearlyLocation->getName());
          renderer_.printEndlineText("(вы еще не готовы)");
          finalBossLocationNum = i + 1;
        } else {
          renderer_.printText(i + 1);
          renderer_.printText(": ");
          renderer_.printEndlineText(nearlyLocation->getName());
        }
      }
    }
    renderer_.printText(currentLocation->getChoices().size() + 1);
    renderer_.printEndlineText(": Остановиться на локации");
    int userChoice = 0;
    std::cin >> userChoice;
    if (userChoice == currentLocation->getChoices().size()+1) {
      return;
    } else if (userChoice <= currentLocation->getChoices().size() && userChoice > 0) {
      if (finalBossLocationNum == userChoice && player_.getEnemiesCount() != (enemiesCount_ - 1)) {
        return;
      } else {
        player_.setLocationId(nearlyLocations[userChoice - 1]->getId());
      }
    } else {
      renderer_.printEndlineText("Такого варианта нет");
    }
  }
}

void LocationSystem::lootAbilities(){
            std::vector<int> &locationAbilities = currentLocation_->getAbilities();
            std::vector<int> &playerAbilities = player_.getAbilities();
            while (!locationAbilities.empty())
            {
                renderer_.printEndlineText("Способности на локации:");
                renderer_.printEndlineText("0: Выйти");
                for (int i = 0; i < locationAbilities.size(); ++i)
                {
                    Ability *ability = findById<Ability>(locationAbilities[i], abilities_);
                    if (ability){
                        renderer_.printText(i + 1);
                        renderer_.printText(": ");
                        renderer_.printEndlineText(ability->getName());
                    }
                }

                int choice = -1;
                renderer_.printEndlineText("Выберите предмет для подбора: ");
                std::cin >> choice;

                if (choice == 0)
                {
                    break;
                }
                  if (choice > 0 && choice <= locationAbilities.size()){
                    int itemId = locationAbilities[choice - 1];
                    playerAbilities.push_back(itemId);
                    locationAbilities.erase(locationAbilities.begin() + (choice - 1));
                    renderer_.printEndlineText("Предмет подобран!");
                }
                else
                {
                    renderer_.printEndlineText("Неверный выбор, попробуйте снова.");
                }
            }

            if (locationAbilities.empty())
            {
                renderer_.printEndlineText("На локации больше нет предметов.");
            }
}

void LocationSystem::lootItems(){
            std::vector<int> &locationItems = currentLocation_->getItems();
            std::vector<int> &playerInventory = player_.getInventory();
            while (!locationItems.empty())
            {
                renderer_.printEndlineText("Предметы на локации:");
                renderer_.printEndlineText("0: Выйти");
                for (int i = 0; i < locationItems.size(); ++i)
                {
                    Item *item = findById<Item>(locationItems[i], items_);
                    if (item){
                        renderer_.printText(i + 1);
                        renderer_.printText(": ");
                        renderer_.printEndlineText(item->getName());
                    }
                }

                int choice = -1;
                renderer_.printEndlineText("Выберите предмет для подбора: ");
                std::cin >> choice;

                if (choice == 0)
                {
                    break;
                }
                  if (choice > 0 && choice <= locationItems.size()){
                    int itemId = locationItems[choice - 1];
                    playerInventory.push_back(itemId);
                    locationItems.erase(locationItems.begin() + (choice - 1));
                    renderer_.printEndlineText("Предмет подобран!");
                }
                else
                {
                    renderer_.printEndlineText("Неверный выбор, попробуйте снова.");
                }
            }

            if (locationItems.empty())
            {
                renderer_.printEndlineText("На локации больше нет предметов.");
            }
}