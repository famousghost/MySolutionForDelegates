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
}

void Warlock::Unregister()
{
	auto* characterManager = CharacterManager::Instance();
	characterManager->UpdateCharacters.Unregister(this, &ICharacter::PrintType);
}

void Warlock::PrintType()
{
	std::string type = m_type == HeroType::Melee ? "Melee" : "Range";
	std::cout << "Warlock::PrintType = " << type << "\n";
}