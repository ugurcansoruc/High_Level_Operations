#include "_Thread.h"

template<typename Callable, typename... Args>
void Thread<Callable, Args...>::Thread_Function()
{
    while (this->_status)
    {
        std::apply(this->_threadEntity._function, this->_threadEntity._arguments);
        this_thread::sleep_for(chrono::microseconds(ONESECONDUS / this->_threadEntity._frequence));
    }
}

IThread * Thread_Manager::GetThread(const string& thread_name)
{
    if (_thread_map.find(thread_name) != _thread_map.end())
    {
        return _thread_map[thread_name].get();
    }
    return nullptr;
}