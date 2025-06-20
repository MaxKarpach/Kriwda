#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include <iostream>
#include <Player.h>
#include <Enemy.h>
#include <Renderer.h>
#include <Location.h>
#include <Ability.h>

class BattleSystem {
 public:
  BattleSystem(Player& player, Enemy* enemy, Renderer& renderer, Location* location,
               std::vector<Ability*>& player_abilities, std::vector<Ability*>& enemy_abilities);

  void prepare_battle();
  void start_battle();
  bool end_battle();
  void clash();
  void battle();
  int enemy_move();
  void player_attack();
  void player_defence();
  void player_dodge();
  void player_ability();
  void enemy_attack();
  void enemy_defence();
  void enemy_dodge();
  void enemy_ability();

 private:
  Player& player_;
  Enemy* enemy_;
  Renderer& renderer_;
  Location* current_location_;
  std::vector<Ability*> player_abilities_;
  std::vector<Ability*> enemy_abilities_;
  int player_hp_;
  int enemy_hp_;
  int user_choice_;
  int enemy_choice_;
};

#endif
