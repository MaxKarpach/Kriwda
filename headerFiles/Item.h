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

    int getId() const { return id; }
    void setId(int value) { id = value; }

    std::string getName() const { return name; }
    void setName(std::string value) { name = value; }

    char getType() const { return type; }
    void setType(char value) { type = value; }

    int getFactor() const { return factor; }
    void setFactor(int value) { factor = value; }

    std::string getDescription() const { return description; }
    void setDescription(std::string value) { description = value; }

private:
int id;
std::string name;
char type;
int factor;
std::string description;
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