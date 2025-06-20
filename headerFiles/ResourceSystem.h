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
                 std::vector<DialogNode>& dialogNodes,
                 std::vector<DialogChoice>& dialogChoices,
                 std::vector<Scene>& scenes,
                 Game& game,
                 std::string& fileName);

  void downloadData();
  void saveGame();

 private:
  Player& player_;
  std::vector<Enemy>& enemies_;
  std::vector<Location>& locations_;
  std::vector<Ability>& abilities_;
  std::vector<Item>& items_;
  std::vector<Scene>& scenes_;
  std::vector<DialogNode>& dialogNodes_;
  std::vector<DialogChoice>& dialogChoices_;
  Game& game_;
  std::string& fileName_;
};

#endif
