#include "Warlock.h"
#include "CharacterManager.h"

Warlock::Warlock(HeroType type)
    :m_type(type)
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
    characterManager->UpdateCharactersDelegate.Unregister(&Warlock::PrintType);
}

void Warlock::PrintType()
{
    std::string type = m_type == HeroType::Melee ? "Melee" : "Range";
    std::cout << "Warlock::PrintType = " << type << "\n";
}

void Warlock::PrintType2()
{
    std::string type = m_type == HeroType::Melee ? "Melee" : "Range";
    std::cout << "Warlock::PrintType2 = " << type << "\n";
}