#ifndef LOCATIONSYSTEM_H
#define LOCATIONSYSTEM_H

#include <iostream>
#include <vector>

#include <Player.h>
#include <Location.h>
#include <Renderer.h>
#include <Ability.h>
#include <Item.h>

class LocationSystem {
 public:
  LocationSystem(Player& player,
                 std::vector<Location>& locations,
                 int& enemiesCount,
                 Renderer& renderer,
                 std::vector<Ability>& abilities,
                 std::vector<Item>& items,
                 Location* currentLocation);

  void move();
  void lootAbilities();
  void lootItems();

 private:
  Player& player_;
  std::vector<Location>& locations_;
  std::vector<Ability>& abilities_;
  std::vector<Item>& items_;
  Renderer& renderer_;
  int& enemiesCount_;
  Location* currentLocation_;

  template <typename T>
  T* findById(int id, std::vector<T>& vec);
};

#endif  
