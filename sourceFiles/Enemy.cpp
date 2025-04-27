#include "../headerFiles/Enemy.h" 
#include <iostream>

const int MAX_STRING_LEN = 20;

Enemy::Enemy(const int& id, const std::string& name, const int &hp, const int &damage, const int &stamina, const int &shield, const int &dodgeCount,
    const int &abilities, const int &chosenWeapon)
 : id(id), name(name), hp(hp), damage(damage), stamina(stamina), shield(shield), dodgeCount(dodgeCount),
   abilities(abilities), chosenWeapon(chosenWeapon) {}

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
    is >> ed.abilities;
    is >> ed.chosenWeapon;
    enemy = ed;
}