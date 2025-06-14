#include "../headerFiles/Ability.h" 
#include <iostream>

const int MAX_STRING_LEN = 255;

Ability::Ability(const AbilityDef& def)
:id_(def.id), name_(def.name), type_(def.type), factor_(def.factor),
movesCount_(def.movesCount),maxMovesCount_(def.maxMovesCount), description_(def.description)  {}

std::vector<AbilityDef> AbilityRegistry::getAbilities(){
    return abilities;
}

void AbilityRegistry::load(std::istream& is){
    int abilitiesCount = 0;
    is >> abilitiesCount;
    for (int i = 0; i < abilitiesCount; i++){
        AbilityDef ad;
        is >> ad.id;
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, ad.name);
        is >> ad.type;
        is >> ad.factor;
        is >> ad.movesCount;
        is >> ad.maxMovesCount;
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, ad.description);

        abilities.push_back(ad);
    }
}

std::vector<AbilityDef> AbilityRegistry::toAbilityDefs(const std::vector<Ability>& abilities) {
        std::vector<AbilityDef> abilityDefs;
        for (const auto& ability : abilities) {
            AbilityDef def;
            def.id = ability.getId();
            def.name = ability.getName();
            def.type = ability.getType();
            def.factor = ability.getFactor();
            def.movesCount = ability.getMovesCount();
            def.maxMovesCount = ability.getMaxMovesCount();
            def.description = ability.getDescription();
            abilityDefs.push_back(def);
        }
        return abilityDefs;
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
void AbilityRegistry::setAbilities(const std::vector<AbilityDef>& defs) {
    abilities = defs;
}