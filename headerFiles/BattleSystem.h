#include <iostream>
#include <Player.h>
#include <Enemy.h>
#include <Renderer.h>
#include <Location.h>
#include <Ability.h>

#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

class BattleSystem {
 public:
  BattleSystem(Player& player, Enemy* enemy, Renderer& renderer, Location* location,
               std::vector<Ability*>& playerAbilities, std::vector<Ability*>& enemyAbilities);

  void prepareBattle();
  void startBattle();
  bool endBattle();
  void clash();
  void battle();
  int enemyMove();

 private:
  Player& player_;
  Enemy* enemy_;
  Renderer& renderer_;
  Location* currentLocation_;
  std::vector<Ability*> playerAbilities_;
  std::vector<Ability*> enemyAbilities_;
  int playerHp_;
  int enemyHp_;
  int userChoice_;
  int enemyChoice_;
};

#endif  
