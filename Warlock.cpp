#include "Warlock.h"
#include "CharacterManager.h"
#include <iostream>

Warlock::Warlock(const std::string& name, HeroType type)
    :m_name(name), m_type(type)
{
}

void Warlock::Register()
{
    auto* characterManager = CharacterManager::Instance();
    characterManager->UpdateCharacters.Register(this, &ICharacter::PrintType);
    characterManager->UpdateCharactersDelegate.Register(this, &Warlock::PrintType);
    characterManager->UpdateCharactersDelegate.Register(this, &Warlock::PrintType2);
}

void Warlock::Unregister()
{
    auto* characterManager = CharacterManager::Instance();
    characterManager->UpdateCharacters.Unregister(this, &ICharacter::PrintType);
    characterManager->UpdateCharactersDelegate.Unregister(this, &Warlock::PrintType);
    characterManager->UpdateCharactersDelegate.Unregister(this, &Warlock::PrintType2);
}

void Warlock::PrintType()
{
    std::string type = m_type == HeroType::Melee ? "Melee" : "Range";
    std::cout << "(" << m_name << "): " << "Warlock::PrintType = " << type << "\n";
}

void Warlock::PrintType2()
{
    std::string type = m_type == HeroType::Melee ? "Melee" : "Range";
    std::cout << "(" << m_name << "): " << "Warlock::PrintType2 = " << type << "\n";
}