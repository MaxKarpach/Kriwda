#include <iostream>
#ifndef LOCATION_H
#define LOCATION_H
struct LocationDef{
    int id;
    std::string name;
    std::vector<int> choices;
    int enemyId;
    int dialogNodeId;
    std::vector<int> items;
    std::string description;
    bool isFinalBossLocation;
};

class Location{
public:
    Location(const LocationDef& def);

    int getId() const { return id; }
    void setId(int value) { id = value; }

    int getDialogNodeId() const { return dialogNodeId; }
    void setDialogNodeId(int value) { dialogNodeId= value; }

    std::vector<int> getItems() const{ return items; }
    std::vector<int> getChoices() const { return choices; }

    std::string getName() const { return name; }
    void setName(std::string value) { name = value; }

    int getEnemyId() const { return enemyId; }
    void setEnemyId(int value) { enemyId = value; }

    void addChoice(const int& choiceId) {
        choices.push_back(choiceId);
    }
    void showChoices(){
        for (int i = 0; i < choices.size(); i++){
            std::cout << choices[i] << std::endl;
        }
    }
    void removeChoice(int choiceId) {
        auto it = std::find(choices.begin(), choices.end(), choiceId);
        if (it != choices.end()) {
            choices.erase(it);
        } 
    }

    void setItems(std::vector<int> newItems){
        for (int item : newItems){
            items.push_back(item);
        }
    }

    std::vector<int>& getItems() { return items; }

    std::string getDescription() const { return description; }
    void setDescription(std::string value) { description = value; }

    bool getIsFinalBossLocation() const { return isFinalBossLocation; }

private:
int id;
std::string name;
std::vector<int> choices;
int dialogNodeId;
int enemyId;
std::vector<int>items;
std::string description;
bool isFinalBossLocation;
};

class LocationRegistry{
    public:
    void load(std::istream& is);
    std::vector<LocationDef> getLocations();
    std::vector<LocationDef> toLocationDefs(const std::vector<Location> &locations);
    void save(std::ostream &os);
    void setLocations(const std::vector<LocationDef>& defs);
private:
    std::vector<LocationDef> locations;
};
#endif