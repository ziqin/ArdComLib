#ifndef Worker_h
#define Worker_h

#include <Arduino.h>
#if __cplusplus > 199711L // C++ 11+
#include "functional-vlpp/src/functional-vlpp.h"
#endif

namespace ACL {

class Worker {
public:
    Worker(const String& name):
        theName(name) {}
    virtual ~Worker() {}
    const String& name() const {
        return theName;
    }
private:
    String theName;
};

#if __cplusplus > 199711L // C++ 11+: support lambda capture
class TaskWorker final: public Worker {
public:
    TaskWorker(const String& name, vl::Func<void()> func):
        Worker(name),
        func(func) {}
    void work() const {
        func();
    }
private:
    vl::Func<void()> func;
};
#else
class TaskWorker final: public Worker {
public:
    TaskWorker(const String& name, void (*func)()):
        Worker(name),
        func(func) {}
    void work() const {
        func();
    }
private:
    void (*func)();
};
#endif

}

#endif // Worker_h