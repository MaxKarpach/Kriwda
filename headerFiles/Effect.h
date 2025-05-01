#include <iostream>
#ifndef EFFECT_H
#define EFFECT_H
struct EffectDef{
    int id;
    char type;
};

class Effect{
public:
    Effect(const EffectDef& def);

    int getId() const { return id; }
    void setId(int value) { id = value; }

    char getType() const { return type; }
    void setType(char value) { type = value; }

private:
int id;
char type;
};


class EffectRegistry{
    public:
    void load(std::istream& is);
    EffectDef getEffect();
private:
    EffectDef effect;
};
#endif