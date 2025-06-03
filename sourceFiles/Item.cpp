#include "../headerFiles/Item.h" 
#include <iostream>
#include <climits>

const int MAX_STRING_LEN = 255;

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
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, id.name);
        is >> id.type;
        is >> id.factor;
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, id.description);
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