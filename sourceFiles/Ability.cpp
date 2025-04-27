#include "../headerFiles/Ability.h" 
#include <iostream>

const int MAX_STRING_LEN = 20;

Ability::Ability(const int &id, const std::string &name, const char &type, const int &effectId, const int &factor)
:id(id), name(name), type(type), effectId(effectId), factor(factor) {}

AbilityDef AbilityRegistry::getAbility(){
    return ability;
}

void AbilityRegistry::load(std::istream& is){
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
    ability = ad;
}