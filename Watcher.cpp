#include "Watcher.h"

namespace ACL {

Variant AverageWatcher::value() {
    if (!theTimes)
        return Variant(null);

    float sum = 0;
    for (unsigned i = 0; i < theTimes; ++i)
        sum += analogRead(thePin);
    return Variant(sum / theTimes, 4);
}


Variant MultiWatcher::value() {
    unsigned size = sensors.size();
    if (!size)
        return Variant(null);

    float sum = 0;
    for (List<int>::iterator i = sensors.begin(); i != sensors.end(); ++i)
        sum += analogRead(*i);
    return Variant(sum / size, 4);
}

}