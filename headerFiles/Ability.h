#include <iostream>
#include <Renderer.h>
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

    std::string getDescription() const { return description_; }
    void setDescription(std::string value) { description_ = value; }

    int getId() const { return id_; }
    void setId(int value) { id_ = value; }

    std::string getName() const { return name_; }
    void setName(std::string value) { name_ = value; }

    char getType() const { return type_; }
    void setType(char value) { type_ = value; }

    int getFactor() const { return factor_; }
    void setFactor(int value) { factor_ = value; }

    int getMovesCount() const { return movesCount_; }
    void setMovesCount(int value){movesCount_ = value;}

    int getMaxMovesCount() const { return maxMovesCount_; }
    void setMaxMovesCount(int value){maxMovesCount_ = value;}

    void countMoves(){
        if (maxMovesCount_ != movesCount_){
            Renderer renderer;
            renderer.printText("До возможности использовать способность ");
            renderer.printText(name_);
            renderer.printText(" осталось ");
            renderer.printText(movesCount_ + 2);
            renderer.printEndlineText(" хода(ов)");
        }
    }

    void refreshMovesCount(){
        if (maxMovesCount_ != movesCount_){
            if (movesCount_ == -1){
                movesCount_ = maxMovesCount_;
            }
            else {
                movesCount_--;
            }
        }
    }

    private: 
    int id_;
    std::string name_;
    char type_;
    int factor_;
    int movesCount_;
    int maxMovesCount_;
    std::string description_;
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