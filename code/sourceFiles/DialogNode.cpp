#include "../headerFiles/DialogNode.h"
#include <iostream>

const int MAX_STRING_LEN = 255;

DialogNode::DialogNode(const DialogNodeDef& def)
    : id_(def.id),
      name_(def.name),
      text_(def.text),
      choices_(def.choices),
      description_(def.description) {}

std::vector<DialogNodeDef> DialogNodeRegistry::get_dialog_nodes() {
  return dialog_nodes_;
}

void DialogNodeRegistry::load(std::istream& is) {
  int dialog_nodes_count = 0;
  is >> dialog_nodes_count;

  for (int i = 0; i < dialog_nodes_count; ++i) {
    DialogNodeDef def;
    is >> def.id;
    is.ignore(MAX_STRING_LEN, '\n');
    std::getline(is, def.name);
    std::getline(is, def.text);

    int choices_count = 0;
    is >> choices_count;
    for (int j = 0; j < choices_count; ++j) {
      int choice_id;
      is >> choice_id;
      def.choices.push_back(choice_id);
    }

    is.ignore(MAX_STRING_LEN, '\n');
    std::getline(is, def.description);

    dialog_nodes_.push_back(def);
  }
}

void DialogNodeRegistry::save(std::ostream& os) {
  os << dialog_nodes_.size() << std::endl;

  for (const DialogNodeDef& def : dialog_nodes_) {
    os << def.id << std::endl;
    os << def.name << std::endl;
    os << def.text << std::endl;
    os << def.choices.size() << std::endl;

    for (int choice_id : def.choices) {
      os << choice_id << std::endl;
    }

    os << def.description << std::endl;
  }
}

std::vector<DialogNodeDef> DialogNodeRegistry::to_dialog_node_defs(const std::vector<DialogNode>& dialog_nodes) {
  std::vector<DialogNodeDef> defs;
  for (const auto& node : dialog_nodes) {
    DialogNodeDef def;
    def.id = node.get_id();
    def.name = node.get_name();
    def.text = node.get_text();
    def.choices = node.get_choices();
    def.description = node.get_description();
    defs.push_back(def);
  }
  return defs;
}

void DialogNodeRegistry::set_dialog_nodes(const std::vector<DialogNodeDef>& defs) {
  dialog_nodes_ = defs;
}
