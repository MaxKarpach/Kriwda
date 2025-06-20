#include "LocationSystem.h"

LocationSystem::LocationSystem(Player& player, std::vector<Location>& locations, int& enemiesCount, 
    Renderer& renderer): player_(player), locations_(locations), enemiesCount_(enemiesCount),
    renderer_(renderer){}

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
