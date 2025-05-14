#include <iostream>
#ifndef PLAYER_H
#define PLAYER_H
struct PlayerDef{
    int hp;
    int damage;
    int stamina;
    int shield;
    int dodgeCount;
    int money;
    int locationId;
    int dialogNodeId;
    std::vector<int> inventory;
    std::vector<int> abilities;
    std::array<int, 3> chosenAbilities;
    int chosenWeaponId;
    bool isShieldOn;
    bool isDodgeOn;
    int staminaFactor;
    int shieldFactor;
    int maxDodgeCount;
    int maxStamina;
    int maxShield;
    int staminaRecoveryFactor;
};

class Player {
public:
    Player(const PlayerDef& def);

    int getHp() const { return hp; }
    void setHp(int value) { hp = value; }

    int getDamage() const { return damage; }
    void setDamage(int value) { damage = value; }

    int getStamina() const { return stamina; }
    void setStamina(int value) { stamina = value; }

    int getMaxStamina() const { return maxStamina; }
    void setMaxStamina(int value) { maxStamina = value; }

    int getMaxShield() const { return maxShield; }
    void setMaxShield(int value) { maxShield = value; }

    int getStaminaFactor() const { return staminaFactor; }
    void setStaminaFactor(int value) { staminaFactor = value; }

    int getStaminaRecoveryFactor() const { return staminaRecoveryFactor; }
    void setStaminaRecoveryFactor(int value) { staminaRecoveryFactor = value; }

    std::vector<int> getInventory() const { return inventory; }

    int getShield() const { return shield; }
    void setShield(int value) { shield = value; }

    int getShieldFactor() const { return shieldFactor; }
    void setShieldFactor(int value) { shieldFactor = value; }

    bool getIsShieldOn() const { return isShieldOn; }
    void setIsShieldOn(bool value) { isShieldOn = value; }

    bool getIsDodgeOn() const { return isDodgeOn; }
    void setIsDodgeOn(bool value) { isDodgeOn = value; }

    int getDodgeCount() const { return dodgeCount; }
    void setDodgeCount(int value) { dodgeCount = value;}

     int getMaxDodgeCount() const { return maxDodgeCount; }
     void setMaxDodgeCount(int value) {maxDodgeCount = value;}

     void setInventory(std::vector<int> value) { inventory = value; }

     int getMoney() const { return money; }
     void setMoney(int value) { money = value; }

     int getLocationId() const { return locationId; }
     void setLocationId(int value) { locationId = value; }

     int getDialogNodeId() const { return dialogNodeId; }
     void setDialogNodeId(int value) { dialogNodeId = value; }

     int getChosenWeaponId() const { return chosenWeaponId; }
     void setChosenWeaponId(int value) { chosenWeaponId = value; }

     void showInventory()
     {
         for (int i = 0; i < inventory.size(); i++)
         {
             std::cout << inventory[i] << std::endl;
         }
    }
    void addItemToInventory(int itemId){
        inventory.push_back(itemId);
    }
    void removeItemFromInventory(int itemId) {
        auto it = std::find(inventory.begin(), inventory.end(), itemId);
        if (it != inventory.end()) {
            inventory.erase(it);
        } 
    }

    void showAbilities(){
        for (int i = 0; i < abilities.size(); i++){
            std::cout << abilities[i] << std::endl;
        }
    }
    void addAbility(int abilityId){
        abilities.push_back(abilityId);
    }
    void removeAbility(int abilityId) {
        auto it = std::find(abilities.begin(), abilities.end(), abilityId);
        if (it != abilities.end()) {
            abilities.erase(it);
        } 
    }
    void showChosenAbilities(){
        for (int i = 0; i < chosenAbilities.size(); i++){
            std::cout << chosenAbilities[i] << std::endl;
        }
    }
    void addChosenAbility(int abilityId, int chosenAbilityIndex){
        if ((chosenAbilities.size()-1) >= chosenAbilityIndex){
            chosenAbilities[chosenAbilityIndex] = abilityId;
        }
    }
    void removeChosenAbility(int chosenAbilityIndex) {
        chosenAbilities[chosenAbilityIndex] = 0;
    }

    std::array<int, 3> getChosenAbilities(){
        return chosenAbilities;
    }

    std::vector<int> getAbilities(){
        return abilities;
    }

private:
    int hp;
    int damage;
    int stamina;
    int shield;
    int dodgeCount;
    int money;
    int locationId;
    int dialogNodeId;
    std::vector<int> inventory;
    std::vector<int> abilities;
    std::array<int, 3> chosenAbilities;
    int chosenWeaponId;
    bool isShieldOn;
    bool isDodgeOn;
    int staminaFactor;
    int shieldFactor;
    int maxDodgeCount;
    int maxStamina;
    int maxShield;
    int staminaRecoveryFactor;
};

class PlayerRegistry{
    public:
    void load(std::istream& is);
    PlayerDef getPlayer();
    void save(std::ostream &os);
private:
    PlayerDef player;
};
#endif