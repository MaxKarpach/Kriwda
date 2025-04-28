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
    Location(const int& id, const std::string& name, const std::vector<int> &choices, const std::vector<int>& enemies);

    int getId() const { return id; }
    void setId(int value) { id = value; }

    std::string getName() const { return name; }
    void setName(std::string value) { name = value; }

    void addToChoices(int locationId){
        choices.push_back(locationId);
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
    LocationDef getLocation();
private:
    LocationDef location;
};
#endif