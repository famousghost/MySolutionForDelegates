#include <iostream>
#include "WorkerExample.h"
#include "CharacterManager.h"
#include "Worrior.h"
#include "Warlock.h"

#ifndef WORKER_EXAMPLE
#define WORKER_EXAMPLE
#endif

#ifndef CHARACTER_EXAMPLE
#define CHARACTER_EXAMPLE
#endif

using namespace std;

int main() {
    //********* WORKER EXAMPLE *********//
#ifdef WORKER_EXAMPLE
    std::cout << "***************************************************\nWORKER_EXAMPLE:" << std::endl;
    WorkerExample workerExample;
    workerExample.Update();
#endif
    //********* WORKER EXAMPLE *********//

    //********* CHARACTER EXAMPLE *********//
#ifdef CHARACTER_EXAMPLE
    std::cout << "***************************************************\n\nCHARACTER_EXAMPLE:" << std::endl;
    Worrior worrior("Worrior1", 100.0f, 100.0f, 20.0f, 0.2f, HeroType::Melee);
    Worrior worrior2("Worrior2", 100.0f, 10.0f, 50.0f, 0.2f, HeroType::Melee);
    Warlock warlock("warlock1", HeroType::Range);
    Warlock warlock2("warlock2", HeroType::Range);

    worrior.Register();
    worrior2.Register();
    warlock.Register();
    warlock2.Register();

    CharacterManager::Instance()->Update();

    worrior.Unregister();
    warlock2.Unregister();

    std::cout << "-------------------------------" << std::endl;

    //Unresgister isnt working properly Fix it
    CharacterManager::Instance()->Update();
#endif
    //********* CHARACTER EXAMPLE *********//
    return 0;
}