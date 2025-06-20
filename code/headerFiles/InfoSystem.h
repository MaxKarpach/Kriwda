#ifndef INFO_SYSTEM_H
#define INFO_SYSTEM_H

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
  T* find_by_id(int id, std::vector<T>& vec);

  void show_descriptions();

 private:
  Player& player_;
  std::vector<Enemy>& enemies_;
  std::vector<Ability>& abilities_;
  std::vector<Item>& items_;
  Renderer& renderer_;

  template <typename T>
  void show_data_description(std::vector<int>& player_data,
                             std::vector<T>& data,
                             Renderer& renderer,
                             const std::string& description);
};

#endif
