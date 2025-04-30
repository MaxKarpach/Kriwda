#include "../headerFiles/Player.h" 
#include <iostream>

Player::Player(const int &hp, const int &damage, const int &stamina, const int &shield, const int &dodgeCount,
    const int &money, const int &locationId, const int &dialogNodeId, const std::vector<int> &inventory,
    const std::vector<int> &abilities, const std::array<int, 3>& chosenAbilities, const int &chosenWeaponId)
 : hp(hp), damage(damage), stamina(stamina), shield(shield), dodgeCount(dodgeCount), money(money), 
   locationId(locationId), dialogNodeId(dialogNodeId), inventory(inventory), abilities(abilities), 
   chosenAbilities(chosenAbilities), chosenWeaponId(chosenWeaponId) {}

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
    player = pd;
}