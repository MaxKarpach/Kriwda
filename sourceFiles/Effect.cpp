#include "../headerFiles/Effect.h" 
#include <iostream>

Effect::Effect(const EffectDef& def)
:id(def.id), type(def.type) {}

EffectDef EffectRegistry::getEffect(){
    return effect;
}

void EffectRegistry::load(std::istream& is){
    EffectDef ed;
    is >> ed.id;
    is >> ed.type;
    effect = ed;
}