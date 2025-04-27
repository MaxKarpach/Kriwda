#include "../headerFiles/Effect.h" 
#include <iostream>

Effect::Effect(const int &id, const char &type)
:id(id), type(type) {}

EffectDef EffectRegistry::getEffect(){
    return effect;
}

void EffectRegistry::load(std::istream& is){
    EffectDef ed;
    is >> ed.id;
    is >> ed.type;
    effect = ed;
}