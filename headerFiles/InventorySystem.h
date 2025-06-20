#include <iostream>
#include <Player.h>
#include <Item.h>
#include <Renderer.h>


#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H

class InventorySystem {
 public:
  InventorySystem(Player& player, std::vector<Item>& items, Renderer& renderer);

  void showInventory();
  void showChosenWeapon();

private:
  Player& player_;
  std::vector<Item>& items_;
  Renderer& renderer_;
  template<typename T> T* findById(int id, std::vector<T>& vec);
};

#endif  
