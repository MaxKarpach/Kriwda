#include "../headerFiles/Item.h" 
#include <iostream>
#include <climits>

const int MAX_STRING_LEN = 100;

Item::Item(const ItemDef& def)
:id(def.id), name(def.name), type(def.type), factor(def.factor), description(def.description){}

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
        is >> id.factor;
        char buf2[MAX_STRING_LEN + 1] = {0};
        is.getline(buf2, MAX_STRING_LEN);
        memset(buf2, 0, sizeof(buf2));
        is.getline(buf2, MAX_STRING_LEN);
        id.description = buf2;
        items.push_back(id);
    }
}
void ItemRegistry::save(std::ostream& os){
    os << items.size() << std::endl;
    for (const ItemDef& id : items) {
        os << id.id << std::endl;
        os << id.name << std::endl;
        os << id.type << std::endl;
        os << id.factor << std::endl;
        os << id.description << std::endl;
    }
}
std::vector<ItemDef> ItemRegistry::toItemDefs(const std::vector<Item>& items) {
    std::vector<ItemDef> itemDefs;
    for (const auto& item : items) {
        ItemDef def;
        def.id = item.getId();
        def.name = item.getName();
        def.type = item.getType();
        def.factor = item.getFactor();
        def.description = item.getDescription();
        itemDefs.push_back(def);
    }
    return itemDefs;
}
void ItemRegistry::setItems(const std::vector<ItemDef>& defs) {
    items = defs;
}