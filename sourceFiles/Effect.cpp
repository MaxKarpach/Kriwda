#include "../headerFiles/Effect.h" 
#include <iostream>

Effect::Effect(const EffectDef& def)
:id(def.id), type(def.type) {}

std::vector<EffectDef> EffectRegistry::getEffects(){
    return effects;
}

void EffectRegistry::load(std::istream& is){
    int effectsCount = 0;
    is >> effectsCount;
    for (int i = 0; i < effectsCount; i++){
    EffectDef ed;
    is >> ed.id;
    is >> ed.type;
    effects.push_back(ed);
    }
}