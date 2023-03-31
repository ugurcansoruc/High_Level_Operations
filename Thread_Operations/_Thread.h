#ifndef THREAD_OPERATIONS__THREAD_H__
#define THREAD_OPERATIONS__THREAD_H__

#include <iostream>
#include <thread>
#include <map>
#include <typeinfo>
#include <chrono>
#include "_IThread.h"
#include <_Variable.h>

#define ONESECONDUS 1000000

using namespace std;

template<typename Callable, typename... Args>
class Thread : public IThread
{
private:
    class ThreadEntity
    {
    public:
        string _name;
        Callable _function;
        tuple<Args...> _arguments;
        thread _thread;

        int32_t _frequence;
        bool _isOnceRun;
        bool _isAutoRestart;
        bool _status;

        uint64_t _taskStartTime;
        uint64_t _taskEndTime;
        uint64_t _taskWorkCount;
    };

public:
    Thread(string name, Callable func, tuple<Args...> args)
    {
        _threadEntity._name = name;
        _threadEntity._function = func;
        _threadEntity._arguments = args;
        _threadEntity._frequence = 1;
        _threadEntity._isOnceRun = false;
        _threadEntity._isAutoRestart = false;
        _threadEntity._status = false;
        _threadEntity._taskStartTime = 0;
        _threadEntity._taskEndTime = 0;
        _threadEntity._taskWorkCount = 0;
    };

private:
    ThreadEntity _threadEntity;

private:
    void Thread_Function()
    {
        while (this->_threadEntity._status)
        {
            this->_threadEntity._taskStartTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();

            std::apply(this->_threadEntity._function, this->_threadEntity._arguments);

            this->_threadEntity._taskEndTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
            this->_threadEntity._taskWorkCount++;

            this_thread::sleep_for(chrono::microseconds(ONESECONDUS / this->_threadEntity._frequence));
        }
    };

public:
    void Start() override
    {
        if (!_threadEntity._status)
        {
            _threadEntity._status = true;
            _threadEntity._thread = thread(&Thread::Thread_Function, this);
        }
    };

    void Stop() override
    {
        _threadEntity._status = false;
        if (_threadEntity._thread.joinable())
            _threadEntity._thread.join();
    };

    void Kill() override
    {
        if (_threadEntity._thread.joinable())
        {
            _threadEntity._thread.detach();
            _threadEntity._thread.~thread();
        }
    };
};

class Thread_Manager
{
private:
    map<string, unique_ptr<IThread>> _thread_map;
    Variable_Manager variable_manager;
public:
    template<typename Callable, typename... Args>
    void Create_Thread(const std::string& thread_name, Callable function, Args... args)
    {
        //variable_manager.Check_Variable(new String_Controller(thread_name)); // TODO her defasında bir string controller oluşturulmasına gerek yok!!!
        //TODO thread olusturma durumu kontrol et!!
        _thread_map[thread_name] = make_unique<Thread<decltype(function), decltype(args)...>>(thread_name, function, make_tuple(args...));
    }

    IThread* GetThread(const string& thread_name);
};

#endif // !THREAD_OPERATIONS__THREAD_H__
