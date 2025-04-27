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
    int abilities;
    int chosenWeapon;
};

class Enemy{
public:
    Enemy(const int& id, const std::string& name, const int &hp, const int &damage, const int &stamina, const int &shield, const int &dodgeCount,
           const int &abilities, const int &chosenWeapon);

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

    int getAbilities() const { return abilities; }
    void setAbilities(int value) { abilities = value; }

    int getChosenWeapon() const { return chosenWeapon; }
    void setChosenWeapon(int value) { chosenWeapon = value; }

private:
    std::string name;
    int id;
    int hp;
    int damage;
    int stamina;
    int shield;
    int dodgeCount;
    int abilities;
    int chosenWeapon;
};


class EnemyRegistry{
    public:
    void load(std::istream& is);
    EnemyDef getEnemy();
private:
    EnemyDef enemy;
};
#endif