#include <iostream>
#ifndef LOCATION_H
#define LOCATION_H

#include <Renderer.h>

struct LocationDef {
  int id;
  std::string name;
  std::vector<int> choices;
  int enemyId;
  int dialogNodeId;
  std::vector<int> items;
  std::string description;
  bool isFinalBossLocation;
  std::vector<int> abilities;
};

class Location {
 public:
  Location(const LocationDef& def);

  int getId() const { return id_; }
  void setId(int value) { id_ = value; }

  int getDialogNodeId() const { return dialogNodeId_; }
  void setDialogNodeId(int value) { dialogNodeId_ = value; }

  std::vector<int> getItems() const { return items_; }
  std::vector<int> getChoices() const { return choices_; }
  std::vector<int> getAbilities() const { return abilities_; }

  std::string getName() const { return name_; }
  void setName(std::string value) { name_ = value; }

  int getEnemyId() const { return enemyId_; }
  void setEnemyId(int value) { enemyId_ = value; }

  void addChoice(const int& choiceId) { choices_.push_back(choiceId); }

  void showChoices() {
    for (int i = 0; i < choices_.size(); i++) {
      Renderer renderer;
      renderer.printEndlineText(choices_[i]);
    }
  }

  void removeChoice(int choiceId) {
    auto it = std::find(choices_.begin(), choices_.end(), choiceId);
    if (it != choices_.end()) {
      choices_.erase(it);
    }
  }

  void setItems(std::vector<int> newItems) {
    for (int item : newItems) {
      items_.push_back(item);
    }
  }

  std::vector<int>& getItems() { return items_; }
  std::vector<int>& getAbilities() { return abilities_; }

  std::string getDescription() const { return description_; }
  void setDescription(std::string value) { description_ = value; }

  bool getIsFinalBossLocation() const { return isFinalBossLocation_; }

 private:
  int id_;
  std::string name_;
  std::vector<int> choices_;
  int enemyId_;
  int dialogNodeId_;
  std::vector<int> items_;
  std::string description_;
  bool isFinalBossLocation_;
  std::vector<int> abilities_;
};

class LocationRegistry {
 public:
  void load(std::istream& is);
  std::vector<LocationDef> getLocations();
  std::vector<LocationDef> toLocationDefs(const std::vector<Location>& locations);
  void save(std::ostream& os);
  void setLocations(const std::vector<LocationDef>& defs);

 private:
  std::vector<LocationDef> locations;
};

#endif  
