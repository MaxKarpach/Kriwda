#include "Item.h"

const int MAX_STRING_LEN = 255;

Item::Item(const ItemDef& def)
    : id_(def.id), name_(def.name), type_(def.type), factor_(def.factor), description_(def.description) {}

std::vector<ItemDef> ItemRegistry::get_items() {
    return items_;
}

void ItemRegistry::load(std::istream& is) {
    int items_count = 0;
    is >> items_count;
    for (int i = 0; i < items_count; ++i) {
        ItemDef def;
        is >> def.id;
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, def.name);
        is >> def.type;
        is >> def.factor;
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, def.description);
        items_.push_back(def);
    }
}

void ItemRegistry::save(std::ostream& os) {
    os << items_.size() << std::endl;
    for (const ItemDef& def : items_) {
        os << def.id << std::endl;
        os << def.name << std::endl;
        os << def.type << std::endl;
        os << def.factor << std::endl;
        os << def.description << std::endl;
    }
}

std::vector<ItemDef> ItemRegistry::to_item_defs(const std::vector<Item>& items) {
    std::vector<ItemDef> item_defs;
    for (const auto& item : items) {
        ItemDef def;
        def.id = item.get_id();
        def.name = item.get_name();
        def.type = item.get_type();
        def.factor = item.get_factor();
        def.description = item.get_description();
        item_defs.push_back(def);
    }
    return item_defs;
}

void ItemRegistry::set_items(const std::vector<ItemDef>& defs) {
    items_ = defs;
}
