#include "../headerFiles/Enemy.h" 
#include <iostream>

const int MAX_STRING_LEN = 20;

Enemy::Enemy(const EnemyDef& def)
: id(def.id), name(def.name), hp(def.hp), damage(def.damage), stamina(def.stamina), shield(def.shield), dodgeCount(def.dodgeCount),
abilities(def.abilities), chosenWeaponId(def.chosenWeaponId),locationId(def.locationId) {}

EnemyDef EnemyRegistry::getEnemy(){
    return enemy;
}

void EnemyRegistry::load(std::istream& is){
    EnemyDef ed;
    is >> ed.id;
    char buf[MAX_STRING_LEN + 1] = {0};
    is.getline(buf, MAX_STRING_LEN);
    memset(buf, 0, sizeof(buf));
    is.getline(buf, MAX_STRING_LEN);
    ed.name = buf;
    is >> ed.hp;
    is >> ed.damage;
    is >> ed.stamina;
    is >> ed.shield;
    is >> ed.dodgeCount;
    is >> ed.abilities[0];
    is >> ed.abilities[1];
    is >> ed.abilities[2];
    is >> ed.chosenWeaponId;
    is >> ed.locationId;
    enemy = ed;
}