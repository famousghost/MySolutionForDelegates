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

    //New best solution
    Delegate<void()> UpdateCharactersDelegate;

    Delegate<void(int, int)> SumDelegate;
private:

    CharacterManager()
    {
    }

    static CharacterManager* m_instance;
};
