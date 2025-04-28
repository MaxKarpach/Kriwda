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
};

class Enemy{
public:
Enemy(const int& id, const std::string& name, const int &hp, const int &damage, const int &stamina, const int &shield, const int &dodgeCount,
    const std::array<int, 3>& abilities, const int &chosenWeaponId);

    int getId() const { return id; }
    void setId(int value) { id = value; }

    std::string getName() const { return name; }
    void setName(std::string value) { name = value; }

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

    int getChosenWeaponId() const { return chosenWeaponId; }
    void setChosenWeaponId(int value) { chosenWeaponId = value; }

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
};


class EnemyRegistry{
    public:
    void load(std::istream& is);
    EnemyDef getEnemy();
private:
    EnemyDef enemy;
};
#endif