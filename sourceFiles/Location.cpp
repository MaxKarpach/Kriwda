#include "../headerFiles/Location.h" 
#include <iostream>

const int MAX_STRING_LEN = 20;

Location::Location(const int& id, const std::string& name, const std::vector<int> &choices)
:id(id), name(name), choices(choices) {}

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
    location = ld;
}