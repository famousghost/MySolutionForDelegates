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

int getMul(int x, int y)
{
    return x * y;
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

struct X
{
    void operator()()
    {
        std::cout << "Functor::X()\n";
    }
};

void WorkerExample::Update()
{
    X x;
    WorkerManager<Worker> manager;

    manager.UpdateCustomerInfo.REGISTER_FUNC(func);
    manager.UpdateCustomerInfo.REGISTER_FUNC(func2);
    manager.UpdateCustomerInfo.REGISTER_FUNC(func3);
    manager.UpdateCustomerInfo.REGISTER_FUNC(A::f);
    manager.UpdateCustomerInfo.REGISTER_FUNC(B::f);
    manager.UpdateCustomerInfo.REGISTER_FUNC(C::f);
    manager.retUpdate.REGISTER_FUNC(getMul);
    auto lambda = []() {std::cout << "Lambda Test\n"; };
    manager.UpdateCustomerInfo.REGISTER_FUNC(lambda);
    manager.UpdateCustomerInfo.REGISTER_METHOD(&x, &X::operator());
    Worker worker1(1);

    worker1.RegisterAtWork(manager);

    Worker worker2(2);

    worker2.RegisterAtWork(manager);

    Worker worker3(3);

    worker3.RegisterAtWork(manager);

    manager.Update();

    manager.UpdateCustomerInfo.UNREGISTER_FUNC(func);
    manager.UpdateCustomerInfo.UNREGISTER_FUNC(B::f);
    manager.UpdateCustomerInfo.UNREGISTER_FUNC(lambda);
    manager.UpdateCustomerInfo.UNREGISTER_METHOD(&x, &X::operator());
        
    worker2.UnRegisterFromWork(manager);

    std::cout << "---------------------------" << std::endl;

    manager.Update();

    manager.UpdateCustomerInfo.UNREGISTER_FUNC(func2);
    manager.UpdateCustomerInfo.UNREGISTER_FUNC(func3);

    worker1.UnRegisterFromWork(manager);

    std::cout << "---------------------------" << std::endl;

    manager.Update();
}
