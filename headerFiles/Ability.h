#include <iostream>
#ifndef ABILITY_H
#define ABILITY_H
struct AbilityDef{
    int id;
    std::string name;
    char type;
    int effectId;
    int factor;
    int movesCount;
    int maxMovesCount;
    std::string description;
};

class Ability {
public:
    Ability(const AbilityDef& def);

    std::string getDescription() const { return description; }
    void setDescription(std::string value) { description = value; }

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

    int getMovesCount() const { return movesCount; }
    void setMovesCount(int value){movesCount = value;}

    int getMaxMovesCount() const { return maxMovesCount; }
    void setMaxMovesCount(int value){maxMovesCount = value;}

    private: 
    int id;
    std::string name;
    char type;
    int effectId;
    int factor;
    int movesCount;
    int maxMovesCount;
    std::string description;
};

class AbilityRegistry{
    public:
    void load(std::istream& is);
    std::vector<AbilityDef> getAbilities();
private:
    std::vector<AbilityDef> abilities;
};
#endif