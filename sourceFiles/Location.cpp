#include "../headerFiles/Location.h" 
#include <iostream>

const int MAX_STRING_LEN = 255;

Location::Location(const LocationDef& def)
:id_(def.id), name_(def.name), choices_(def.choices), enemyId_(def.enemyId), items_(def.items), 
dialogNodeId_(def.dialogNodeId), description_(def.description), isFinalBossLocation_(def.isFinalBossLocation), 
abilities_(def.abilities){}

std::vector<LocationDef> LocationRegistry::getLocations(){
    return locations;
}

void  LocationRegistry::load(std::istream& is){
    int locationsCount = 0;
    is >> locationsCount;
    for (int i = 0; i < locationsCount; i++){
        LocationDef ld;
    is >> ld.id;
    is.ignore(MAX_STRING_LEN, '\n');
    std::getline(is, ld.name);
    int choicesCount = 0;
    is >> choicesCount;
    for (int i = 0; i < choicesCount;i++){
        int locationId = 0;
        is >> locationId;
        ld.choices.push_back(locationId);
    }
    is >> ld.dialogNodeId;
    is >> ld.enemyId;
    int itemsCount = 0;
    is >> itemsCount;
    for (int i = 0; i < itemsCount; i++){
        int itemId = 0;
        is >> itemId;
        ld.items.push_back(itemId);
    }
    is.ignore(MAX_STRING_LEN, '\n');
    std::getline(is, ld.description);
    is >> ld.isFinalBossLocation;
    int abilitiesCount = 0;
    is >> abilitiesCount;
    for (int i = 0; i < abilitiesCount; i++){
        int abilityId = 0;
        is >> abilityId;
        ld.abilities.push_back(abilityId);
    }
    locations.push_back(ld);
    }
}

void LocationRegistry::save(std::ostream& os) {
    os << locations.size() << std::endl;
    for (const LocationDef& ld : locations) {
        os << ld.id << std::endl;
        os << ld.name << std::endl;

        os << ld.choices.size() << std::endl;
        for (int choiceId : ld.choices) {
            os << choiceId << std::endl;
        }

        os << ld.dialogNodeId << std::endl;
        os << ld.enemyId<< std::endl;

        os << ld.items.size() << std::endl;
        for (int itemId : ld.items) {
            os << itemId << std::endl;
        }

        os << ld.description << std::endl;
        os << ld.isFinalBossLocation << std::endl;
        os << ld.abilities.size() << std::endl;
        for (int abilityId : ld.abilities){
            os << abilityId << std::endl;
        }
    }
}
std::vector<LocationDef> LocationRegistry::toLocationDefs(const std::vector<Location>& locations) {
    std::vector<LocationDef> locationDefs;
    for (const auto& location : locations) {
        LocationDef def;
        def.id = location.getId();
        def.name = location.getName();
        def.choices = location.getChoices();
        def.dialogNodeId = location.getDialogNodeId();
        def.enemyId = location.getEnemyId();
        def.items = location.getItems();
        def.description = location.getDescription();
        def.isFinalBossLocation = location.getIsFinalBossLocation();
        def.abilities = location.getAbilities();
        locationDefs.push_back(def);
    }
    return locationDefs;
}
void LocationRegistry::setLocations(const std::vector<LocationDef>& defs) {
    locations = defs;
}