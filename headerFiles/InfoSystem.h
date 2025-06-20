#ifndef INFOSYSTEM_H
#define INFOSYSTEM_H

#include <iostream>
#include <vector>
#include <string>

#include <Player.h>
#include <Enemy.h>
#include <Ability.h>
#include <Item.h>
#include <Renderer.h>

class InfoSystem {
 public:
  InfoSystem(Player& player,
             std::vector<Enemy>& enemies,
             std::vector<Ability>& abilities,
             std::vector<Item>& items,
             Renderer& renderer);

  template <typename T>
  T* findById(int id, std::vector<T>& vec);

  void showDescriptions();

 private:
  Player& player_;
  std::vector<Enemy>& enemies_;
  std::vector<Ability>& abilities_;
  std::vector<Item>& items_;
  Renderer& renderer_;

  template <typename T>
  void showDataDescription(std::vector<int>& playerData,
                           std::vector<T>& data,
                           Renderer& renderer,
                           const std::string& description);
};

#endif
