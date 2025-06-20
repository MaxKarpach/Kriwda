#include "../headerFiles/DialogChoice.h"
#include <iostream>

const int MAX_STRING_LEN = 255;

DialogChoice::DialogChoice(const DialogChoiceDef& def)
    : id_(def.id),
      text_(def.text),
      next_node_id_(def.next_node_id),
      is_used_(def.is_used) {}

std::vector<DialogChoiceDef> DialogChoiceRegistry::get_dialog_choices() {
  return dialog_choices_;
}

void DialogChoiceRegistry::load(std::istream& is) {
  int dialog_choices_count = 0;
  is >> dialog_choices_count;
  for (int i = 0; i < dialog_choices_count; ++i) {
    DialogChoiceDef def;
    is >> def.id;
    is.ignore(MAX_STRING_LEN, '\n');
    std::getline(is, def.text);
    is >> def.next_node_id;
    is >> def.is_used;
    dialog_choices_.push_back(def);
  }
}

void DialogChoiceRegistry::save(std::ostream& os) {
  os << dialog_choices_.size() << std::endl;
  for (const DialogChoiceDef& def : dialog_choices_) {
    os << def.id << std::endl;
    os << def.text << std::endl;
    os << def.next_node_id << std::endl;
    os << def.is_used << std::endl;
  }
}

std::vector<DialogChoiceDef> DialogChoiceRegistry::to_dialog_choice_defs(const std::vector<DialogChoice>& dialog_choices) {
  std::vector<DialogChoiceDef> defs;
  for (const auto& choice : dialog_choices) {
    DialogChoiceDef def;
    def.id = choice.get_id();
    def.text = choice.get_text();
    def.next_node_id = choice.get_next_node_id();
    def.is_used = choice.get_is_used();
    defs.push_back(def);
  }
  return defs;
}

void DialogChoiceRegistry::set_dialog_choices(const std::vector<DialogChoiceDef>& defs) {
  dialog_choices_ = defs;
}

