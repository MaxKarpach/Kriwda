#ifndef ABILITIESSYSTEM_H
#define ABILITIESSYSTEM_H

#include <iostream>
#include <vector>

#include "Player.h"
#include "Ability.h"
#include "Renderer.h"

class AbilitiesSystem {
 public:
  AbilitiesSystem(Player& player, std::vector<Ability>& abilities, Renderer& renderer);

  void change_abilities();

 private:
  Player& player_;
  std::vector<Ability>& abilities_;
  Renderer& renderer_;

  template <typename T>
  T* find_by_id(int id, std::vector<T>& vec);
};

#endif
