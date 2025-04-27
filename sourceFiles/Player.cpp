#include "../headerFiles/Player.h" 
#include <iostream>

Player::Player(const int &hp, const int &damage, const int &stamina, const int &shield, const int &dodgeCount,
    const int &money, const int& questId, const int& locationId, const int& dialogNodeId, const int& inventory,
    const int& abilities, const int& chosenAbilities, const int& chosenWeapon)
 : hp(hp), damage(damage), stamina(stamina), shield(shield), dodgeCount(dodgeCount), money(money), 
   questId(questId), locationId(locationId), dialogNodeId(dialogNodeId), inventory(inventory),
   abilities(abilities), chosenAbilities(chosenAbilities), chosenWeapon(chosenWeapon) {}

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
    is >> pd.questId;
    is >> pd.locationId;
    is >> pd.dialogNodeId;
    is >> pd.inventory;
    is >> pd.abilities;
    is >> pd.chosenAbilities;
    is >> pd.chosenWeapon;
    player = pd;
}