#pragma once
#include <thread>
#include <functional>


/**
 * This class is used as an interface that other tasks should implement in order to 
 * allow them to run a task in a thread and in order to be able to be stopped at any time
 */
class TaskInterface
{   
    private:
    pthread_t _nativeHandle;
    bool _isRunning = false;

    public:
    TaskInterface() {}
    virtual ~TaskInterface() { forceStop(); }
    virtual void runnable() = 0;

    void run()
    {
        _isRunning = true;
        std::thread t = std::thread(std::bind(&TaskInterface::runnable, this));
        _nativeHandle = t.native_handle();
        t.detach();
    }

    void forceStop()
    {
        pthread_cancel(_nativeHandle);
        _isRunning = false;
    }

    bool isRunning()
    {
        return _isRunning;
    }

};