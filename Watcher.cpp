#include "Watcher.h"

using namespace ACL;

JsonVariant AverageWatcher::value() {
    if (!theTimes)
        return JsonVariant(null);

    float sum = 0;
    for (unsigned i = 0; i < theTimes; ++i)
        sum += analogRead(thePin);
    return JsonVariant(sum / theTimes, 4);
}


JsonVariant MultiWatcher::value() {
    unsigned size = sensors.size();
    if (!size)
        return JsonVariant(null);

    float sum = 0;
    for (List<int>::iterator i = sensors.begin(); i != sensors.end(); ++i)
        sum += analogRead(*i);
    return JsonVariant(sum / size, 4);
}