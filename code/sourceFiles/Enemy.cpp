#include "Enemy.h"

const int MAX_STRING_LEN = 255;

Enemy::Enemy(const EnemyDef& def)
    : id_(def.id), name_(def.name), hp_(def.hp), damage_(def.damage), stamina_(def.stamina), shield_(def.shield),
      dodge_count_(def.dodge_count), abilities_(def.abilities), location_id_(def.location_id), is_shield_on_(def.is_shield_on),
      is_dodge_on_(def.is_dodge_on), stamina_factor_(def.stamina_factor), shield_factor_(def.shield_factor),
      max_dodge_count_(def.max_dodge_count), max_stamina_(def.max_stamina), max_shield_(def.max_shield),
      stamina_recovery_factor_(def.stamina_recovery_factor), items_(def.items), description_(def.description),
      abilities_count_(def.abilities_count) {}

std::vector<EnemyDef> EnemyRegistry::get_enemies() {
    return enemies;
}

void EnemyRegistry::load(std::istream& is) {
    int enemies_count = 0;
    is >> enemies_count;
    for (int i = 0; i < enemies_count; i++) {
        EnemyDef ed;
        is >> ed.id;
        is.ignore(MAX_STRING_LEN, '\n');
        std::getline(is, ed.name);
        is >> ed.hp;
        is >> ed.damage;
        is >> ed.stamina;
        is >> ed.shield;
        is >> ed.dodge_count;
        is >> ed.abilities_count;
        for (int j = 0; j < ed.abilities_count; j++) {
            is >> ed.abilities[j];
        }
        is >> ed.location_id;
        is >> ed.is_shield_on;
        is >> ed.is_dodge_on;
        is >> ed.stamina_factor;
        is >> ed.shield_factor;
        is >> ed.max_dodge_count;
        is >> ed.max_stamina;
        is >> ed.max_shield;
        is >> ed.stamina_recovery_factor;

        int items_count = 0;
        is >> items_count;
        for (int j = 0; j < items_count; j++) {
            int item_id = 0;
            is >> item_id;
            ed.items.push_back(item_id);
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
        os << ed.dodge_count << std::endl;
        os << ed.abilities_count << std::endl;
        for (int i = 0; i < ed.abilities_count; i++) {
            os << ed.abilities[i] << std::endl;
        }
        os << ed.location_id << std::endl;
        os << ed.is_shield_on << std::endl;
        os << ed.is_dodge_on << std::endl;
        os << ed.stamina_factor << std::endl;
        os << ed.shield_factor << std::endl;
        os << ed.max_dodge_count << std::endl;
        os << ed.max_stamina << std::endl;
        os << ed.max_shield << std::endl;
        os << ed.stamina_recovery_factor << std::endl;
        os << ed.items.size() << std::endl;
        for (int i = 0; i < ed.items.size(); i++) {
            os << ed.items[i] << std::endl;
        }
        os << ed.description << std::endl;
    }
}

std::vector<EnemyDef> EnemyRegistry::to_enemy_defs(const std::vector<Enemy>& enemies) {
    std::vector<EnemyDef> defs;
    for (const auto& enemy : enemies) {
        EnemyDef def;
        def.id = enemy.get_id();
        def.name = enemy.get_name();
        def.hp = enemy.get_hp();
        def.damage = enemy.get_damage();
        def.stamina = enemy.get_stamina();
        def.shield = enemy.get_shield();
        def.dodge_count = enemy.get_dodge_count();
        def.abilities_count = enemy.get_abilities_count();
        def.abilities = enemy.get_abilities();
        def.location_id = enemy.get_location_id();
        def.is_shield_on = enemy.get_is_shield_on();
        def.is_dodge_on = enemy.get_is_dodge_on();
        def.stamina_factor = enemy.get_stamina_factor();
        def.shield_factor = enemy.get_shield_factor();
        def.max_dodge_count = enemy.get_max_dodge_count();
        def.max_stamina = enemy.get_max_stamina();
        def.max_shield = enemy.get_max_shield();
        def.stamina_recovery_factor = enemy.get_stamina_recovery_factor();
        def.items = enemy.get_items();
        def.description = enemy.get_description();
        defs.push_back(def);
    }
    return defs;
}

void EnemyRegistry::set_enemies(const std::vector<EnemyDef>& defs) {
    enemies = defs;
}
