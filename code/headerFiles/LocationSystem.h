#ifndef LOCATION_SYSTEM_H
#define LOCATION_SYSTEM_H

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
                 int& enemies_count,
                 Renderer& renderer,
                 std::vector<Ability>& abilities,
                 std::vector<Item>& items,
                 Location* current_location);

  void move();
  void loot_abilities();
  void loot_items();

 private:
  Player& player_;
  std::vector<Location>& locations_;
  std::vector<Ability>& abilities_;
  std::vector<Item>& items_;
  Renderer& renderer_;
  int& enemies_count_;
  Location* current_location_;

  template <typename T>
  T* find_by_id(int id, std::vector<T>& vec);
};

#endif

