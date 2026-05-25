#pragma once
#include <csignal>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>

class NoManaException : public std::exception {
  public:
    const char *what() const noexcept override {
        return "Za mało many na wykonianie tej akcji";
    }
};

class Character;

class CanCastSpells {
  protected:
    int mana;
    int maxMana;

  public:
    CanCastSpells(int mana_) : mana(mana_), maxMana(mana_) {};
    virtual ~CanCastSpells() = default;

    const int getMana() { return mana; }
    void addMana(int amount) {
        int mx_to_add = std::min(amount + mana, maxMana);
        std::cout << "dodano " << mx_to_add << " many" << std::endl;
    }

    void useMana(int amount) {
        if (amount > getMana())
            throw NoManaException();

        mana -= amount;
        std::cout << "Zużyto " << amount << " many. Zostało " << getMana()
                  << std::endl;
    }

    virtual void castSpell(Character *target) = 0;
};

class CanUseMelee {

  public:
    CanUseMelee() = default;
    virtual ~CanUseMelee() = default;
    virtual void performMeleeAttack(Character *target) = 0;
};

class Character {
  protected:
    int health;
    int maxHealth;
    std::string name;

  public:
    Character(const std::string &name_, int health_ = 100)
        : health(health_), maxHealth(health_), name(name_) {};

    virtual ~Character() = default;

    const std::string &getName() const { return name; }
    const int getHealth() { return health; }
    bool isAlive() { return health > 0; }
    void takeDamage(int damage) {
        if (!isAlive()) {
            std::cout << "Postać nie żyje" << std::endl;
            return;
        }
        int damage_taken = std::min(damage, health);
        health -= damage_taken;

        std::cout << "Postać otrzymała " << damage_taken << " obrażeń"
                  << std::endl;
        if (!isAlive())
            std::cout << "Postać nie żyje" << std::endl;
    }
    void heal(int hp) {
        int new_hp = std::min(hp + health, maxHealth);
        int wyleczone = new_hp - health;
        std::cout << "Wyleczono " << wyleczone << std::endl;
        health = new_hp;
        std::cout << "Aktualne życie " << getHealth() << std::endl;
    }

    virtual void attack(Character *target) = 0;
};

class Warrior : public Character, public CanUseMelee {
  protected:
    int meleeDamage;

  public:
    Warrior(const std::string &name_, int health_ = 120, int meleeDamage_ = 15)
        : Character(name_, health_), CanUseMelee(),
          meleeDamage(meleeDamage_) {};
    void performMeleeAttack(Character *target) override;
    void attack(Character *target) override;
};

class Mage : public Character, CanCastSpells {
  protected:
    int spellDamage;

  public:
    Mage(const std::string &name_, int health_ = 80, int damage_ = 20,
         int mana_ = 150)
        : Character(name_, health_), CanCastSpells(mana_),
          spellDamage(damage_) {};

    void attack(Character *target) override;
    void castSpell(Character *target) override;
};

class BattleMage : public Character, public CanCastSpells, public CanUseMelee {
  protected:
    int meleeDmg;
    int spellDmg;

  public:
    BattleMage(const std::string &name, int health_ = 100, int mana_ = 100,
               int meleeDamage_ = 10, int spellDmg_ = 15)
        : Character(name, health_), CanCastSpells(mana_), CanUseMelee(),
          meleeDmg(meleeDamage_), spellDmg(spellDmg_) {};

    void castSpell(Character *target) override;
    void performMeleeAttack(Character *target) override;
    void attack(Character *target) override;
};

class Rogue : public Character, public CanUseMelee {

  protected:
    int basicAttackDamage;
    int backstabDamage;

  public:
    Rogue(const std::string &name_, int health_ = 90, int bsattack_ = 12,
          int backDmg_ = 30)
        : Character(name_, health_), basicAttackDamage(bsattack_),
          backstabDamage(backDmg_) {};

    void backstab(Character *target);
    void performMeleeAttack(Character *target) override;
    void attack(Character *target) override;
};