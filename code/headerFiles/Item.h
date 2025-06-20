#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <vector>
#include <string>

struct ItemDef {
  int id;
  std::string name;
  char type;
  int factor;
  std::string description;
};

class Item {
 public:
  Item(const ItemDef& def);

  int get_id() const { return id_; }
  void set_id(int value) { id_ = value; }

  std::string get_name() const { return name_; }
  void set_name(const std::string& value) { name_ = value; }

  char get_type() const { return type_; }
  void set_type(char value) { type_ = value; }

  int get_factor() const { return factor_; }
  void set_factor(int value) { factor_ = value; }

  std::string get_description() const { return description_; }
  void set_description(const std::string& value) { description_ = value; }

 private:
  int id_;
  std::string name_;
  char type_;
  int factor_;
  std::string description_;
};

class ItemRegistry {
 public:
  void load(std::istream& is);
  std::vector<ItemDef> get_items();
  void save(std::ostream& os);
  std::vector<ItemDef> to_item_defs(const std::vector<Item>& items);
  void set_items(const std::vector<ItemDef>& defs);

 private:
  std::vector<ItemDef> items_;
};

#endif
