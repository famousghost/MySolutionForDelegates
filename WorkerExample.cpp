#include "WorkerExample.h"
#include "Worker.h"
#include <iostream>

void func()
{
    std::cout << "func()" << std::endl;
}

void func2()
{
    std::cout << "func2()" << std::endl;
}

void func3()
{
    std::cout << "func3()" << std::endl;
}

int Result(int x)
{
    return 10 * x;
}

int Result2(int x)
{
    return 20 * x;
}

void WorkerExample::Update()
{
    WorkerManager<Worker> manager;

    manager.funcUpdateClinetsInformation.Register(func);
    manager.funcUpdateClinetsInformation.Register(func2);
    manager.funcUpdateClinetsInformation.Register(func3);
    manager.checkFunctionDelegate.Register(Result);
    manager.checkFunctionDelegate.Register(Result2);

    Worker worker1(1);

    worker1.RegisterAtWork(manager);

    Worker worker2(2);

    worker2.RegisterAtWork(manager);

    Worker worker3(3);

    worker3.RegisterAtWork(manager);

    manager.Update();

    manager.funcUpdateClinetsInformation.Unregister(func);

    worker1.UnRegisterFromWork(manager);

    manager.checkFunctionDelegate.Unregister(Result2);

    std::cout << "---------------------------" << std::endl;

    manager.Update();

    manager.funcUpdateClinetsInformation.Unregister(func2);
    manager.funcUpdateClinetsInformation.Unregister(func3);
}
