#include <iostream>
#ifndef PLAYER_H
#define PLAYER_H

#include <Renderer.h>

struct PlayerDef {
  int hp;
  int damage;
  int stamina;
  int shield;
  int dodgeCount;
  int locationId;
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
  std::vector<int> enemies;
  int abilitiesCount;
};

class Player {
 public:
  Player(const PlayerDef& def);
  Player();

  int getHp() const { return hp_; }
  void setHp(int value) { hp_ = value; }

  int getDamage() const { return damage_; }
  void setDamage(int value) { damage_ = value; }

  int getStamina() const { return stamina_; }
  void setStamina(int value) { stamina_ = value; }

  int getMaxStamina() const { return maxStamina_; }
  void setMaxStamina(int value) { maxStamina_ = value; }

  int getMaxShield() const { return maxShield_; }
  void setMaxShield(int value) { maxShield_ = value; }

  int getStaminaFactor() const { return staminaFactor_; }
  void setStaminaFactor(int value) { staminaFactor_ = value; }

  int getStaminaRecoveryFactor() const { return staminaRecoveryFactor_; }
  void setStaminaRecoveryFactor(int value) { staminaRecoveryFactor_ = value; }

  std::vector<int>& getInventory() { return inventory_; }

  int getShield() const { return shield_; }
  void setShield(int value) { shield_ = value; }

  int getAbilitiesCount() const { return abilitiesCount_; }
  void setAbilitiesCount(int value) { abilitiesCount_ = value; }

  int getShieldFactor() const { return shieldFactor_; }
  void setShieldFactor(int value) { shieldFactor_ = value; }

  bool getIsShieldOn() const { return isShieldOn_; }
  void setIsShieldOn(bool value) { isShieldOn_ = value; }

  bool getIsDodgeOn() const { return isDodgeOn_; }
  void setIsDodgeOn(bool value) { isDodgeOn_ = value; }

  int getDodgeCount() const { return dodgeCount_; }
  void setDodgeCount(int value) { dodgeCount_ = value; }

  int getMaxDodgeCount() const { return maxDodgeCount_; }
  void setMaxDodgeCount(int value) { maxDodgeCount_ = value; }

  void setInventory(std::vector<int> value) { inventory_ = value; }

  int getLocationId() const { return locationId_; }
  void setLocationId(int value) { locationId_ = value; }

  int getChosenWeaponId() const { return chosenWeaponId_; }
  void setChosenWeaponId(int value) { chosenWeaponId_ = value; }

  void showInventory() {
    for (int i = 0; i < inventory_.size(); i++) {
      Renderer renderer;
      renderer.printEndlineText(inventory_[i]);
    }
  }

  void addItemToInventory(int itemId) { inventory_.push_back(itemId); }

  void removeItemFromInventory(int itemId) {
    auto it = std::find(inventory_.begin(), inventory_.end(), itemId);
    if (it != inventory_.end()) {
      inventory_.erase(it);
    }
  }

  void showAbilities() {
    for (int i = 0; i < abilities_.size(); i++) {
      Renderer renderer;
      renderer.printEndlineText(abilities_[i]);
    }
  }

  void addAbility(int abilityId) { abilities_.push_back(abilityId); }

  void removeAbility(int abilityId) {
    auto it = std::find(abilities_.begin(), abilities_.end(), abilityId);
    if (it != abilities_.end()) {
      abilities_.erase(it);
    }
  }

  void showChosenAbilities() {
    for (int i = 0; i < chosenAbilities_.size(); i++) {
      Renderer renderer;
      renderer.printEndlineText(chosenAbilities_[i]);
    }
  }

  void addChosenAbility(int abilityId, int chosenAbilityIndex) {
    if ((chosenAbilities_.size() - 1) >= chosenAbilityIndex) {
      chosenAbilities_[chosenAbilityIndex] = abilityId;
    }
  }

  void removeChosenAbility(int chosenAbilityIndex) {
    chosenAbilities_[chosenAbilityIndex] = 0;
  }

  std::vector<int>& getAbilities() { return abilities_; }

  std::vector<int>& getEnemies() { return enemies_; }

  void addToEnemies(int enemyId) { enemies_.push_back(enemyId); }

  std::array<int, 3>& getChosenAbilities() { return chosenAbilities_; }

  int getEnemiesCount() { return enemies_.size(); }

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

  void initDodgeCount() {
    if (isDodgeOn_) {
      if (dodgeCount_ == maxDodgeCount_) {
        isDodgeOn_ = false;
        dodgeCount_ = 0;
      } else {
        Renderer renderer;
        renderer.printText("До уклонения осталось: ");
        renderer.printText(maxDodgeCount_ - dodgeCount_);
        renderer.printEndlineText(" хода(/ов)");
        dodgeCount_++;
      }
    }
  }

  void afterRoundInfo() {
    Renderer renderer;
    renderer.printText("Здоровье игрока: ");
    renderer.printEndlineText(hp_);
    renderer.printText("Щит игрока: ");
    renderer.printEndlineText(shield_);
    renderer.printText("Выносливость игрока: ");
    renderer.printEndlineText(stamina_);
  }

  void loseRound(int& playerHp) {
    hp_ = playerHp;
    stamina_ = maxStamina_;
    shield_ = maxShield_;
    dodgeCount_ = 0;
    isDodgeOn_ = 0;
    isShieldOn_ = 0;
  }

  void winRound(const int& enemyId, const int& playerHp) {
    addToEnemies(enemyId);
    hp_ = playerHp;
    stamina_ = maxStamina_;
    shield_ = maxShield_;
    dodgeCount_ = 0;
    isDodgeOn_ = 0;
    isShieldOn_ = 0;
  }

  void refreshStatsAfterRound() {
    if (shield_ < 0) {
      shield_ = 0;
    }
    isShieldOn_ = 0;
    if (stamina_ + staminaFactor_ < maxStamina_) {
      stamina_ = stamina_ + staminaRecoveryFactor_;
    }
    if (shield_ + shieldFactor_ < maxShield_) {
      shield_ = shield_ + shieldFactor_;
    }
  }

 private:
  int hp_;
  int damage_;
  int stamina_;
  int shield_;
  int dodgeCount_;
  int locationId_;
  std::vector<int> inventory_;
  std::vector<int> abilities_;
  std::array<int, 3> chosenAbilities_;
  int chosenWeaponId_;
  bool isShieldOn_;
  bool isDodgeOn_;
  int staminaFactor_;
  int shieldFactor_;
  int maxDodgeCount_;
  int maxStamina_;
  int maxShield_;
  int staminaRecoveryFactor_;
  std::vector<int> enemies_;
  int abilitiesCount_;
};

class PlayerRegistry {
 public:
  void load(std::istream& is);
  PlayerDef getPlayer();
  void save(std::ostream& os);
  PlayerDef toPlayerDef(Player& player);
  void setPlayer(const PlayerDef& def);

 private:
  PlayerDef player;
};

#endif  
