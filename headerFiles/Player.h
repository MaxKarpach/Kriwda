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
    int questId;
    int locationId;
    int dialogNodeId;
    std::vector<int> inventory;
    std::vector<int> abilities;
    std::array<int, 3> chosenAbilities;
    int chosenWeaponId;
};

class Player {
public:
    Player(const int &hp, const int &damage, const int &stamina, const int &shield, const int &dodgeCount,
           const int &money, const int &locationId, const int &dialogNodeId, const std::vector<int> &inventory,
           const std::vector<int> &abilities, const std::array<int, 3>& chosenAbilities, const int &chosenWeaponId);

    int getHp() const { return hp; }
    void setHp(int value) { hp = value; }

    int getDamage() const { return damage; }
    void setDamage(int value) { damage = value; }

    int getStamina() const { return stamina; }
    void setStamina(int value) { stamina = value; }

    int getShield() const { return shield; }
    void setShield(int value) { shield = value; }

    int getDodgeCount() const { return dodgeCount; }
    void setDodgeCount(int value) { dodgeCount = value; }

    int getMoney() const { return money; }
    void setMoney(int value) { money = value; }

    int getLocationId() const { return locationId; }
    void setLocationId(int value) { locationId = value; }

    int getDialogNodeId() const { return dialogNodeId; }
    void setDialogNodeId(int value) { dialogNodeId = value; }

    int getChosenWeaponId() const { return chosenWeaponId; }
    void setChosenWeaponId(int value) { chosenWeaponId = value; }

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
};


class PlayerRegistry{
    public:
    void load(std::istream& is);
    PlayerDef getPlayer();
private:
    PlayerDef player;
};
#endif