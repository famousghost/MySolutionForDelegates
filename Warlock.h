#pragma once
#include "ICharacter.h"
#include <iostream>

class Warlock : public ICharacter
{
public:
	Warlock(HeroType type);

	virtual void Register() override;

	virtual void Unregister() override;

	virtual void PrintType() override;
private:
	
	HeroType m_type;

};

