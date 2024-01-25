#pragma once
#include "ICharacter.h"
#include <string>

class Worrior : public ICharacter
{
public:
	Worrior() = default;

	Worrior(const std::string& name, float hp, float mp, float attackPower, float damageReduction, HeroType type);

	virtual void Register() override;

	virtual void Unregister() override;

	virtual void PrintType() override;

private:
	float AttackPower;
	float HP;
	float MP;
	float DamageReduction;
	HeroType Type;
	std::string m_name;
};

