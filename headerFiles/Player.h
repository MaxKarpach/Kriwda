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
    int inventory;
    int abilities;
    int chosenAbilities;
    int chosenWeapon;
};

class Player {
public:
    Player(const int &hp, const int &damage, const int &stamina, const int &shield, const int &dodgeCount,
           const int &money, const int &questId, const int &locationId, const int &dialogNodeId, const int &inventory,
           const int &abilities, const int &chosenAbilities, const int &chosenWeapon);

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

    int getQuestId() const { return questId; }
    void setQuestId(int value) { questId = value; }

    int getLocationId() const { return locationId; }
    void setLocationId(int value) { locationId = value; }

    int getDialogNodeId() const { return dialogNodeId; }
    void setDialogNodeId(int value) { dialogNodeId = value; }

    int getInventory() const { return inventory; }
    void setInventory(int value) { inventory = value; }

    int getAbilities() const { return abilities; }
    void setAbilities(int value) { abilities = value; }

    int getChosenAbilities() const { return chosenAbilities; }
    void setChosenAbilities(int value) { chosenAbilities = value; }

    int getChosenWeapon() const { return chosenWeapon; }
    void setChosenWeapon(int value) { chosenWeapon = value; }

private:
    int hp;
    int damage;
    int stamina;
    int shield;
    int dodgeCount;
    int money;
    int questId;
    int locationId;
    int dialogNodeId;
    int inventory;
    int abilities;
    int chosenAbilities;
    int chosenWeapon;
};


class PlayerRegistry{
    public:
    void load(std::istream& is);
    PlayerDef getPlayer();
private:
    PlayerDef player;
};
#endif