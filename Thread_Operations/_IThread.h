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

#endif //HIGH_LEVEL_OPERATIONS__ITHREAD_H
