#include "../headerFiles/Ability.h" 
#include <iostream>

const int MAX_STRING_LEN = 60;

Ability::Ability(const AbilityDef& def)
:id(def.id), name(def.name), type(def.type), effectId(def.effectId), factor(def.factor),
movesCount(def.movesCount) {}

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
    is >> ad.effectId;
    is >> ad.factor;
    is >> ad.movesCount;
    abilities.push_back(ad);
    }
}