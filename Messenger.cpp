#include <Arduino.h>
#include "Messenger.h"
#include "Watcher.h"
#include "WatchersDic.h"
#include "List.h"
#include "../ArduinoJson/include/ArduinoJson.h"

using namespace ACL;

Messenger::Messenger(unsigned baudRate) {
    Serial.begin(baudRate);
    watchersList = new List<Watcher*>();
}


Messenger::Messenger(unsigned baudRate, unsigned long timeout) {
    Serial.begin(baudRate);
    Serial.setTimeout(timeout);
    watchersList = new List<Watcher*>();
}


Messenger::~Messenger() {
    Serial.end();
}


void Messenger::addWatcher(Watcher *Watcher) {
    watchersList->push(Watcher);
}


void Messenger::listen() {
    WatchersDic watchers(watchersList);
    delete watchersList;
    watchersList = NULL;

    for (;;) {
        int status = 0;
        StaticJsonBuffer<200> resBuffer;
        JsonObject& res = resBuffer.createObject();

        String reqStr = Serial.readStringUntil('\n');
        if (reqStr.length() > 0) {
            StaticJsonBuffer<100> reqBuffer;
            JsonObject& req = reqBuffer.parseObject(reqStr);

            if (req.success() && req.containsKey("watchers")) {
                JsonArray& reqWatchers = req["watchers"];
                JsonObject& resWatchers = res.createNestedObject("watchers");
                for (JsonArray::const_iterator i = reqWatchers.begin(); i != reqWatchers.end(); ++i) {
                    Watcher *w = watchers[*i];
                    if (!w) {
                        status |= 2;
                    } else {
                        resWatchers[static_cast<const char*>(*i)] = w->value();
                    }
                }
            } else {
                status |= 1;
            }

            res["status"] = status;
            res.printTo(Serial);
            Serial.println();
        }
    }
}