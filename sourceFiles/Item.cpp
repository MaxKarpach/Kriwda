#include "../headerFiles/Item.h" 
#include <iostream>

const int MAX_STRING_LEN = 20;

Item::Item(const int &id, const std::string &name, const char &type, const int &effectId, const int &factor)
:id(id), name(name), type(type), effectId(effectId), factor(factor) {}

ItemDef ItemRegistry::getItem(){
    return item;
}

void ItemRegistry::load(std::istream& is){
    ItemDef id;
    is >> id.id;
    char buf[MAX_STRING_LEN + 1] = {0};
    is.getline(buf, MAX_STRING_LEN);
    memset(buf, 0, sizeof(buf));
    is.getline(buf, MAX_STRING_LEN);
    id.name = buf;
    is >> id.type;
    is >> id.effectId;
    is >> id.factor;
    item = id;
}