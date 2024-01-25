#include "Worrior.h"
#include "CharacterManager.h"
#include <string>

Worrior::Worrior(float hp, float mp, float attackPower, float damageReduction, HeroType type)
    :HP(hp),
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
}

void Worrior::Unregister()
{
    auto* characterManager = CharacterManager::Instance();
    characterManager->UpdateCharacters.Unregister(this, &ICharacter::PrintType);
    characterManager->UpdateCharactersDelegate.Unregister(&Worrior::PrintType);
}

void Worrior::PrintType()
{
    std::string type = Type == HeroType::Melee ? "Melee" : "Range";
    std::cout << "Worrior::PrintType = " << type << "\n";
}