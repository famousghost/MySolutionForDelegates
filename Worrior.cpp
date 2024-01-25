#include "Worrior.h"
#include "CharacterManager.h"
#include <iostream>

Worrior::Worrior(const std::string& name, float hp, float mp, float attackPower, float damageReduction, HeroType type)
    :m_name(name),
    HP(hp),
    MP(mp),
    AttackPower(attackPower),
    DamageReduction(damageReduction),
    Type(type)
{}

void Worrior::Register()
{
    auto* characterManager = CharacterManager::Instance();
    characterManager->UpdateCharacters.Register(this, &ICharacter::PrintType);
    characterManager->UpdateCharactersDelegate.Register(this, &Worrior::PrintType);
    characterManager->SumDelegate.Register(this, &Worrior::Sum);
}

void Worrior::Unregister()
{
    auto* characterManager = CharacterManager::Instance();
    characterManager->UpdateCharacters.Unregister(this, &ICharacter::PrintType);
    characterManager->UpdateCharactersDelegate.Unregister(this, &Worrior::PrintType);
    characterManager->SumDelegate.Unregister(this, &Worrior::Sum);
}

void Worrior::PrintType()
{
    std::string type = Type == HeroType::Melee ? "Melee" : "Range";
    std::cout << "(" << m_name << "): " << "Worrior::PrintType = " << type << "\n";
}

void Worrior::Sum(int x, int y)
{
    std::cout << "(" << m_name << "): " << "Worrior::Sum() " << x + y << std::endl;
}
