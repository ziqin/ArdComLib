#ifndef TemWatcher_h
#define TemWatcher_h

#include <Watcher.h>
#include <Dht11.h>

class TemWatcher: public ACL::Watcher {
public:
    TemWatcher(const String& name, uint8_t pin):
        ACL::Watcher(name),
        dht11Sensor(pin)
    {}

    ACL::Variant value() override
    {
        switch (dht11Sensor.read()) {
            case Dht11::OK:
                return ACL::Variant(dht11Sensor.getTemperature());
            default:
                return ACL::Variant(ACL::null);
        }
    }

private:
    Dht11 dht11Sensor;
};

#endif