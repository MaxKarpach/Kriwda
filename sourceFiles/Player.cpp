#include "../headerFiles/Player.h"
#include <iostream>

Player::Player(const PlayerDef& def)
    : hp_(def.hp),
      damage_(def.damage),
      stamina_(def.stamina),
      shield_(def.shield),
      dodgeCount_(def.dodgeCount),
      locationId_(def.locationId),
      inventory_(def.inventory),
      abilities_(def.abilities),
      chosenAbilities_(def.chosenAbilities),
      chosenWeaponId_(def.chosenWeaponId),
      isShieldOn_(def.isShieldOn),
      isDodgeOn_(def.isDodgeOn),
      staminaFactor_(def.staminaFactor),
      shieldFactor_(def.shieldFactor),
      maxDodgeCount_(def.maxDodgeCount),
      maxStamina_(def.maxStamina),
      maxShield_(def.maxShield),
      staminaRecoveryFactor_(def.staminaRecoveryFactor),
      enemies_(def.enemies),
      abilitiesCount_(def.abilitiesCount) {}

Player::Player()
    : hp_(0),
      damage_(0),
      stamina_(0),
      shield_(0),
      dodgeCount_(0),
      locationId_(0),
      chosenWeaponId_(0),
      isShieldOn_(false),
      isDodgeOn_(false),
      staminaFactor_(0),
      shieldFactor_(0),
      maxDodgeCount_(0),
      maxStamina_(0),
      maxShield_(0),
      staminaRecoveryFactor_(0),
      abilitiesCount_(3) {}

PlayerDef PlayerRegistry::getPlayer() {
    return player;
}

void PlayerRegistry::load(std::istream& is) {
    PlayerDef pd;

    is >> pd.hp;
    is >> pd.damage;
    is >> pd.stamina;
    is >> pd.shield;
    is >> pd.dodgeCount;
    is >> pd.locationId;

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

    is >> pd.abilitiesCount;
    for (int i = 0; i < pd.abilitiesCount; i++) {
        is >> pd.chosenAbilities[i];
    }

    is >> pd.chosenWeaponId;
    is >> pd.isShieldOn;
    is >> pd.isDodgeOn;
    is >> pd.staminaFactor;
    is >> pd.shieldFactor;
    is >> pd.maxDodgeCount;
    is >> pd.maxStamina;
    is >> pd.maxShield;
    is >> pd.staminaRecoveryFactor;

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
    os << player.dodgeCount << std::endl;
    os << player.locationId << std::endl;

    os << player.inventory.size() << std::endl;
    for (int itemId : player.inventory) {
        os << itemId << std::endl;
    }

    os << player.abilities.size() << std::endl;
    for (int abilityId : player.abilities) {
        os << abilityId << std::endl;
    }

    os << player.abilitiesCount << std::endl;
    for (int i = 0; i < player.abilitiesCount; i++) {
        os << player.chosenAbilities[i] << std::endl;
    }

    os << player.chosenWeaponId << std::endl;
    os << player.isShieldOn << std::endl;
    os << player.isDodgeOn << std::endl;
    os << player.staminaFactor << std::endl;
    os << player.shieldFactor << std::endl;
    os << player.maxDodgeCount << std::endl;
    os << player.maxStamina << std::endl;
    os << player.maxShield << std::endl;
    os << player.staminaRecoveryFactor << std::endl;

    os << player.enemies.size() << std::endl;
    for (int enemyId : player.enemies) {
        os << enemyId << std::endl;
    }
}

PlayerDef PlayerRegistry::toPlayerDef(Player& player) {
    PlayerDef def;

    def.hp = player.getHp();
    def.damage = player.getDamage();
    def.stamina = player.getStamina();
    def.shield = player.getShield();
    def.dodgeCount = player.getDodgeCount();
    def.locationId = player.getLocationId();
    def.inventory = player.getInventory();
    def.abilities = player.getAbilities();
    def.abilitiesCount = player.getAbilitiesCount();
    def.chosenAbilities = player.getChosenAbilities();
    def.chosenWeaponId = player.getChosenWeaponId();
    def.isShieldOn = player.getIsShieldOn();
    def.isDodgeOn = player.getIsDodgeOn();
    def.staminaFactor = player.getStaminaFactor();
    def.shieldFactor = player.getShieldFactor();
    def.maxDodgeCount = player.getMaxDodgeCount();
    def.maxStamina = player.getMaxStamina();
    def.maxShield = player.getMaxShield();
    def.staminaRecoveryFactor = player.getStaminaRecoveryFactor();
    def.enemies = player.getEnemies();

    return def;
}

void PlayerRegistry::setPlayer(const PlayerDef& def) {
    player = def;
}
