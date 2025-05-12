#include "../headerFiles/Location.h" 
#include <iostream>

const int MAX_STRING_LEN = 100;

Location::Location(const LocationDef& def)
:id(def.id), name(def.name), choices(def.choices), enemyId(def.enemyId), items(def.items), dialogNodeId(def.dialogNodeId),
description(def.description){}

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
    is >> ld.dialogNodeId;
    is >> ld.enemyId;
    int itemsCount = 0;
    is >> itemsCount;
    for (int i = 0; i < itemsCount; i++){
        int itemId = 0;
        is >> itemId;
        ld.items.push_back(itemId);
    }
    char buf2[MAX_STRING_LEN + 1] = {0};
    is.getline(buf2, MAX_STRING_LEN);
    memset(buf2, 0, sizeof(buf2));
    is.getline(buf2, MAX_STRING_LEN);
    ld.description = buf2;
    locations.push_back(ld);
    }
}