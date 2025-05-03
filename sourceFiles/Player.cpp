#include "../headerFiles/Player.h" 
#include <iostream>

Player::Player(const PlayerDef& def)
 : hp(def.hp), damage(def.damage), stamina(def.stamina), shield(def.shield), dodgeCount(def.dodgeCount), money(def.money), 
   locationId(def.locationId), dialogNodeId(def.dialogNodeId), inventory(def.inventory), abilities(def.abilities), 
   chosenAbilities(def.chosenAbilities), chosenWeaponId(def.chosenWeaponId), isShieldOn(def.isShieldOn), 
   isDodgeOn(def.isDodgeOn), staminaFactor(def.staminaFactor) {}

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
    is >> pd.money;
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
    is >> pd.chosenAbilities[0];
    is >> pd.chosenAbilities[1];
    is >> pd.chosenAbilities[2];
    is >> pd.chosenWeaponId;
    is >> pd.isShieldOn;
    is >> pd.isDodgeOn;
    is >> pd.staminaFactor;
    player = pd;
}