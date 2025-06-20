#ifndef DIALOG_NODE_H
#define DIALOG_NODE_H

#include <iostream>
#include <vector>
#include <string>
#include <Renderer.h>

struct DialogNodeDef {
  int id;
  std::string name;
  std::string text;
  std::vector<int> choices;
  std::string description;
};

class DialogNode {
 public:
  DialogNode(const DialogNodeDef& def);

  int get_id() const { return id_; }
  void set_id(int value) { id_ = value; }

  std::string get_text() const { return text_; }
  void set_text(const std::string& value) { text_ = value; }

  std::string get_description() const { return description_; }
  void set_description(const std::string& value) { description_ = value; }

  std::string get_name() const { return name_; }
  void set_name(const std::string& value) { name_ = value; }

  void add_choice(const int& choice_id) {
    choices_.push_back(choice_id);
  }

  void show_choices() {
    for (int i = 0; i < choices_.size(); ++i) {
      Renderer renderer;
      renderer.print_endline_text(choices_[i]);
    }
  }

  void remove_choice(int choice_id) {
    auto it = std::find(choices_.begin(), choices_.end(), choice_id);
    if (it != choices_.end()) {
      choices_.erase(it);
    }
  }

  std::vector<int> get_choices() const { return choices_; }

 private:
  int id_;
  std::string name_;
  std::string text_;
  std::vector<int> choices_;
  std::string description_;
};

class DialogNodeRegistry {
 public:
  void load(std::istream& is);
  std::vector<DialogNodeDef> get_dialog_nodes();
  void save(std::ostream& os);
  std::vector<DialogNodeDef> to_dialog_node_defs(const std::vector<DialogNode>& dialog_nodes);
  void set_dialog_nodes(const std::vector<DialogNodeDef>& defs);

 private:
  std::vector<DialogNodeDef> dialog_nodes_;
};

#endif

