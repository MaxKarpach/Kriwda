#ifndef ENEMY_H
#define ENEMY_H

#include <Renderer.h>

struct EnemyDef {
  int id;
  std::string name;
  int hp;
  int damage;
  int stamina;
  int shield;
  int dodge_count;
  std::array<int, 3> abilities;
  int location_id;
  bool is_shield_on;
  bool is_dodge_on;
  int stamina_factor;
  int shield_factor;
  int max_dodge_count;
  int max_stamina;
  int max_shield;
  int stamina_recovery_factor;
  std::vector<int> items;
  std::string description;
  int abilities_count;
};

class Enemy {
 public:
  Enemy(const EnemyDef& def);

  int get_id() const { return id_; }
  void set_id(int value) { id_ = value; }

  std::array<int, 3> get_abilities() const { return abilities_; }

  std::string get_name() const { return name_; }
  void set_name(std::string value) { name_ = value; }

  std::string get_description() const { return description_; }
  void set_description(std::string value) { description_ = value; }

  int get_hp() const { return hp_; }
  void set_hp(int value) { hp_ = value; }

  int get_damage() const { return damage_; }
  void set_damage(int value) { damage_ = value; }

  bool get_is_shield_on() const { return is_shield_on_; }
  void set_is_shield_on(bool value) { is_shield_on_ = value; }

  bool get_is_dodge_on() const { return is_dodge_on_; }
  void set_is_dodge_on(bool value) { is_dodge_on_ = value; }

  int get_stamina() const { return stamina_; }
  void set_stamina(int value) { stamina_ = value; }

  int get_stamina_factor() const { return stamina_factor_; }
  void set_stamina_factor(int value) { stamina_factor_ = value; }

  int get_shield_factor() const { return shield_factor_; }
  void set_shield_factor(int value) { shield_factor_ = value; }

  int get_shield() const { return shield_; }
  void set_shield(int value) { shield_ = value; }

  int get_dodge_count() const { return dodge_count_; }
  void set_dodge_count(int value) { dodge_count_ = value; }

  int get_stamina_recovery_factor() const { return stamina_recovery_factor_; }
  void set_stamina_recovery_factor(int value) { stamina_recovery_factor_ = value; }

  int get_location_id() const { return location_id_; }
  void set_location_id(int value) { location_id_ = value; }

  void show_abilities() {
    for (int i = 0; i < abilities_.size(); i++) {
      Renderer renderer;
      renderer.print_endline_text(abilities_[i]);
    }
  }

  void add_ability(int ability_id, int ability_index) {
    if ((abilities_.size() - 1) >= ability_index) {
      abilities_[ability_index] = ability_id;
    }
  }

  void remove_ability(int ability_index) {
    abilities_[ability_index] = 0;
  }

  std::array<int, 3> get_abilities() { return abilities_; }

  int get_max_stamina() const { return max_stamina_; }
  void set_max_stamina(int value) { max_stamina_ = value; }

  int get_max_shield() const { return max_shield_; }
  void set_max_shield(int value) { max_shield_ = value; }

  int get_abilities_count() const { return abilities_count_; }
  void set_abilities_count(int value) { abilities_count_ = value; }

  int get_max_dodge_count() const { return max_dodge_count_; }
  void set_max_dodge_count(int value) { max_dodge_count_ = value; }

  std::vector<int> get_items() const { return items_; }
  void set_items(const std::vector<int>& value) { items_ = value; }

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
        dodge_count_++;
      }
    }
  }

  void after_round_info() {
    Renderer renderer;
    renderer.print_text("Здоровье врага: ");
    renderer.print_endline_text(hp_);
  }

  void win_round(int& enemy_hp) {
    hp_ = enemy_hp;
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
  std::string name_;
  int id_;
  int hp_;
  int damage_;
  int stamina_;
  int shield_;
  int dodge_count_;
  std::array<int, 3> abilities_;
  int location_id_;
  bool is_shield_on_;
  bool is_dodge_on_;
  int stamina_factor_;
  int shield_factor_;
  int max_dodge_count_;
  int max_stamina_;
  int max_shield_;
  int stamina_recovery_factor_;
  std::vector<int> items_;
  std::string description_;
  int abilities_count_;
};

class EnemyRegistry {
 public:
  void load(std::istream& is);
  std::vector<EnemyDef> get_enemies();
  void save(std::ostream& os);
  std::vector<EnemyDef> to_enemy_defs(const std::vector<Enemy>& enemies);
  void set_enemies(const std::vector<EnemyDef>& defs);

 private:
  std::vector<EnemyDef> enemies;
};

#endif
