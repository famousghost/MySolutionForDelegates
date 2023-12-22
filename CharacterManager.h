#pragma once
#include "Delegates.h"
#include "ICharacter.h"

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

    DelegateMethod<void(ICharacter::*)()> UpdateCharacters;
private:

    CharacterManager()
    {
    }

    static CharacterManager* m_instance;
};
