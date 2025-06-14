#include <iostream>
#ifndef ITEM_H
#define ITEM_H
struct ItemDef{
    int id;
    std::string name;
    char type;
    int factor;
    std::string description;
};

class Item {
public:
    Item(const ItemDef& def);

    int getId() const { return id_; }
    void setId(int value) { id_ = value; }

    std::string getName() const { return name_; }
    void setName(std::string value) { name_ = value; }

    char getType() const { return type_; }
    void setType(char value) { type_ = value; }

    int getFactor() const { return factor_; }
    void setFactor(int value) { factor_ = value; }

    std::string getDescription() const { return description_; }
    void setDescription(std::string value) { description_ = value; }

private:
int id_;
std::string name_;
char type_;
int factor_;
std::string description_;
};


class ItemRegistry{
    public:
    void load(std::istream& is);
    std::vector<ItemDef> getItems();
    void save(std::ostream &os);
    std::vector<ItemDef> toItemDefs(const std::vector<Item> &items);
    void setItems(const std::vector<ItemDef>& defs);
private:
    std::vector<ItemDef> items;
};
#endif