#include "../headerFiles/Location.h" 
#include <iostream>

const int MAX_STRING_LEN = 20;

Location::Location(const int& id, const std::string& name, const std::vector<int> &choices, const std::vector<int>& enemies)
:id(id), name(name), choices(choices), enemies(enemies) {}

LocationDef LocationRegistry::getLocation(){
    return location;
}

void  LocationRegistry::load(std::istream& is){
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
    location = ld;
}