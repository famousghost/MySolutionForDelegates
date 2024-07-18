#include "CharacterManager.h"

CharacterManager* CharacterManager::m_instance = nullptr;

void CharacterManager::Update()
{
    //New the best solution
    UpdateCharactersDelegate.Invoke();
    SumDelegate.Invoke(10, 40);
}