#include "../headerFiles/Item.h" 
#include <iostream>
#include <climits>

const int MAX_STRING_LEN = 100;

Item::Item(const ItemDef& def)
:id(def.id), name(def.name), type(def.type), effectId(def.effectId), factor(def.factor), description(def.description){}

std::vector<ItemDef> ItemRegistry::getItems(){
    return items;
}

void ItemRegistry::load(std::istream& is){
    int itemsCount = 0;
    is >> itemsCount;
    for (int i = 0; i < itemsCount;i++){
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
        char buf2[MAX_STRING_LEN + 1] = {0};
        is.getline(buf2, MAX_STRING_LEN);
        memset(buf2, 0, sizeof(buf2));
        is.getline(buf2, MAX_STRING_LEN);
        id.description = buf2;
        items.push_back(id);
    }
}