#include "_Thread.h"

void
Thread_Manager::Perform_Thread_Check()
{
    for(auto it = _threadMap.begin(); it != _threadMap.end(); it++)
    {
        IThread * _IThread = GetThread(it->first);

        this->CheckTimeOut(_IThread);
        this->CheckOverRun(_IThread);
    }
}

void Thread_Manager::CheckTimeOut(IThread * _IThread)
{
    IThreadEntity *_IThradEntity =  _IThread->getIThreadEntity();

    if(_IThradEntity->getTaskRunTimeLimitSecond() < (_IThradEntity->getTaskEndTime() - _IThradEntity->getTaskStartTime()))
    {
        // TODO LOG -> mevcut taskRuntime = asim zamani bildirisi
        if(_IThradEntity->getIsAutoRestart())
        {
            // TODO LOG -> thread sonlandirme bildirisi
            _IThread->Restart();
        }
    }
    else
    {
        // TODO LOG -> mevcut taskRuntime
    }
}


void Thread_Manager::CheckOverRun(IThread * _IThread)
{
    IThreadEntity *_IThradEntity =  _IThread->getIThreadEntity();

    if((0 != _IThradEntity->getTaskWorkCountLimit()) && (_IThradEntity->getTaskWorkCountLimit() < _IThradEntity->getTaskWorkCount()))
    {
        // TODO LOG -> mevcut taskWorkCount = asimi bildir
        if(_IThradEntity->getIsAutoRestart())
        {
            // TODO LOG -> thread sonlandirme bildirisi
            _IThread->Restart();
        }
    }
    else
    {
        // TODO LOG -> mevcut taskWorkCount
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

        try
        {
            this->_IThreadEntity->runTask();
        }
        catch (...)
        {
            //TODO LOG cerr << "Thread[" << _threadEntity._name << "] execution error!" << endl;
        }

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

void Thread::Restart()
{
    this->Stop();
    this->Kill(); // TODO bunu yapmak belki thread sınıfı icin problem yaratabilir tekrar olusturmak gerekebilir.
    this->Start();
};

void Thread::Kill()
{
    if (this->_IThreadEntity->getThread().joinable())
    {
        this->_IThreadEntity->getThread().detach();
        this->_IThreadEntity->getThread().~thread();
    }
}

IThreadEntity * Thread::getIThreadEntity()
{
    return this->_IThreadEntity;
}

IThread * Thread_Manager::GetThread(const string& thread_name)
{
    if (_threadMap.find(thread_name) != _threadMap.end())
    {
        //return _threadMap[thread_name].get();
    }
    return nullptr;
}