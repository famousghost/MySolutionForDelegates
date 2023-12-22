#pragma once
#include "WorkerManager.h"
#include <iostream>

class Worker
{
public:

    Worker() = default;

    Worker(int id);

    int Result(int x);

    void RegisterAtWork(WorkerManager<Worker>& manager);

    void UnRegisterFromWork(WorkerManager<Worker>& manager);

    void DoWork();

    void DoBreak();
private:
    int workerID;
};