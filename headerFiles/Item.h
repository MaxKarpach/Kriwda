#include <iostream>
#ifndef ITEM_H
#define ITEM_H
struct ItemDef{
    int id;
    std::string name;
    char type;
    int effectId;
    int factor;
};

class Item {
public:
    Item(const int &id, const std::string &name, const char &type, const int &effectId, const int &factor);

    int getId() const { return id; }
    void setId(int value) { id = value; }

    std::string getName() const { return name; }
    void setName(std::string value) { name = value; }

    char getType() const { return type; }
    void setType(char value) { type = value; }

    int getEffect() const { return effectId; }
    void setEffect(int value) { id = effectId; }

    int getFactor() const { return factor; }
    void setFactor(int value) { factor = value; }

private:
int id;
std::string name;
char type;
int effectId;
int factor;
};


class ItemRegistry{
    public:
    void load(std::istream& is);
    ItemDef getItem();
private:
    ItemDef item;
};
#endif