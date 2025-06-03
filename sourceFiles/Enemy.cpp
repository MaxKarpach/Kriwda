#include "../headerFiles/Enemy.h" 
#include <iostream>

const int MAX_STRING_LEN = 255;

Enemy::Enemy(const EnemyDef& def)
: id(def.id), name(def.name), hp(def.hp), damage(def.damage), stamina(def.stamina), shield(def.shield), dodgeCount(def.dodgeCount),
abilities(def.abilities), chosenWeaponId(def.chosenWeaponId),locationId(def.locationId), isShieldOn(def.isShieldOn), 
isDodgeOn(def.isDodgeOn), staminaFactor(def.staminaFactor),shieldFactor(def.shieldFactor),
maxDodgeCount(def.maxDodgeCount), maxStamina(def.maxStamina), maxShield(def.maxShield),
staminaRecoveryFactor(def.staminaRecoveryFactor), items(def.items), description(def.description), abilitiesCount(def.abilitiesCount) {}

std::vector<EnemyDef> EnemyRegistry::getEnemies(){
    return enemies;
}

void EnemyRegistry::load(std::istream& is){
    int enemiesCount = 0;
    is >> enemiesCount;
    for (int i = 0; i < enemiesCount;i++){
        EnemyDef ed;
        is >> ed.id;
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, ed.name);
        is >> ed.hp;
        is >> ed.damage;
        is >> ed.stamina;
        is >> ed.shield;
        is >> ed.dodgeCount;
        is >> ed.abilitiesCount;
        for (int i = 0; i < ed.abilitiesCount; i++){
              is >> ed.abilities[i];
        }
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
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, ed.description);
        enemies.push_back(ed);
    }
}

void EnemyRegistry::save(std::ostream& os){
    os << enemies.size() << std::endl;
    for (const EnemyDef& ed : enemies) {
        os << ed.id << std::endl;
        os << ed.name << std::endl;
        os << ed.hp << std::endl;
        os << ed.damage << std::endl;
        os << ed.stamina << std::endl;
        os << ed.shield << std::endl;
        os << ed.dodgeCount << std::endl;
        os << ed.abilitiesCount << std::endl;
        for (int i = 0; i < ed.abilitiesCount; i++){
        os << ed.abilities[i] << std::endl;
        }
        os << ed.chosenWeaponId << std::endl;
        os << ed.locationId << std::endl;
        os << ed.isShieldOn << std::endl;
        os << ed.isDodgeOn << std::endl;
        os << ed.staminaFactor << std::endl;
        os << ed.shieldFactor << std::endl;
        os << ed.maxDodgeCount << std::endl;
        os << ed.maxStamina << std::endl;
        os << ed.maxShield << std::endl;
        os << ed.staminaRecoveryFactor << std::endl;
        os << ed.items.size() << std::endl;
        for (int i = 0; i < ed.items.size(); i++) {
            os << ed.items[i] << std::endl;
        }
        os << ed.description << std::endl;
    }
}
std::vector<EnemyDef> EnemyRegistry::toEnemyDefs(const std::vector<Enemy>& enemies) {
    std::vector<EnemyDef> defs;

    for (const auto& enemy : enemies) {
        EnemyDef def;
        def.id = enemy.getId();
        def.name = enemy.getName();
        def.hp = enemy.getHp();
        def.damage = enemy.getDamage();
        def.stamina = enemy.getStamina();
        def.shield = enemy.getShield();
        def.dodgeCount = enemy.getDodgeCount();
        def.abilitiesCount = enemy.getAbilitiesCount();
        def.abilities = enemy.getAbilities();
        def.chosenWeaponId = enemy.getChosenWeaponId();
        def.locationId = enemy.getLocationId();
        def.isShieldOn = enemy.getIsShieldOn();
        def.isDodgeOn = enemy.getIsDodgeOn();
        def.staminaFactor = enemy.getStaminaFactor();
        def.shieldFactor = enemy.getShieldFactor();
        def.maxDodgeCount = enemy.getMaxDodgeCount();
        def.maxStamina = enemy.getMaxStamina();
        def.maxShield = enemy.getMaxShield();
        def.staminaRecoveryFactor = enemy.getStaminaRecoveryFactor();
        def.items = enemy.getItems();
        def.description = enemy.getDescription();
        defs.push_back(def);
    }

    return defs;
}
void EnemyRegistry::setEnemies(const std::vector<EnemyDef>& defs) {
    enemies = defs;
}