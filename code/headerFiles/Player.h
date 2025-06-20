#ifndef PLAYER_H
#define PLAYER_H

#include <Renderer.h>

struct PlayerDef {
  int hp;
  int damage;
  int stamina;
  int shield;
  int dodge_count;
  int location_id;
  std::vector<int> inventory;
  std::vector<int> abilities;
  std::array<int, 3> chosen_abilities;
  int chosen_weapon_id;
  bool is_shield_on;
  bool is_dodge_on;
  int stamina_factor;
  int shield_factor;
  int max_dodge_count;
  int max_stamina;
  int max_shield;
  int stamina_recovery_factor;
  std::vector<int> enemies;
  int abilities_count;
};

class Player {
 public:
  Player(const PlayerDef& def);
  Player();

  int get_hp() const { return hp_; }
  void set_hp(int value) { hp_ = value; }

  int get_damage() const { return damage_; }
  void set_damage(int value) { damage_ = value; }

  int get_stamina() const { return stamina_; }
  void set_stamina(int value) { stamina_ = value; }

  int get_max_stamina() const { return max_stamina_; }
  void set_max_stamina(int value) { max_stamina_ = value; }

  int get_max_shield() const { return max_shield_; }
  void set_max_shield(int value) { max_shield_ = value; }

  int get_stamina_factor() const { return stamina_factor_; }
  void set_stamina_factor(int value) { stamina_factor_ = value; }

  int get_stamina_recovery_factor() const { return stamina_recovery_factor_; }
  void set_stamina_recovery_factor(int value) { stamina_recovery_factor_ = value; }

  std::vector<int>& get_inventory() { return inventory_; }
  void set_inventory(std::vector<int> value) { inventory_ = value; }

  int get_shield() const { return shield_; }
  void set_shield(int value) { shield_ = value; }

  int get_abilities_count() const { return abilities_count_; }
  void set_abilities_count(int value) { abilities_count_ = value; }

  int get_shield_factor() const { return shield_factor_; }
  void set_shield_factor(int value) { shield_factor_ = value; }

  bool get_is_shield_on() const { return is_shield_on_; }
  void set_is_shield_on(bool value) { is_shield_on_ = value; }

  bool get_is_dodge_on() const { return is_dodge_on_; }
  void set_is_dodge_on(bool value) { is_dodge_on_ = value; }

  int get_dodge_count() const { return dodge_count_; }
  void set_dodge_count(int value) { dodge_count_ = value; }

  int get_max_dodge_count() const { return max_dodge_count_; }
  void set_max_dodge_count(int value) { max_dodge_count_ = value; }

  int get_location_id() const { return location_id_; }
  void set_location_id(int value) { location_id_ = value; }

  int get_chosen_weapon_id() const { return chosen_weapon_id_; }
  void set_chosen_weapon_id(int value) { chosen_weapon_id_ = value; }

  std::vector<int>& get_abilities() { return abilities_; }
  std::vector<int>& get_enemies() { return enemies_; }
  std::array<int, 3>& get_chosen_abilities() { return chosen_abilities_; }

  int get_enemies_count() { return enemies_.size(); }

  void show_inventory() {
    for (int i = 0; i < inventory_.size(); i++) {
      Renderer renderer;
      renderer.print_endline_text(inventory_[i]);
    }
  }

  void add_item_to_inventory(int item_id) { inventory_.push_back(item_id); }

  void remove_item_from_inventory(int item_id) {
    auto it = std::find(inventory_.begin(), inventory_.end(), item_id);
    if (it != inventory_.end()) {
      inventory_.erase(it);
    }
  }

  void show_abilities() {
    for (int i = 0; i < abilities_.size(); i++) {
      Renderer renderer;
      renderer.print_endline_text(abilities_[i]);
    }
  }

  void add_ability(int ability_id) { abilities_.push_back(ability_id); }

  void remove_ability(int ability_id) {
    auto it = std::find(abilities_.begin(), abilities_.end(), ability_id);
    if (it != abilities_.end()) {
      abilities_.erase(it);
    }
  }

  void show_chosen_abilities() {
    for (int i = 0; i < chosen_abilities_.size(); i++) {
      Renderer renderer;
      renderer.print_endline_text(chosen_abilities_[i]);
    }
  }

  void add_chosen_ability(int ability_id, int chosen_ability_index) {
    if ((chosen_abilities_.size() - 1) >= chosen_ability_index) {
      chosen_abilities_[chosen_ability_index] = ability_id;
    }
  }

  void remove_chosen_ability(int chosen_ability_index) {
    chosen_abilities_[chosen_ability_index] = 0;
  }

  void add_to_enemies(int enemy_id) { enemies_.push_back(enemy_id); }

  void update_dodge_state() {
    if (is_dodge_on_) {
      if (dodge_count_ >= max_dodge_count_) {
        is_dodge_on_ = false;
        dodge_count_ = 0;
      } else {
        dodge_count_++;
      }
    }
  }

  void init_dodge_count() {
    if (is_dodge_on_) {
      if (dodge_count_ == max_dodge_count_) {
        is_dodge_on_ = false;
        dodge_count_ = 0;
      } else {
        Renderer renderer;
        renderer.print_text("До уклонения осталось: ");
        renderer.print_text(max_dodge_count_ - dodge_count_);
        renderer.print_endline_text(" хода(/ов)");
        dodge_count_++;
      }
    }
  }

  void after_round_info() {
    Renderer renderer;
    renderer.print_text("Здоровье игрока: ");
    renderer.print_endline_text(hp_);
    renderer.print_text("Щит игрока: ");
    renderer.print_endline_text(shield_);
    renderer.print_text("Выносливость игрока: ");
    renderer.print_endline_text(stamina_);
  }

  void lose_round(int& player_hp) {
    hp_ = player_hp;
    stamina_ = max_stamina_;
    shield_ = max_shield_;
    dodge_count_ = 0;
    is_dodge_on_ = 0;
    is_shield_on_ = 0;
  }

  void win_round(const int& enemy_id, const int& player_hp) {
    add_to_enemies(enemy_id);
    hp_ = player_hp;
    stamina_ = max_stamina_;
    shield_ = max_shield_;
    dodge_count_ = 0;
    is_dodge_on_ = 0;
    is_shield_on_ = 0;
  }

  void refresh_stats_after_round() {
    if (shield_ < 0) {
      shield_ = 0;
    }
    is_shield_on_ = 0;
    if (stamina_ + stamina_factor_ < max_stamina_) {
      stamina_ = stamina_ + stamina_recovery_factor_;
    }
    if (shield_ + shield_factor_ < max_shield_) {
      shield_ = shield_ + shield_factor_;
    }
  }

 private:
  int hp_;
  int damage_;
  int stamina_;
  int shield_;
  int dodge_count_;
  int location_id_;
  std::vector<int> inventory_;
  std::vector<int> abilities_;
  std::array<int, 3> chosen_abilities_;
  int chosen_weapon_id_;
  bool is_shield_on_;
  bool is_dodge_on_;
  int stamina_factor_;
  int shield_factor_;
  int max_dodge_count_;
  int max_stamina_;
  int max_shield_;
  int stamina_recovery_factor_;
  std::vector<int> enemies_;
  int abilities_count_;
};

class PlayerRegistry {
 public:
  void load(std::istream& is);
  PlayerDef get_player();
  void save(std::ostream& os);
  PlayerDef to_player_def(Player& player);
  void set_player(const PlayerDef& def);

 private:
  PlayerDef player;
};

#endif
