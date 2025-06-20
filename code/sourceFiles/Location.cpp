#include "../headerFiles/Location.h"
#include <iostream>

const int MAX_STRING_LEN = 255;

Location::Location(const LocationDef& def)
    : id_(def.id),
      name_(def.name),
      choices_(def.choices),
      enemy_id_(def.enemy_id),
      items_(def.items),
      dialog_node_id_(def.dialog_node_id),
      description_(def.description),
      is_final_boss_location_(def.is_final_boss_location),
      abilities_(def.abilities) {}

std::vector<LocationDef> LocationRegistry::get_locations() {
    return locations_;
}

void LocationRegistry::load(std::istream& is) {
    int locations_count = 0;
    is >> locations_count;

    for (int i = 0; i < locations_count; ++i) {
        LocationDef def;

        is >> def.id;
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, def.name);

        int choices_count = 0;
        is >> choices_count;
        for (int j = 0; j < choices_count; ++j) {
            int choice_id = 0;
            is >> choice_id;
            def.choices.push_back(choice_id);
        }

        is >> def.dialog_node_id;
        is >> def.enemy_id;

        int items_count = 0;
        is >> items_count;
        for (int j = 0; j < items_count; ++j) {
            int item_id = 0;
            is >> item_id;
            def.items.push_back(item_id);
        }

        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, def.description);

        is >> def.is_final_boss_location;

        int abilities_count = 0;
        is >> abilities_count;
        for (int j = 0; j < abilities_count; ++j) {
            int ability_id = 0;
            is >> ability_id;
            def.abilities.push_back(ability_id);
        }

        locations_.push_back(def);
    }
}

void LocationRegistry::save(std::ostream& os) {
    os << locations_.size() << std::endl;

    for (const LocationDef& def : locations_) {
        os << def.id << std::endl;
        os << def.name << std::endl;

        os << def.choices.size() << std::endl;
        for (int choice_id : def.choices) {
            os << choice_id << std::endl;
        }

        os << def.dialog_node_id << std::endl;
        os << def.enemy_id << std::endl;

        os << def.items.size() << std::endl;
        for (int item_id : def.items) {
            os << item_id << std::endl;
        }

        os << def.description << std::endl;
        os << def.is_final_boss_location << std::endl;

        os << def.abilities.size() << std::endl;
        for (int ability_id : def.abilities) {
            os << ability_id << std::endl;
        }
    }
}

std::vector<LocationDef> LocationRegistry::to_location_defs(const std::vector<Location>& locations) {
    std::vector<LocationDef> defs;

    for (const auto& location : locations) {
        LocationDef def;
        def.id = location.get_id();
        def.name = location.get_name();
        def.choices = location.get_choices();
        def.dialog_node_id = location.get_dialog_node_id();
        def.enemy_id = location.get_enemy_id();
        def.items = location.get_items();
        def.description = location.get_description();
        def.is_final_boss_location = location.is_final_boss_location();
        def.abilities = location.get_abilities();
        defs.push_back(def);
    }

    return defs;
}

void LocationRegistry::set_locations(const std::vector<LocationDef>& defs) {
    locations_ = defs;
}
