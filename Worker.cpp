#include "Worker.h"

Worker::Worker(int id)
    :workerID(id)
{}

void Worker::RegisterAtWork(WorkerManager<Worker>& manager)
{
    manager.UpdateCustomerInfo.REGISTER_METHOD(this, &Worker::DoWork);
    manager.UpdateCustomerInfo.REGISTER_METHOD(this, &Worker::DoBreak);
}

void Worker::UnRegisterFromWork(WorkerManager<Worker>& manager)
{
    manager.UpdateCustomerInfo.UNREGISTER_METHOD(this, &Worker::DoWork);
    manager.UpdateCustomerInfo.UNREGISTER_METHOD(this, &Worker::DoBreak);
}

void Worker::DoWork()
{
    std::cout << "Im working: workerId = " << workerID << std::endl;
}

void Worker::DoBreak()
{
    std::cout << "Im on break: workerId = " << workerID << std::endl;
}
