#include <iostream>
#include "Delegates.h"

using namespace std;

class Worker;

class Manager
{
public:

    DelegateMethod<Worker*, void(Worker::*)()> classUpdateClinetsInformation;
    DelegateFunc<int(*)(int)> checkFunctionDelegate;

    DelegateFunc<void(*)()> funcUpdateClinetsInformation;
    DelegateMethod<Worker*, int(Worker::*)()> checkMethodDelegate;


    void Update()
    {
        classUpdateClinetsInformation.Invoke();
        funcUpdateClinetsInformation.Invoke();
        std:vector<int> results = checkMethodDelegate.InvokeRet();

        int sum = 0;
        for (int i = 0; i < results.size(); ++i)
        {
            sum += results[i];
        }
        std::cout << "Method Delegate Sum is equal: " << sum << std::endl;

        results = checkFunctionDelegate.InvokeRet(5);

        sum = 0;
        for (int i = 0; i < results.size(); ++i)
        {
            sum += results[i];
        }
        std::cout << "Function Delegate Sum is equal: " << sum << std::endl;
    }
};

class Worker
{
public:

    Worker() = default;

    Worker(int id)
        :workerID(id)
    {}

    int Result()
    {
        return 20;
    }

    void RegisterAtWork(Manager& manager)
    {
        manager.classUpdateClinetsInformation.Register(this, &Worker::DoWork);
        manager.classUpdateClinetsInformation.Register(this, &Worker::DoBreak);
        manager.checkMethodDelegate.Register(this, &Worker::Result);
    }

    void UnRegisterFromWork(Manager& manager)
    {
        manager.classUpdateClinetsInformation.Unregister(this, &Worker::DoWork);
        manager.classUpdateClinetsInformation.Unregister(this, &Worker::DoBreak);
        manager.checkMethodDelegate.Unregister(this, &Worker::Result);
    }

    void DoWork()
    {
        std::cout << "Im working: workerId = " << workerID << std::endl;
    }

    void DoBreak()
    {
        std::cout << "Im on break: workerId = " << workerID << std::endl;
    }
private:
    int workerID;
};

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

int main() {
    Manager manager;

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
    return 0;
}