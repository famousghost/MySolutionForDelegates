#pragma once
#include "Delegates.h"
#include <vector>
#include <iostream>

template<typename Type>
class WorkerManager
{
public:

    Delegate<void()> UpdateCustomerInfo;
    Delegate<int(int, int)> retUpdate;
    
    void Update();
};

template<typename Type>
inline void WorkerManager<Type>::Update()
{
    UpdateCustomerInfo.Invoke();
    auto l_values = retUpdate.InvokeRet(10, 20);
    for (const auto& value : l_values)
    {
        std::cout << "Return Value: " << value << std::endl;
    }
}
