#include "../headerFiles/Enemy.h" 
#include <iostream>

const int MAX_STRING_LEN = 100;

Enemy::Enemy(const EnemyDef& def)
: id(def.id), name(def.name), hp(def.hp), damage(def.damage), stamina(def.stamina), shield(def.shield), dodgeCount(def.dodgeCount),
abilities(def.abilities), chosenWeaponId(def.chosenWeaponId),locationId(def.locationId), isShieldOn(def.isShieldOn), 
isDodgeOn(def.isDodgeOn), staminaFactor(def.staminaFactor),shieldFactor(def.shieldFactor),
maxDodgeCount(def.maxDodgeCount), maxStamina(def.maxStamina), maxShield(def.maxShield),
staminaRecoveryFactor(def.staminaRecoveryFactor), items(def.items), description(def.description) {}

std::vector<EnemyDef> EnemyRegistry::getEnemies(){
    return enemies;
}

void EnemyRegistry::load(std::istream& is){
    int enemiesCount = 0;
    is >> enemiesCount;
    for (int i = 0; i < enemiesCount;i++){
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
        is >> ed.isShieldOn;
        is >> ed.isDodgeOn;
        is >> ed.staminaFactor;
        is >> ed.shieldFactor;
        is >> ed.maxDodgeCount;
        is >> ed.maxStamina;
        is >> ed.maxShield;
        is >> ed.staminaRecoveryFactor;
        int itemsCount = 0;
        is >> itemsCount;
        for (int i = 0; i < itemsCount; i++){
            int itemId = 0;
            is >> itemId;
            ed.items.push_back(itemId);
        }
        char buf2[MAX_STRING_LEN + 1] = {0};
        is.getline(buf2, MAX_STRING_LEN);
        memset(buf2, 0, sizeof(buf2));
        is.getline(buf2, MAX_STRING_LEN);
        ed.description = buf2;
            enemies.push_back(ed);
    }
}