#include "../headerFiles/Enemy.h" 
#include <iostream>

const int MAX_STRING_LEN = 255;

Enemy::Enemy(const EnemyDef& def)
    : id_(def.id), name_(def.name), hp_(def.hp), damage_(def.damage), stamina_(def.stamina), shield_(def.shield),
      dodgeCount_(def.dodgeCount), abilities_(def.abilities), locationId_(def.locationId), isShieldOn_(def.isShieldOn),
      isDodgeOn_(def.isDodgeOn), staminaFactor_(def.staminaFactor), shieldFactor_(def.shieldFactor),
      maxDodgeCount_(def.maxDodgeCount), maxStamina_(def.maxStamina), maxShield_(def.maxShield),
      staminaRecoveryFactor_(def.staminaRecoveryFactor), items_(def.items), description_(def.description),
      abilitiesCount_(def.abilitiesCount) {}

std::vector<EnemyDef> EnemyRegistry::getEnemies() {
    return enemies;
}

void EnemyRegistry::load(std::istream& is) {
    int enemiesCount = 0;
    is >> enemiesCount;
    for (int i = 0; i < enemiesCount; i++) {
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
        for (int j = 0; j < ed.abilitiesCount; j++) {
            is >> ed.abilities[j];
        }
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
        for (int j = 0; j < itemsCount; j++) {
            int itemId = 0;
            is >> itemId;
            ed.items.push_back(itemId);
        }

        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, ed.description);

        enemies.push_back(ed);
    }
}

void EnemyRegistry::save(std::ostream& os) {
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
        for (int i = 0; i < ed.abilitiesCount; i++) {
            os << ed.abilities[i] << std::endl;
        }
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
