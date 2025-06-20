#ifndef LOCATION_H
#define LOCATION_H

#include <Renderer.h>
#include <vector>
#include <string>
#include <algorithm>

struct LocationDef {
  int id;
  std::string name;
  std::vector<int> choices;
  int enemy_id;
  int dialog_node_id;
  std::vector<int> items;
  std::string description;
  bool is_final_boss_location;
  std::vector<int> abilities;
};

class Location {
 public:
  Location(const LocationDef& def);

  int get_id() const { return id_; }
  void set_id(int value) { id_ = value; }

  int get_dialog_node_id() const { return dialog_node_id_; }
  void set_dialog_node_id(int value) { dialog_node_id_ = value; }

  std::vector<int> get_items() const { return items_; }
  std::vector<int> get_choices() const { return choices_; }
  std::vector<int> get_abilities() const { return abilities_; }

  std::string get_name() const { return name_; }
  void set_name(const std::string& value) { name_ = value; }

  int get_enemy_id() const { return enemy_id_; }
  void set_enemy_id(int value) { enemy_id_ = value; }

  void add_choice(int choice_id) { choices_.push_back(choice_id); }

  void show_choices() {
    Renderer renderer;
    for (int choice : choices_) {
      renderer.print_endline_text(choice);
    }
  }

  void remove_choice(int choice_id) {
    auto it = std::find(choices_.begin(), choices_.end(), choice_id);
    if (it != choices_.end()) {
      choices_.erase(it);
    }
  }

  void set_items(const std::vector<int>& new_items) {
    for (int item : new_items) {
      items_.push_back(item);
    }
  }

  std::vector<int>& get_items_ref() { return items_; }
  std::vector<int>& get_abilities_ref() { return abilities_; }

  std::string get_description() const { return description_; }
  void set_description(const std::string& value) { description_ = value; }

  bool is_final_boss_location() const { return is_final_boss_location_; }

 private:
  int id_;
  std::string name_;
  std::vector<int> choices_;
  int enemy_id_;
  int dialog_node_id_;
  std::vector<int> items_;
  std::string description_;
  bool is_final_boss_location_;
  std::vector<int> abilities_;
};

class LocationRegistry {
 public:
  void load(std::istream& is);
  std::vector<LocationDef> get_locations();
  std::vector<LocationDef> to_location_defs(const std::vector<Location>& locations);
  void save(std::ostream& os);
  void set_locations(const std::vector<LocationDef>& defs);

 private:
  std::vector<LocationDef> locations_;
};

#endif
