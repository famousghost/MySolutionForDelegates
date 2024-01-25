#include "CharacterManager.h"

CharacterManager* CharacterManager::m_instance = nullptr;

void CharacterManager::Update()
{
    //Previous wrong solution
    //UpdateCharacters.Invoke();

    //New the best solution
    UpdateCharactersDelegate.Invoke();
}