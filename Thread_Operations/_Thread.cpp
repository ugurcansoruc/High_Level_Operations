#include "_Thread.h"

IThread * Thread_Manager::GetThread(const string& thread_name)
{
    if (_thread_map.find(thread_name) != _thread_map.end())
    {
        return _thread_map[thread_name].get();
    }
    return nullptr;
}