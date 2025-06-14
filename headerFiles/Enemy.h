#include <iostream>
#ifndef ENEMY_H
#define ENEMY_H
#include <Renderer.h>
struct EnemyDef{
    int id;
    std::string name;
    int hp;
    int damage;
    int stamina;
    int shield;
    int dodgeCount;
    std::array<int, 3> abilities;
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
    int abilitiesCount;
};

class Enemy{
public:
Enemy(const EnemyDef& def);

    int getId() const { return id_; }
    void setId(int value) { id_ = value; }

    std::array<int, 3> getAbilities() const {return abilities_; }

    std::string getName() const { return name_; }
    void setName(std::string value) { name_ = value; }

    std::string getDescription() const { return description_; }
    void setDescription(std::string value) { description_ = value; }

    int getHp() const { return hp_; }
    void setHp(int value) { hp_ = value; }

    int getDamage() const { return damage_; }
    void setDamage(int value) { damage_ = value; }

    bool getIsShieldOn() const { return isShieldOn_; }
    void setIsShieldOn(bool value) { isShieldOn_ = value; }

    bool getIsDodgeOn() const { return isDodgeOn_; }
    void setIsDodgeOn(bool value) { isDodgeOn_ = value; }

    int getStamina() const { return stamina_; }
    void setStamina(int value) { stamina_ = value; }

    int getStaminaFactor() const { return staminaFactor_; }
    void setStaminaFactor(int value) { staminaFactor_ = value; }

    int getShieldFactor() const { return shieldFactor_; }
    void setShieldFactor(int value) { shieldFactor_ = value; }

    int getShield() const { return shield_; }
    void setShield(int value) { shield_ = value; }

    int getDodgeCount() const { return dodgeCount_; }
    void setDodgeCount(int value) { dodgeCount_ = value; }

    int getStaminaRecoveryFactor() const { return staminaRecoveryFactor_; }
    void setStaminaRecoveryFactor(int value) { staminaRecoveryFactor_ = value; }

    int getLocationId() const { return locationId_; }
    void setLocationId(int value) { locationId_ = value; }

    void showAbilities(){
        for (int i = 0; i < abilities_.size(); i++){
            Renderer renderer;
            renderer.printEndlineText(abilities_[i]);
        }
    }
    void addAbility(int abilityId, int abilityIndex){
        if ((abilities_.size()-1) >= abilityIndex){
            abilities_[abilityIndex] = abilityId;
        }
    }
    void removeAbility(int abilityIndex) {
        abilities_[abilityIndex] = 0;
    }

    std::array<int, 3> getAbilities(){
        return abilities_;
    }

    int getMaxStamina() const { return maxStamina_; }
    void setMaxStamina(int value) { maxStamina_ = value; }

    int getMaxShield() const { return maxShield_; }
    void setMaxShield(int value) { maxShield_ = value; }

    int getAbilitiesCount() const { return abilitiesCount_; }
    void setAbilitiesCount(int value) { abilitiesCount_ = value; }

    int getMaxDodgeCount() const { return maxDodgeCount_; }
    void setMaxDodgeCount(int value) {maxDodgeCount_ = value;}

    std::vector<int> getItems() const { return items_; }
    void setItems(const std::vector<int>& value) { items_ = value; }

        void updateDodgeState() {
        if (isDodgeOn_) {
            if (dodgeCount_ >= maxDodgeCount_) {
                isDodgeOn_ = false;
                dodgeCount_ = 0;
            } else {
                dodgeCount_++;
            }
        }
    }

        void initDodgeCount(){
            if (isDodgeOn_){
            if (dodgeCount_ == maxDodgeCount_){
                isDodgeOn_ = false;
                dodgeCount_ = 0;
            }
            else
            {
                dodgeCount_++;
            }
        }
    }

        void afterRoundInfo(){
            Renderer renderer;
            renderer.printText("Здоровье врага: ");
            renderer.printEndlineText(hp_);
    }

        void winRound(int& enemyHp){
            hp_ = enemyHp;
            stamina_ = maxStamina_;
            shield_ = maxShield_;
            dodgeCount_ = 0;
            isDodgeOn_ = 0;
            isShieldOn_ = 0;
    }

        void refreshStatsAfterRound(){
        if (shield_ < 0){
            shield_ = 0;
        }
        isShieldOn_ = 0;
        if (stamina_ + staminaFactor_ < maxStamina_){
            stamina_ = stamina_ + staminaRecoveryFactor_;
        }
        if (shield_ + shieldFactor_ < maxShield_){
            shield_ = shield_ + shieldFactor_;
        }
        
    }

private:
    std::string name_;
    int id_;
    int hp_;
    int damage_;
    int stamina_;
    int shield_;
    int dodgeCount_;
    std::array<int, 3> abilities_;
    int locationId_;
    bool isShieldOn_;
    bool isDodgeOn_;
    int staminaFactor_;
    int shieldFactor_;
    int maxDodgeCount_;
    int maxStamina_;
    int maxShield_;
    int staminaRecoveryFactor_;
    std::vector<int> items_;
    std::string description_;
    int abilitiesCount_;
};


class EnemyRegistry{
    public:
    void load(std::istream& is);
    std::vector<EnemyDef> getEnemies();
    void save(std::ostream &os);
    std::vector<EnemyDef> toEnemyDefs(const std::vector<Enemy>& enemies);
    void setEnemies(const std::vector<EnemyDef>& defs);
private:
    std::vector<EnemyDef> enemies;
};
#endif