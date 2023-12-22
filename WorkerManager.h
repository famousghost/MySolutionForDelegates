#pragma once
#include "Delegates.h"
#include <vector>
#include <iostream>

template<typename Type>
class WorkerManager
{
public:

    DelegateMethod< void(Type::*)()> classUpdateClinetsInformation;

    DelegateFunc<int(*)(int)> checkFunctionDelegate;

    DelegateFunc<void(*)()> funcUpdateClinetsInformation;

    DelegateMethod<int(Type::*)(int)> checkMethodDelegate;

    void Update();
};

template<typename Type>
inline void WorkerManager<Type>::Update()
{
    classUpdateClinetsInformation.Invoke();
    funcUpdateClinetsInformation.Invoke();
    std::vector<int> results = checkMethodDelegate.InvokeRet(3);

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
