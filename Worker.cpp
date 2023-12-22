#include "Worker.h"

Worker::Worker(int id)
    :workerID(id)
{}

int Worker::Result(int x)
{
    return 20 * x;
}

void Worker::RegisterAtWork(WorkerManager<Worker>& manager)
{
    manager.classUpdateClinetsInformation.Register(this, &Worker::DoWork);
    manager.classUpdateClinetsInformation.Register(this, &Worker::DoBreak);
    manager.checkMethodDelegate.Register(this, &Worker::Result);
}

void Worker::UnRegisterFromWork(WorkerManager<Worker>& manager)
{
    manager.classUpdateClinetsInformation.Unregister(this, &Worker::DoWork);
    manager.classUpdateClinetsInformation.Unregister(this, &Worker::DoBreak);
    manager.checkMethodDelegate.Unregister(this, &Worker::Result);
}

void Worker::DoWork()
{
    std::cout << "Im working: workerId = " << workerID << std::endl;
}

void Worker::DoBreak()
{
    std::cout << "Im on break: workerId = " << workerID << std::endl;
}
