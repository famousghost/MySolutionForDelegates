#pragma once
#include "WorkerManager.h"
#include <iostream>

class Worker
{
public:

    Worker() = default;

    Worker(int id);

    void RegisterAtWork(WorkerManager<Worker>& manager);

    void UnRegisterFromWork(WorkerManager<Worker>& manager);

    void DoWork();

    void DoBreak();

    int GetSum(int x, int y);
private:
    int workerID;
};