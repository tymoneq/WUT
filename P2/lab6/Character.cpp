#include "Character.hpp"

void Warrior::performMeleeAttack(Character *target) {
    if (!target->isAlive()) {
        std::cout << "Przeciwnik nie żyje" << std::endl;
        return;
    }
    int mn_damage = std::min(meleeDamage, target->getHealth());
    std::cout << "Zadano " << mn_damage << "obrażeń" << std::endl;
    target->takeDamage(mn_damage);
}

void Warrior::attack(Character *target) {
    std::cout << "Przygotowanie do ataku: " << std::endl;
    performMeleeAttack(target);
}

void Mage::castSpell(Character *target) {
    if (!target->isAlive()) {
        std::cout << "Przeciwnik nie żyje" << std::endl;
        return;
    }
    int damageDealt = spellDamage;
    Warrior *warriorTarget = dynamic_cast<Warrior *>(target);
    CanUseMelee *meleeTarget = dynamic_cast<CanUseMelee *>(target);

    if (warriorTarget || meleeTarget) {
        damageDealt += 10;
        std::cout << "Dodatkowe obrażenia" << std::endl;
    }

    useMana(10);
    std::cout << name << " blasts " << target->getName() << " for "
              << damageDealt << " magic damage!" << std::endl;
    target->takeDamage(damageDealt);
}

void Mage::attack(Character *target) {
    std::cout << "Przygotowanie do ataku " << std::endl;
    try {
        castSpell(target);
    } catch (const NoManaException &e) {
        std::cerr << name << " failed to cast spell: " << e.what() << std::endl;
    }
}

void BattleMage::attack(Character *target) {
    if (!target || !target->isAlive()) {
        std::cout << "Przeciwnik nie żyje" << std::endl;
        return;
    }

    if (rand() % 2 == 0) {

        try {
            castSpell(target);
        } catch (const NoManaException &e) {
            std::cerr << name << " couldn't cast spell: " << e.what()
                      << std::endl;
            std::cout << name << " resorts to a basic melee attack."
                      << std::endl;
            performMeleeAttack(target);
        }
    } else {
        performMeleeAttack(target);
    }
}

void BattleMage::castSpell(Character *target) {

    if (!target->isAlive()) {
        std::cout << "Przeciwnik nie żyje" << std::endl;
        return;
    }
    int damageDealt = spellDmg;
    useMana(8);
    std::cout << name << " blasts " << target->getName() << " for "
              << damageDealt << " magic damage!" << std::endl;
    target->takeDamage(damageDealt);
}

void BattleMage::performMeleeAttack(Character *target) {
    if (!target->isAlive()) {
        std::cout << "Przeciwnik nie żyje" << std::endl;
        return;
    }
    int mn_damage = std::min(meleeDmg, target->getHealth());
    std::cout << "Zadano " << mn_damage << "obrażeń" << std::endl;
    target->takeDamage(mn_damage);
}
void Rogue::attack(Character *target) {
    if (!target || !target->isAlive()) {
        std::cout << name
                  << " attacks but the target is invalid or already defeated."
                  << std::endl;
        return;
    }
    std::cout << name << " attempts a quick strike on " << target->getName()
              << "." << std::endl;
    if (rand() % 2 == 0)
        performMeleeAttack(target);
    else
        backstab(target);
}

void Rogue::performMeleeAttack(Character *target) {
    if (!target || !target->isAlive())
        return;
    int damageDealt = basicAttackDamage;
    std::cout << name << " hits " << target->getName() << " for " << damageDealt
              << " physical damage!" << std::endl;
    target->takeDamage(damageDealt);
}

void Rogue::backstab(Character *target) {

    if (!target || !target->isAlive()) {
        std::cout << name
                  << " tries to backstab but the target is invalid or already "
                     "defeated."
                  << std::endl;
        return;
    }

    std::cout << name << " attempts a backstab on " << target->getName() << "."
              << std::endl;

    if (typeid(*target) != typeid(Mage) &&
        typeid(*target) != typeid(BattleMage) &&
        dynamic_cast<CanCastSpells *>(target) == nullptr) {
        int damageDealt = backstabDamage;
        std::cout << name << " successfully backstabs " << target->getName()
                  << " for " << damageDealt << " massive damage!" << std::endl;
        target->takeDamage(damageDealt);
    } else {
        std::cout << name << "'s backstab failed against a magic-user!"
                  << std::endl;
    }
}