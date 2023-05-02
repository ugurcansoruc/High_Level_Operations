#ifndef THREAD_OPERATIONS__THREAD_H__
#define THREAD_OPERATIONS__THREAD_H__

#include <iostream>
#include <thread>
#include <map>
#include <typeinfo>
#include <chrono>
#include <_Variable.h>

#define ONESECONDUS 1000000

using namespace std;

class IThreadEntity
{
public:
    virtual thread& getThread() = 0;
    virtual void setThread(thread&& thread)= 0;
    virtual bool getStatus() = 0;
    virtual void setStatus(bool status)= 0;
    virtual bool getIsOnceRun() = 0;
    virtual void setIsOnceRun(bool isOnceRun)= 0;
    virtual bool getIsAutoRestart() = 0;
    virtual void setIsAutoRestart(bool isAutoRestart)= 0;
    virtual uint64_t getTaskStartTime() = 0;
    virtual void setTaskStartTime(uint64_t taskStartTime)= 0;
    virtual uint64_t getTaskEndTime() = 0;
    virtual void setTaskEndTime(uint64_t taskEndTime)= 0;
    virtual uint64_t getFrequence() = 0;
    virtual void setFrequence(uint64_t frequence)= 0;
    virtual uint64_t getTaskWorkCount() = 0;
    virtual void increaseTaskWorkCount(int16_t count)= 0;
    virtual void setTaskWorkCount(int16_t count) = 0;
    virtual uint64_t getTaskRunTimeLimitSecond() = 0;
    virtual void setTaskRunTimeLimitSecond(uint64_t taskRunTimeLimitSecond)= 0;
    virtual uint64_t getTaskWorkCountLimit() = 0;
    virtual void setTaskWorkCountLimit(uint64_t taskWorkCountLimit)= 0;
    virtual void runTask() = 0;
    virtual ~IThreadEntity() {}
};

template<typename Callable, typename... Args>
class ThreadEntity: public IThreadEntity
{
private:
    string _name;
    Callable _function;
    tuple<Args...> _arguments;
    thread _thread;
    bool _isOnceRun;
    bool _isAutoRestart;
    bool _status;
    uint64_t _frequence;
    uint64_t _taskStartTime;
    uint64_t _taskEndTime;
    uint64_t _taskWorkCount;
    uint64_t _taskRunTimeLimitSecond;
    uint64_t _taskWorkCountLimit;
public:
    ThreadEntity(string name, Callable function, tuple<Args...> arguments) : _name(name), _function(function), _arguments(arguments)
    {
        this->_frequence = 1;
        this->_isOnceRun = false;
        this->_isAutoRestart = false;
        this->_status = false;
        this->_taskStartTime = 0;
        this->_taskEndTime = 0;
        this->_taskWorkCount = 0;
        this->_taskRunTimeLimitSecond = 10;
        this->_taskWorkCountLimit = 0;
    }

    thread& getThread() override{
        return this->_thread;
    };

    void setThread(thread&& thread) override{
        this->_thread = move(thread);
    };
    bool getStatus() override {
        return this->_status;
    };
    void setStatus(bool status) override{
        this->_status = status;
    };
    bool getIsOnceRun() override {
        return this->_isOnceRun;
    };
    void setIsOnceRun(bool isOnceRun) override{
        this->_isOnceRun = isOnceRun;
    };

    bool getIsAutoRestart() override{
        return this->_isAutoRestart;
    };
    void setIsAutoRestart(bool isAutoRestart) override{
        this->_isAutoRestart = isAutoRestart;
    };
    uint64_t getTaskStartTime() override{
        return this->_taskStartTime;
    };
    void setTaskStartTime(uint64_t taskStartTime) override{
        this->_taskStartTime = taskStartTime;
    };
    uint64_t getTaskEndTime() override{
        return this->_taskEndTime;
    };
    void setTaskEndTime(uint64_t taskEndTime) override{
        this->_taskEndTime = taskEndTime;
    };
    uint64_t getFrequence() override{
        return this->_frequence;
    };
    void setFrequence(uint64_t frequence) override{
        this->_frequence = frequence;
    };
    uint64_t getTaskWorkCount() override{
        return this->_taskWorkCount;
    };
    void increaseTaskWorkCount(int16_t count) override{
        this->_taskWorkCount += count;
    };
    void setTaskWorkCount(int16_t count) override{
        this->_taskWorkCount = count;
    };
    uint64_t getTaskRunTimeLimitSecond() override{
        return this->_taskRunTimeLimitSecond;
    };
    void setTaskRunTimeLimitSecond(uint64_t taskRunTimeLimitSecond) override{
        this->_taskRunTimeLimitSecond = taskRunTimeLimitSecond;
    };
    uint64_t getTaskWorkCountLimit() override{
        return this->_taskWorkCountLimit;
    };
    void setTaskWorkCountLimit(uint64_t taskWorkCountLimit) override{
        this->_taskWorkCountLimit = taskWorkCountLimit;
    };

    void runTask() override{
        apply(this->_function, this->_arguments);
    }
};

class IThread
{
public:
    virtual void Start() = 0;
    virtual void Stop() = 0;
    virtual void Restart() = 0;
    virtual void Kill() = 0;
    virtual void Reset() = 0;
    virtual IThreadEntity * getIThreadEntity() = 0;
    virtual ~IThread() {}
};

class Thread : public IThread
{

private:
    IThreadEntity * _IThreadEntity;

private:
    void Thread_Function();
public:
    Thread(IThreadEntity * IThreadEntity): _IThreadEntity(IThreadEntity){}

    void Start() override;

    void Stop() override;

    void Restart() override;

    void Kill() override;

    void Reset() override;

    IThreadEntity * getIThreadEntity() override;
};

class Thread_Manager
{
private:
    map<string, unique_ptr<Thread>> _threadMap;
    Variable_Manager variable_manager; //TODO daha sonra implemente edilecektir.
private:
    void Perform_Thread_Check();
    void CheckTimeOut(IThread * _IThread);
    void CheckOverRun(IThread * _IThread);
public:
    Thread_Manager()
    {
        this->Create_Thread("_Perform_Thread_Check_", &Thread_Manager::Perform_Thread_Check, this);
        IThread *_IThread  = this->GetThread("_Perform_Thread_Check_");
        IThreadEntity *_IThreadEntity  = _IThread->getIThreadEntity();
        _IThreadEntity->setTaskWorkCountLimit(10);
        _IThreadEntity->setIsAutoRestart(true);
        _IThread->Start();
    };

    template<typename Callable, typename... Args>
    IThread * Create_Thread(const std::string& thread_name, Callable function, Args... args)
    {
        //variable_manager.Check_Variable(new String_Controller(thread_name)); // TODO her defasında bir string controller oluşturulmasına gerek yok!!!
        //TODO bu islem thread gelen isimde birs thread olup olmamasına gore gerceklestirilmelidir.
        this->_threadMap[thread_name] = make_unique<Thread>(Thread(new ThreadEntity<decltype(function), decltype(args)...>(thread_name, function, make_tuple(args...))));

        return GetThread(thread_name);
    }

    IThread * GetThread(const string& thread_name);
};

#endif // !THREAD_OPERATIONS__THREAD_H__
