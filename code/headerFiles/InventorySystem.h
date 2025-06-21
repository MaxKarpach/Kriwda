#ifndef INVENTORY_SYSTEM_H
#define INVENTORY_SYSTEM_H

#include <iostream>
#include <vector>

#include <Player.h>
#include <Item.h>
#include <Renderer.h>

class InventorySystem {
 public:
  InventorySystem(Player& player,
                  std::vector<Item>& items,
                  Renderer& renderer);

  void show_inventory();
  void show_chosen_weapon();
  void item_effect(char& type, Item* item, int& input, std::vector<int>& inventory);

 private:
  Player& player_;
  std::vector<Item>& items_;
  Renderer& renderer_;

  template <typename T>
  T* find_by_id(int id, std::vector<T>& vec);
};

#endif
