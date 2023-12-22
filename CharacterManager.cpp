#include "CharacterManager.h"

CharacterManager* CharacterManager::m_instance = nullptr;

void CharacterManager::Update()
{
	UpdateCharacters.Invoke();
}