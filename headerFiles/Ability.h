#include <iostream>
#ifndef ABILITY_H
#define ABILITY_H
struct AbilityDef{
    int id;
    std::string name;
    char type;
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

    int getFactor() const { return factor; }
    void setFactor(int value) { factor = value; }

    int getMovesCount() const { return movesCount; }
    void setMovesCount(int value){movesCount = value;}

    int getMaxMovesCount() const { return maxMovesCount; }
    void setMaxMovesCount(int value){maxMovesCount = value;}

    void countMoves(){
        if (maxMovesCount != movesCount){
        std::cout << "До возможности использовать способность " << name << " осталось " << movesCount + 2 << " хода(ов)" << std::endl;
        }
    }

    void refreshMovesCount(){
        if (maxMovesCount != movesCount){
            if (movesCount == -1)
            {
                setMovesCount(maxMovesCount);
            }
            else
            {
                setMovesCount(movesCount - 1);
            }
        }
    }

    private: 
    int id;
    std::string name;
    char type;
    int factor;
    int movesCount;
    int maxMovesCount;
    std::string description;
};

class AbilityRegistry{
    public:
    void load(std::istream& is);
    std::vector<AbilityDef> getAbilities();
    void save(std::ostream &os);
    std::vector<AbilityDef> toAbilityDefs(const std::vector<Ability> &abilities);
    void setAbilities(const std::vector<AbilityDef>& defs);
private:
    std::vector<AbilityDef> abilities;
};
#endif