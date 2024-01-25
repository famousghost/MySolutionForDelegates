#pragma once
#include "Delegates.h"
#include "ICharacter.h"
#include <functional>

class CharacterManager
{
public:

    static CharacterManager* Instance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new CharacterManager();
        }
        return m_instance;
    }

    void Update();

    //Old wrong solution
    DelegateMethod<void(ICharacter::*)()> UpdateCharacters;

    //New best solution
    Delegate<void()> UpdateCharactersDelegate;
private:

    CharacterManager()
    {
    }

    static CharacterManager* m_instance;
};
