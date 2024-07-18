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
    characterManager->UpdateCharactersDelegate.REGISTER_METHOD(this, &Worrior::PrintType);
    characterManager->SumDelegate.REGISTER_METHOD(this, &Worrior::Sum);
}

void Worrior::Unregister()
{
    auto* characterManager = CharacterManager::Instance();
    characterManager->UpdateCharactersDelegate.UNREGISTER_METHOD(this, &Worrior::PrintType);
    characterManager->SumDelegate.UNREGISTER_METHOD(this, &Worrior::Sum);
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
