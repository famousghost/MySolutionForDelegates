#pragma once
#include "ICharacter.h"
#include <string>

class Warlock : public ICharacter
{
public:
    Warlock(const std::string& name, HeroType type);

    virtual void Register() override;

    virtual void Unregister() override;

    virtual void PrintType() override;

    void PrintType2();

    void Sum(int x, int y);
private:

    HeroType m_type;
    std::string m_name;
};
