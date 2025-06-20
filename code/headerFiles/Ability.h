#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>
#include <Renderer.h>

struct AbilityDef {
  int id;
  std::string name;
  char type;
  int factor;
  int moves_count;
  int max_moves_count;
  std::string description;
};

class Ability {
 public:
  Ability(const AbilityDef& def);

  std::string get_description() const { return description_; }
  void set_description(const std::string& value) { description_ = value; }

  int get_id() const { return id_; }
  void set_id(int value) { id_ = value; }

  std::string get_name() const { return name_; }
  void set_name(const std::string& value) { name_ = value; }

  char get_type() const { return type_; }
  void set_type(char value) { type_ = value; }

  int get_factor() const { return factor_; }
  void set_factor(int value) { factor_ = value; }

  int get_moves_count() const { return moves_count_; }
  void set_moves_count(int value) { moves_count_ = value; }

  int get_max_moves_count() const { return max_moves_count_; }
  void set_max_moves_count(int value) { max_moves_count_ = value; }

  void count_moves();
  void refresh_moves_count();

 private:
  int id_;
  std::string name_;
  char type_;
  int factor_;
  int moves_count_;
  int max_moves_count_;
  std::string description_;
};

class AbilityRegistry {
 public:
  void load(std::istream& is);
  std::vector<AbilityDef> get_abilities();
  void save(std::ostream& os);
  std::vector<AbilityDef> to_ability_defs(const std::vector<Ability>& abilities);
  void set_abilities(const std::vector<AbilityDef>& defs);

 private:
  std::vector<AbilityDef> abilities_;
};

#endif
