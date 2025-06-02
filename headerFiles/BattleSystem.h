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

private:
    Player& player;
    Enemy* enemy;
    Renderer& renderer;
    Location* currentLocation;
 std::vector<Ability*> playerAbilities;
std::vector<Ability*> enemyAbilities;
    int playerHp;
    int enemyHp;
    int userChoice;
    int enemyChoice;
};
#endif