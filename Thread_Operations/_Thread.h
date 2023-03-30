#ifndef THREAD_OPERATIONS__THREAD_H__
#define THREAD_OPERATIONS__THREAD_H__

#include <iostream>
#include <thread>
#include <_Variable.h>
#include <map>
#include <typeinfo>

#define ONESECONDUS 1000000

using namespace std;

class IThread
{
public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Kill() = 0;
    virtual void run() = 0;
    virtual ~IThread() {}
};

template<typename Callable, typename... Args>
class Thread : public IThread
{
private:
    class ThreadEntity
    {
    public:
        Callable _function;
        tuple<Args...> _arguments;
        thread _thread;
        string _name;
        int32_t _frequence;
        bool _onceRun;
        bool _status;
    };

public:
    Thread(string name, Callable func, tuple<Args...> args)
    {
        _threadEntity._name = name;
        _threadEntity._function = func;
        _threadEntity._arguments = args;
        _threadEntity._frequence = 1;
        _threadEntity._status = false;
    };

private:
    void Thread_Function();
    ThreadEntity _threadEntity;

public:
    void Start() override
    {

    };
    void Stop() override
    {

    };
    void Kill() override
    {

    };

    void run() override
    {
        apply(this->_threadEntity._function, this->_threadEntity._arguments);
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
