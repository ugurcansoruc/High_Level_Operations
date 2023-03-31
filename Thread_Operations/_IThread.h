#ifndef HIGH_LEVEL_OPERATIONS__ITHREAD_H
#define HIGH_LEVEL_OPERATIONS__ITHREAD_H

#include <functional>
#include "iostream"

using namespace std;

class IThread
{
public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Kill() = 0;
    virtual ~IThread() {}
};

/*
class IThreadManager
{
public:
    virtual ~IThreadManager() {}
    virtual void Create_Thread(const std::string& thread_name, std::function<void()> function) = 0;
    virtual IThread* GetThread(const std::string& thread_name) = 0;
};*/


#endif //HIGH_LEVEL_OPERATIONS__ITHREAD_H
