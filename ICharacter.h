#pragma once
enum class HeroType
{
	Melee = 0,
	Range = 1
};

class ICharacter
{
public:

	virtual void Register() = 0;
	virtual void Unregister() = 0;

	virtual void PrintType() = 0;
	
};

