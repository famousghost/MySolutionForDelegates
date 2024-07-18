#pragma once
#include "Delegates.h"
#include <vector>
#include <iostream>

template<typename Type>
class WorkerManager
{
public:

    Delegate<void()> UpdateCustomerInfo;

    void Update();
};

template<typename Type>
inline void WorkerManager<Type>::Update()
{
    UpdateCustomerInfo.Invoke();
}
