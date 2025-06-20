#ifndef DIALOG_CHOICE_H
#define DIALOG_CHOICE_H

#include <iostream>
#include <vector>
#include <string>

struct DialogChoiceDef {
  int id;
  std::string text;
  int next_node_id;
  bool is_used;
};

class DialogChoice {
 public:
  DialogChoice(const DialogChoiceDef& def);

  int get_id() const { return id_; }
  void set_id(int value) { id_ = value; }

  std::string get_text() const { return text_; }
  void set_text(const std::string& value) { text_ = value; }

  int get_next_node_id() const { return next_node_id_; }
  void set_next_node_id(int value) { next_node_id_ = value; }

  bool get_is_used() const { return is_used_; }
  void set_is_used(bool value) { is_used_ = value; }

 private:
  int id_;
  std::string text_;
  int next_node_id_;
  bool is_used_;
};

class DialogChoiceRegistry {
 public:
  void load(std::istream& is);
  std::vector<DialogChoiceDef> get_dialog_choices();
  void save(std::ostream& os);
  std::vector<DialogChoiceDef> to_dialog_choice_defs(const std::vector<DialogChoice>& dialog_choices);
  void set_dialog_choices(const std::vector<DialogChoiceDef>& defs);

 private:
  std::vector<DialogChoiceDef> dialog_choices_;
};

#endif
