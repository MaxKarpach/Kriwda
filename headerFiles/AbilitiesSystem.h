#include <iostream>
#include <Player.h>
#include <Ability.h>
#include <Renderer.h>

#ifndef ABILITIESSYSTEM_H
#define ABILITIESSYSTEM_H

class AbilitiesSystem {
 public:
  AbilitiesSystem(Player& player, std::vector<Ability>& abilities, Renderer& renderer);
  void changeAbilities();

  private:
  Player& player_;
  std::vector<Ability>& abilities_;
  Renderer &renderer_;
  template<typename T> T* findById(int id, std::vector<T>& vec);
};

#endif  