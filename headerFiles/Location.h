#include <iostream>
#ifndef LOCATION_H
#define LOCATION_H
struct LocationDef{
    int id;
    std::string name;
    std::vector<int> choices;
    std::vector<int> enemies;
};

class Location{
public:
    Location(const LocationDef& def);

    int getId() const { return id; }
    void setId(int value) { id = value; }

    std::string getName() const { return name; }
    void setName(std::string value) { name = value; }

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

    void addEnemy(const int& enemyId) {
        enemies.push_back(enemyId);
    }
    void showEnemies(){
        for (int i = 0; i < enemies.size(); i++){
            std::cout << enemies[i] << std::endl;
        }
    }
    void removeEnemy(int enemyId) {
        auto it = std::find(enemies.begin(), enemies.end(), enemyId);
        if (it != enemies.end()) {
            enemies.erase(it);
        } 
    }

private:
int id;
std::string name;
std::vector<int> choices;
std::vector<int> enemies;
};


class LocationRegistry{
    public:
    void load(std::istream& is);
    std::vector<LocationDef> getLocations();
private:
    std::vector<LocationDef> locations;
};
#endif