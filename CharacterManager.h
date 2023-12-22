#pragma once
#include "Delegates.h"

template<typename Type>
class CharacterManager
{
public:

	static CharacterManager<Type>* Instance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new CharacterManager<Type>();
		}
		return m_instance;
	}

	void Update();
	
	DelegateMethod<Type*, void(Type::*)()> UpdateCharacters;


private:

	CharacterManager()
	{
	}

	static CharacterManager<Type>* m_instance;

};

template<typename Type>
CharacterManager<Type>* CharacterManager<Type>::m_instance = nullptr;

template<typename Type>
inline void CharacterManager<Type>::Update()
{
	UpdateCharacters.Invoke();
}
