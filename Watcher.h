#ifndef Watcher_h
#define Watcher_h

#include <Arduino.h>
#include "../ArduinoJson/include/ArduinoJson/JsonVariant.hpp"
#include "List.h"
#if __cplusplus > 199711L // C++ 11+
#include "Vlpp/Function.h"
#endif

namespace ACL {

typedef ArduinoJson::JsonVariant Variant;

const char * const null = static_cast<const char*>(0);

/// 观察者基类
class Watcher {
public:
    Watcher(const String& name):
        theName(name) {}
    virtual ~Watcher() {}
    virtual Variant value() = 0;
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
    virtual Variant value() override {
        return Variant(digitalRead(thePin) == HIGH);
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
    virtual Variant value() override {
        return Variant(analogRead(thePin));
    }
protected:
    uint8_t thePin;
};


/// 多次读取模拟传感信号传感器，并取平均值
class AverageWatcher final: public AnalogWatcher {
public:
    AverageWatcher(const String& name, uint8_t pin, unsigned times):
        AnalogWatcher(name, pin), theTimes(times) {}
    Variant value() override;
private:
    unsigned theTimes;
};

/// 使用用户指定函数映射模拟信号传感器读数
/// 模板参数为用户指定函数的返回值的类型
#if __cplusplus > 199711L // support lambda closure if C++ 11+
template <typename T>
class TransWatcher final: public AnalogWatcher {
public:
    TransWatcher(const String& name, uint8_t pin, vl::Func<T(int)> func):
        AnalogWatcher(name, pin),
        func(func) {}

    Variant value() override {
        return Variant(func(analogRead(thePin)));
    }

private:
    vl::Func<T(int)> func;
};
#else
template <typename T>
class TransWatcher final: public AnalogWatcher {
public:
    TransWatcher(const String& name, uint8_t pin, T (*func)(int)):
        AnalogWatcher(name, pin),
        func(func) {}

    Variant value() override {
        if (!func)
            return Variant(null);
        return Variant(func(analogRead(thePin)));
    }

private:
    T (*func)(int);
};
#endif


/// 读取多个模拟信号传感器，并取平均值
class MultiWatcher final: public Watcher {
public:
    MultiWatcher(const String& name):
        Watcher(name) {}
    void addSensor(uint8_t pin) {
        sensors.push(pin);
    }
    Variant value() override;
private:
    List<int> sensors;
};

} // namespace: ACL

#endif // Watcher_h