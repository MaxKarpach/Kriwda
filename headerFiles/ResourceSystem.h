#ifndef RESOURCESYSTEM_H
#define RESOURCESYSTEM_H

#include <iostream>
#include <string>
#include <vector>

#include <Player.h>
#include <Enemy.h>
#include <Location.h>
#include <Ability.h>
#include <Item.h>
#include <Scene.h>
#include <DialogNode.h>
#include <DialogChoice.h>
#include <Game.h>

class ResourceSystem {
 public:
  ResourceSystem(Player& player,
                 std::vector<Location>& locations,
                 std::vector<Enemy>& enemies,
                 std::vector<Ability>& abilities,
                 std::vector<Item>& items,
                 std::vector<DialogNode>& dialog_nodes,
                 std::vector<DialogChoice>& dialog_choices,
                 std::vector<Scene>& scenes,
                 Game& game,
                 std::string& file_name);

  void download_data();
  void save_game();

 private:
  Player& player_;
  std::vector<Enemy>& enemies_;
  std::vector<Location>& locations_;
  std::vector<Ability>& abilities_;
  std::vector<Item>& items_;
  std::vector<Scene>& scenes_;
  std::vector<DialogNode>& dialog_nodes_;
  std::vector<DialogChoice>& dialog_choices_;
  Game& game_;
  std::string& file_name_;
};

#endif

