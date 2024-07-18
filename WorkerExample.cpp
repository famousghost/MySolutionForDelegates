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

namespace A
{
    void f()
    {
        std::cout << "A::f()\n";
    }
}

namespace B
{
    void f()
    {
        std::cout << "B::f()\n";
    }
}

namespace C
{
    void f()
    {
        std::cout << "C::f()\n";
    }
}

void WorkerExample::Update()
{
    WorkerManager<Worker> manager;

    manager.UpdateCustomerInfo.REGISTER_FUNC(func);
    manager.UpdateCustomerInfo.REGISTER_FUNC(func2);
    manager.UpdateCustomerInfo.REGISTER_FUNC(func3);
    manager.UpdateCustomerInfo.REGISTER_FUNC(A::f);
    manager.UpdateCustomerInfo.REGISTER_FUNC(B::f);
    manager.UpdateCustomerInfo.REGISTER_FUNC(C::f);

    Worker worker1(1);

    worker1.RegisterAtWork(manager);

    Worker worker2(2);

    worker2.RegisterAtWork(manager);

    Worker worker3(3);

    worker3.RegisterAtWork(manager);

    manager.Update();

    manager.UpdateCustomerInfo.UNREGISTER_FUNC(func);
    manager.UpdateCustomerInfo.UNREGISTER_FUNC(B::f);

    worker2.UnRegisterFromWork(manager);

    std::cout << "---------------------------" << std::endl;

    manager.Update();

    manager.UpdateCustomerInfo.UNREGISTER_FUNC(func2);
    manager.UpdateCustomerInfo.UNREGISTER_FUNC(func3);

    worker1.UnRegisterFromWork(manager);

    std::cout << "---------------------------" << std::endl;

    manager.Update();
}
