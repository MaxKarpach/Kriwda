#include <iostream>
#ifndef ENEMY_H
#define ENEMY_H
struct EnemyDef{
    int id;
    std::string name;
    int hp;
    int damage;
    int stamina;
    int shield;
    int dodgeCount;
    std::array<int, 3> abilities;
    int chosenWeaponId;
    int locationId;
    bool isShieldOn;
    bool isDodgeOn;
    int staminaFactor;
    int shieldFactor;
    int maxDodgeCount;
    int maxStamina;
    int maxShield;
    int staminaRecoveryFactor;
    std::vector<int> items;
    std::string description;
};

class Enemy{
public:
Enemy(const EnemyDef& def);

    int getId() const { return id; }
    void setId(int value) { id = value; }

    std::string getName() const { return name; }
    void setName(std::string value) { name = value; }

    std::string getDescription() const { return description; }
    void setDescription(std::string value) { description = value; }

    int getHp() const { return hp; }
    void setHp(int value) { hp = value; }

    int getDamage() const { return damage; }
    void setDamage(int value) { damage = value; }

    bool getIsShieldOn() const { return isShieldOn; }
    void setIsShieldOn(bool value) { isShieldOn = value; }

    bool getIsDodgeOn() const { return isDodgeOn; }
    void setIsDodgeOn(bool value) { isDodgeOn = value; }

    int getStamina() const { return stamina; }
    void setStamina(int value) { stamina = value; }

    int getStaminaFactor() const { return staminaFactor; }
    void setStaminaFactor(int value) { staminaFactor = value; }

    int getShieldFactor() const { return shieldFactor; }
    void setShieldFactor(int value) { shieldFactor = value; }

    int getShield() const { return shield; }
    void setShield(int value) { shield = value; }

    int getDodgeCount() const { return dodgeCount; }
    void setDodgeCount(int value) { dodgeCount = value; }

    int getStaminaRecoveryFactor() const { return staminaRecoveryFactor; }
    void setStaminaRecoveryFactor(int value) { staminaRecoveryFactor = value; }

    int getChosenWeaponId() const { return chosenWeaponId; }
    void setChosenWeaponId(int value) { chosenWeaponId = value; }

    int getLocationId() const { return locationId; }
    void setLocationId(int value) { locationId = value; }

    void showAbilities(){
        for (int i = 0; i < abilities.size(); i++){
            std::cout << abilities[i] << std::endl;
        }
    }
    void addAbility(int abilityId, int abilityIndex){
        if ((abilities.size()-1) >= abilityIndex){
            abilities[abilityIndex] = abilityId;
        }
    }
    void removeAbility(int abilityIndex) {
        abilities[abilityIndex] = 0;
    }

    std::array<int, 3> getAbilities(){
        return abilities;
    }

    int getMaxStamina() const { return maxStamina; }
    void setMaxStamina(int value) { maxStamina = value; }

    int getMaxShield() const { return maxShield; }
    void setMaxShield(int value) { maxShield = value; }

    int getMaxDodgeCount() const { return maxDodgeCount; }
    void setMaxDodgeCount(int value) {maxDodgeCount = value;}

private:
    std::string name;
    int id;
    int hp;
    int damage;
    int stamina;
    int shield;
    int dodgeCount;
    std::array<int, 3> abilities;
    int chosenWeaponId;
    int locationId;
    bool isShieldOn;
    bool isDodgeOn;
    int staminaFactor;
    int shieldFactor;
    int maxDodgeCount;
    int maxStamina;
    int maxShield;
    int staminaRecoveryFactor;
    std::vector<int> items;
    std::string description;
};


class EnemyRegistry{
    public:
    void load(std::istream& is);
    std::vector<EnemyDef> getEnemies();
private:
    std::vector<EnemyDef> enemies;
};
#endif