#include "../headerFiles/Ability.h" 
#include <iostream>

const int MAX_STRING_LEN = 100;

Ability::Ability(const AbilityDef& def)
:id(def.id), name(def.name), type(def.type), factor(def.factor),
movesCount(def.movesCount),maxMovesCount(def.maxMovesCount), description(def.description)  {}

std::vector<AbilityDef> AbilityRegistry::getAbilities(){
    return abilities;
}

void AbilityRegistry::load(std::istream& is){
    int abilitiesCount = 0;
    is >> abilitiesCount;
    for (int i = 0; i < abilitiesCount; i++){
        AbilityDef ad;
    is >> ad.id;
    char buf[MAX_STRING_LEN + 1] = {0};
    is.getline(buf, MAX_STRING_LEN);
    memset(buf, 0, sizeof(buf));
    is.getline(buf, MAX_STRING_LEN);
    ad.name = buf;
    is >> ad.type;
    is >> ad.factor;
    is >> ad.movesCount;
    is >> ad.maxMovesCount;
    char buf2[MAX_STRING_LEN + 1] = {0};
    is.getline(buf2, MAX_STRING_LEN);
    memset(buf2, 0, sizeof(buf2));
    is.getline(buf2, MAX_STRING_LEN);
    ad.description = buf2;
    abilities.push_back(ad);
    }
}

void AbilityRegistry::save(std::ostream& os){
    os << abilities.size() << std::endl;
    for (const AbilityDef& ad : abilities) {
        os << ad.id << std::endl;
        os << ad.name << std::endl;
        os << ad.type << std::endl;
        os << ad.factor << std::endl;
        os << ad.movesCount << std::endl;
        os << ad.maxMovesCount << std::endl;
        os << ad.description << std::endl;
    }
}