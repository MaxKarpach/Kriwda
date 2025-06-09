#include "../headerFiles/Player.h" 
#include <iostream>

Player::Player(const PlayerDef& def)
 : hp(def.hp), damage(def.damage), stamina(def.stamina), shield(def.shield), dodgeCount(def.dodgeCount), 
   locationId(def.locationId), dialogNodeId(def.dialogNodeId), inventory(def.inventory), abilities(def.abilities), 
   chosenAbilities(def.chosenAbilities), chosenWeaponId(def.chosenWeaponId), isShieldOn(def.isShieldOn), 
   isDodgeOn(def.isDodgeOn), staminaFactor(def.staminaFactor), shieldFactor(def.shieldFactor),
   maxDodgeCount(def.maxDodgeCount), maxStamina(def.maxStamina), maxShield(def.maxShield), 
   staminaRecoveryFactor(def.staminaRecoveryFactor), enemies(def.enemies), abilitiesCount(def.abilitiesCount) {}

Player::Player() 
    : hp(0), damage(0), stamina(0), shield(0), dodgeCount(0),
     locationId(0), dialogNodeId(0), chosenWeaponId(0),
      isShieldOn(false), isDodgeOn(false), staminaFactor(0),
      shieldFactor(0), maxDodgeCount(0), maxStamina(0),
      maxShield(0), staminaRecoveryFactor(0), abilitiesCount(3) {}

PlayerDef PlayerRegistry::getPlayer(){
    return player;
}

void PlayerRegistry::load(std::istream& is){
    PlayerDef pd;
    is >> pd.hp;
    is >> pd.damage;
    is >> pd.stamina;
    is >> pd.shield;
    is >> pd.dodgeCount;
    is >> pd.locationId;
    is >> pd.dialogNodeId;
    int inventorySize = 0;
    is >> inventorySize;
    for (int i = 0; i < inventorySize; i++){
        int itemId = 0;
        is >> itemId;
        pd.inventory.push_back(itemId);
    }
    int abilitiesSize = 0;
    is >> abilitiesSize;
    for (int i = 0; i < abilitiesSize; i++){
        int abilityId = 0;
        is >> abilityId;
        pd.abilities.push_back(abilityId);
    }
    is >> pd.abilitiesCount;
    for (int i = 0; i < pd.abilitiesCount; i++){
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
    for (int i = 0; i < enemiesSize; i++){
        int enemyId = 0;
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
    os << player.dialogNodeId << std::endl;

    os << player.inventory.size() << std::endl;
    for (int itemId : player.inventory) {
        os << itemId << std::endl;
    }

    os << player.abilities.size() << std::endl;
    for (int abilityId : player.abilities) {
        os << abilityId << std::endl;
    }
    os << player.abilitiesCount << std::endl;
    for (int i = 0; i < player.abilitiesCount; i++){
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
    def.dialogNodeId = player.getDialogNodeId();
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