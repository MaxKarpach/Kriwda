#include <iostream>
#ifndef ABILITY_H
#define ABILITY_H
struct AbilityDef{
    int id;
    std::string name;
    char type;
    int effectId;
    int factor;
};

class Ability {
public:
    Ability(const AbilityDef& def);

    int getId() const { return id; }
    void setId(int value) { id = value; }

    std::string getName() const { return name; }
    void setName(std::string value) { name = value; }

    char getType() const { return type; }
    void setType(char value) { type = value; }

    int getEffect() const { return effectId; }
    void setEffect(int value) { id = effectId; }

    int getFactor() const { return factor; }
    void setFactor(int value) { factor = value; }

private:
int id;
std::string name;
char type;
int effectId;
int factor;
};


class AbilityRegistry{
    public:
    void load(std::istream& is);
    AbilityDef getAbility();
private:
    AbilityDef ability;
};
#endif