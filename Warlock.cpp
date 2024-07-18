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
    characterManager->UpdateCharactersDelegate.REGISTER_METHOD(this, &Warlock::PrintType);
    characterManager->UpdateCharactersDelegate.REGISTER_METHOD(this, &Warlock::PrintType2);
    characterManager->SumDelegate.REGISTER_METHOD(this, &Warlock::Sum);
}

void Warlock::Unregister()
{
    auto* characterManager = CharacterManager::Instance();
    characterManager->UpdateCharactersDelegate.UNREGISTER_METHOD(this, &Warlock::PrintType);
    characterManager->UpdateCharactersDelegate.UNREGISTER_METHOD(this, &Warlock::PrintType2);
    characterManager->SumDelegate.UNREGISTER_METHOD(this, &Warlock::Sum);
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

void Warlock::Sum(int x, int y)
{
    std::cout << "(" << m_name  << "): " << "Warlock::Sum() " << x + y << std::endl;
}
