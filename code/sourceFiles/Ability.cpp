#include "Ability.h"

const int MAX_STRING_LEN = 255;

Ability::Ability(const AbilityDef& def)
    : id_(def.id),
      name_(def.name),
      type_(def.type),
      factor_(def.factor),
      moves_count_(def.moves_count),
      max_moves_count_(def.max_moves_count),
      description_(def.description) {}

void Ability::count_moves() {
  if (max_moves_count_ != moves_count_) {
    Renderer renderer;
    renderer.print_text("До возможности использовать способность ");
    renderer.print_text(name_);
    renderer.print_text(" осталось ");
    renderer.print_text(moves_count_ + 2);
    renderer.print_endline_text(" хода(ов)");
  }
}

void Ability::refresh_moves_count() {
  if (max_moves_count_ != moves_count_) {
    if (moves_count_ == -1) {
      moves_count_ = max_moves_count_;
    } else {
      moves_count_--;
    }
  }
}

std::vector<AbilityDef> AbilityRegistry::get_abilities() {
  return abilities_;
}

void AbilityRegistry::load(std::istream& is) {
  int abilities_count = 0;
  is >> abilities_count;
  for (int i = 0; i < abilities_count; i++) {
    AbilityDef def;
    is >> def.id;
    is.ignore(MAX_STRING_LEN, '\n');
    std::getline(is, def.name);
    is >> def.type;
    is >> def.factor;
    is >> def.moves_count;
    is >> def.max_moves_count;
    is.ignore(MAX_STRING_LEN, '\n');
    std::getline(is, def.description);

    abilities_.push_back(def);
  }
}

std::vector<AbilityDef> AbilityRegistry::to_ability_defs(const std::vector<Ability>& abilities) {
  std::vector<AbilityDef> ability_defs;
  for (const auto& ability : abilities) {
    AbilityDef def;
    def.id = ability.get_id();
    def.name = ability.get_name();
    def.type = ability.get_type();
    def.factor = ability.get_factor();
    def.moves_count = ability.get_moves_count();
    def.max_moves_count = ability.get_max_moves_count();
    def.description = ability.get_description();
    ability_defs.push_back(def);
  }
  return ability_defs;
}

void AbilityRegistry::save(std::ostream& os) {
  os << abilities_.size() << std::endl;
  for (const AbilityDef& def : abilities_) {
    os << def.id << std::endl;
    os << def.name << std::endl;
    os << def.type << std::endl;
    os << def.factor << std::endl;
    os << def.moves_count << std::endl;
    os << def.max_moves_count << std::endl;
    os << def.description << std::endl;
  }
}

void AbilityRegistry::set_abilities(const std::vector<AbilityDef>& defs) {
  abilities_ = defs;
}
