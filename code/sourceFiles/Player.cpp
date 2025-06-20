#include "Player.h"
#include <iostream>

Player::Player(const PlayerDef& def)
    : hp_(def.hp),
      damage_(def.damage),
      stamina_(def.stamina),
      shield_(def.shield),
      dodge_count_(def.dodge_count),
      location_id_(def.location_id),
      inventory_(def.inventory),
      abilities_(def.abilities),
      chosen_abilities_(def.chosen_abilities),
      chosen_weapon_id_(def.chosen_weapon_id),
      is_shield_on_(def.is_shield_on),
      is_dodge_on_(def.is_dodge_on),
      stamina_factor_(def.stamina_factor),
      shield_factor_(def.shield_factor),
      max_dodge_count_(def.max_dodge_count),
      max_stamina_(def.max_stamina),
      max_shield_(def.max_shield),
      stamina_recovery_factor_(def.stamina_recovery_factor),
      enemies_(def.enemies),
      abilities_count_(def.abilities_count) {}

Player::Player()
    : hp_(0),
      damage_(0),
      stamina_(0),
      shield_(0),
      dodge_count_(0),
      location_id_(0),
      chosen_weapon_id_(0),
      is_shield_on_(false),
      is_dodge_on_(false),
      stamina_factor_(0),
      shield_factor_(0),
      max_dodge_count_(0),
      max_stamina_(0),
      max_shield_(0),
      stamina_recovery_factor_(0),
      abilities_count_(3) {}

PlayerDef PlayerRegistry::get_player() {
    return player;
}

void PlayerRegistry::load(std::istream& is) {
    PlayerDef pd;

    is >> pd.hp;
    is >> pd.damage;
    is >> pd.stamina;
    is >> pd.shield;
    is >> pd.dodge_count;
    is >> pd.location_id;

    int inventorySize = 0;
    is >> inventorySize;
    for (int i = 0; i < inventorySize; i++) {
        int itemId;
        is >> itemId;
        pd.inventory.push_back(itemId);
    }

    int abilitiesSize = 0;
    is >> abilitiesSize;
    for (int i = 0; i < abilitiesSize; i++) {
        int abilityId;
        is >> abilityId;
        pd.abilities.push_back(abilityId);
    }

    is >> pd.abilities_count;
    for (int i = 0; i < pd.abilities_count; i++) {
        is >> pd.chosen_abilities[i];
    }

    is >> pd.chosen_weapon_id;
    is >> pd.is_shield_on;
    is >> pd.is_dodge_on;
    is >> pd.stamina_factor;
    is >> pd.shield_factor;
    is >> pd.max_dodge_count;
    is >> pd.max_stamina;
    is >> pd.max_shield;
    is >> pd.stamina_recovery_factor;

    int enemiesSize = 0;
    is >> enemiesSize;
    for (int i = 0; i < enemiesSize; i++) {
        int enemyId;
        is >> enemyId;
        pd.enemies.push_back(enemyId);
    }

    player = pd;
}

void PlayerRegistry::save(std::ostream& os) {
    os << player.hp << std::endl;
    os << player.damage << std::endl;
    os << player.stamina << std::endl;
    os << player.shield << std::endl;
    os << player.dodge_count << std::endl;
    os << player.location_id << std::endl;

    os << player.inventory.size() << std::endl;
    for (int itemId : player.inventory) {
        os << itemId << std::endl;
    }

    os << player.abilities.size() << std::endl;
    for (int abilityId : player.abilities) {
        os << abilityId << std::endl;
    }

    os << player.abilities_count << std::endl;
    for (int i = 0; i < player.abilities_count; i++) {
        os << player.chosen_abilities[i] << std::endl;
    }

    os << player.chosen_weapon_id << std::endl;
    os << player.is_shield_on << std::endl;
    os << player.is_dodge_on << std::endl;
    os << player.stamina_factor << std::endl;
    os << player.shield_factor << std::endl;
    os << player.max_dodge_count << std::endl;
    os << player.max_stamina << std::endl;
    os << player.max_shield << std::endl;
    os << player.stamina_recovery_factor << std::endl;

    os << player.enemies.size() << std::endl;
    for (int enemyId : player.enemies) {
        os << enemyId << std::endl;
    }
}

PlayerDef PlayerRegistry::to_player_def(Player& player) {
    PlayerDef def;

    def.hp = player.get_hp();
    def.damage = player.get_damage();
    def.stamina = player.get_stamina();
    def.shield = player.get_shield();
    def.dodge_count = player.get_dodge_count();
    def.location_id = player.get_location_id();
    def.inventory = player.get_inventory();
    def.abilities = player.get_abilities();
    def.abilities_count = player.get_abilities_count();
    def.chosen_abilities = player.get_chosen_abilities();
    def.chosen_weapon_id = player.get_chosen_weapon_id();
    def.is_shield_on = player.get_is_shield_on();
    def.is_dodge_on = player.get_is_dodge_on();
    def.stamina_factor = player.get_stamina_factor();
    def.shield_factor = player.get_shield_factor();
    def.max_dodge_count = player.get_max_dodge_count();
    def.max_stamina = player.get_max_stamina();
    def.max_shield = player.get_max_shield();
    def.stamina_recovery_factor = player.get_stamina_recovery_factor();
    def.enemies = player.get_enemies();

    return def;
}

void PlayerRegistry::set_player(const PlayerDef& def) {
    player = def;
}

