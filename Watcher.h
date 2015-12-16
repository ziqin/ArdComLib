#ifndef Watcher_h
#define Watcher_h

#include <Arduino.h>
#include "../ArduinoJson/include/ArduinoJson/JsonVariant.hpp"
#include "List.h"

namespace ACL {

using ArduinoJson::JsonVariant;

const char * const null = static_cast<const char*>(0);

/// 观察者基类
class Watcher {
public:
    Watcher(const String& name):
        theName(name) {}
    virtual ~Watcher() {}
    virtual JsonVariant value() = 0;
    const String& name() const {
        return theName;
    }
private:
    String theName;
};


/// 用于读取普通的数字信号传感器
class DigitalWatcher: public Watcher {
public:
    DigitalWatcher(const String& name, uint8_t pin):
        Watcher(name), thePin(pin) {
        pinMode(pin, INPUT);
    }
    virtual ~DigitalWatcher() {}
    virtual JsonVariant value() override {
        return JsonVariant(digitalRead(thePin) == HIGH);
    }
protected:
    uint8_t thePin;
};


/// 用于读取普通的模拟信号传感器
class AnalogWatcher: public Watcher {
public:
    AnalogWatcher(const String& name, uint8_t pin):
        Watcher(name), thePin(pin) {}
    virtual ~AnalogWatcher() {}
    virtual JsonVariant value() override {
        return JsonVariant(analogRead(thePin));
    }
protected:
    uint8_t thePin;
};


/// 多次读取模拟传感信号传感器，并取平均值
class AverageWatcher final: public AnalogWatcher {
public:
    AverageWatcher(const String& name, uint8_t pin, unsigned times):
        AnalogWatcher(name, pin), theTimes(times) {}
    JsonVariant value() override;
private:
    unsigned theTimes;
};


/// 使用用户指定函数映射模拟信号传感器读数
/// 模板参数为用户指定函数的返回值的类型
template <typename T>
class TransWatcher final: public AnalogWatcher {
public:
    TransWatcher(const String& name, uint8_t pin, T (*func)(int)):
        AnalogWatcher(name, pin),
        theFunc(new IntFunc(func)) {}

    TransWatcher(const String& name, uint8_t pin, T (*func)(unsigned)):
        AnalogWatcher(name, pin),
        theFunc(new UnintFunc(func)) {}

    ~TransWatcher() {
        delete theFunc;
    }

    JsonVariant value() override {
        if (!(theFunc))
            return JsonVariant(null);
        return JsonVariant((*theFunc)(analogRead(thePin)));
    }

private:
    class FuncBase {
    protected:
        union {
            T (*iFunc)(int);
            T (*uFunc)(unsigned);
        } f;
    public:
        virtual T operator()(unsigned n) const = 0;
    } *theFunc;

    class IntFunc final: public FuncBase {
    public:
        IntFunc(T (*func)(int)) {
            FuncBase::f.iFunc = func;
        }
        T operator()(unsigned n) const {
            return FuncBase::f.iFunc(n);
        }
    };

    class UnintFunc final: public FuncBase {
    public:
        UnintFunc(T (*func)(unsigned)) {
            FuncBase::f.uFunc = func;
        }
        T operator()(unsigned n) const {
            return FuncBase::f.uFunc(n);
        }
    };
};


/// 读取多个模拟信号传感器，并取平均值
class MultiWatcher final: public Watcher {
public:
    MultiWatcher(const String& name):
        Watcher(name) {}
    void addSensor(uint8_t pin) {
        sensors.push(pin);
    }
    JsonVariant value() override;
private:
    List<int> sensors;
};

} // namespace: ACL

#endif // Watcher_h