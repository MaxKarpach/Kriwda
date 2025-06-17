#include <iostream>

#ifndef DIALOGNODE_H
#define DIALOGNODE_H

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

  int getId() const { return id_; }
  void setId(int value) { id_ = value; }

  std::string getText() const { return text_; }
  void setText(std::string value) { text_ = value; }

  std::string getDescription() const { return description_; }
  void setDescription(std::string value) { description_ = value; }

  std::string getName() const { return name_; }
  void setName(std::string value) { name_ = value; }

  void addChoice(const int& choiceId) {
    choices_.push_back(choiceId);
  }

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

  std::vector<int> getChoices() const { return choices_; }

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
  std::vector<DialogNodeDef> getDialogNodes();
  void save(std::ostream& os);
  std::vector<DialogNodeDef> toDialogNodeDefs(const std::vector<DialogNode>& dialogNodes);
  void setDialogNodes(const std::vector<DialogNodeDef>& defs);

 private:
  std::vector<DialogNodeDef> dialogNodes;
};

#endif  
