#include "_Thread.h"

void
Thread_Manager::Perform_Thread_Check()
{
    for(auto it = _threadMap.begin(); it != _threadMap.end(); it++)
    {
        IThread * _IThread = GetThread(it->first);
        _IThread->Start();
    }
}

void Thread::Start()
{
    if (!_IThreadEntity->getStatus())
    {
        _IThreadEntity->setStatus(true);
        _IThreadEntity->setThread(thread(&Thread::Thread_Function, this));
    }
};


void Thread::Thread_Function()
{

    while (this->_IThreadEntity->getStatus())
    {
        if (this->_IThreadEntity->getIsOnceRun())
        {
            this->_IThreadEntity->setStatus(false);
        }

        this->_IThreadEntity->setTaskStartTime(chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
/*
        try
        {
            apply(_threadEntity._function, _threadEntity._arguments);
        }
        catch (...)
        {
            //TODO LOG cerr << "Thread[" << _threadEntity._name << "] execution error!" << endl;
        }*/

        this->_IThreadEntity->setTaskEndTime(chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
        this->_IThreadEntity->increaseTaskWorkCount();

        this_thread::sleep_for(chrono::microseconds(ONESECONDUS / this->_IThreadEntity->getFrequence()));
    }
};

void Thread::Stop()
{
    this->_IThreadEntity->setStatus(false);

    if (this->_IThreadEntity->getThread().joinable())
    {
        this->_IThreadEntity->getThread().join();
    }
};

void Thread::Kill()
{
    if (this->_IThreadEntity->getThread().joinable())
    {
        this->_IThreadEntity->getThread().detach();
        this->_IThreadEntity->getThread().~thread();
    }
}

IThread * Thread_Manager::GetThread(const string& thread_name)
{
    if (_threadMap.find(thread_name) != _threadMap.end())
    {
        //return _threadMap[thread_name].get();
    }
    return nullptr;
}