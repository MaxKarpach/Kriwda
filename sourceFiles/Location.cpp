#include "../headerFiles/Location.h" 
#include <iostream>

const int MAX_STRING_LEN = 20;

Location::Location(const LocationDef& def)
:id(def.id), name(def.name), choices(def.choices), enemies(def.enemies) {}

std::vector<LocationDef> LocationRegistry::getLocations(){
    return locations;
}

void  LocationRegistry::load(std::istream& is){
    int locationsCount = 0;
    is >> locationsCount;
    for (int i = 0; i < locationsCount; i++){
        LocationDef ld;
    is >> ld.id;
    char buf[MAX_STRING_LEN + 1] = {0};
    is.getline(buf, MAX_STRING_LEN);
    memset(buf, 0, sizeof(buf));
    is.getline(buf, MAX_STRING_LEN);
    ld.name = buf;
    int choicesCount = 0;
    is >> choicesCount;
    for (int i = 0; i < choicesCount;i++){
        int locationId = 0;
        is >> locationId;
        ld.choices.push_back(locationId);
    }
    int enemiesCount = 0;
    is >> enemiesCount;
    for (int i = 0; i < enemiesCount;i++){
        int enemyId = 0;
        is >> enemyId;
        ld.enemies.push_back(enemyId);
    }
    locations.push_back(ld);
    }
}