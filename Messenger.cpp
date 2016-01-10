#include <Arduino.h>
#include "Messenger.h"
#include "Watcher.h"
#include "Worker.h"
#include "NameDic.h"
#include "List.h"
#include "../ArduinoJson/include/ArduinoJson.h"

namespace ACL {

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


void Messenger::addWatcher(Watcher *watcher) {
    watchersList->push(watcher);
}


void Messenger::addWorker(TaskWorker *worker) {
    workersList->push(worker);
}


void Messenger::work() {
    NameDic<Watcher> watchers(watchersList);
    delete watchersList;
    watchersList = NULL;
    NameDic<TaskWorker> workers(workersList);
    delete workersList;
    workersList = NULL;

    for (;;) {
        int status = 0;
        StaticJsonBuffer<200> resBuffer;
        JsonObject& res = resBuffer.createObject();

        String reqStr = Serial.readStringUntil('\n');
        if (reqStr.length() > 0) {
            StaticJsonBuffer<100> reqBuffer;
            JsonObject& req = reqBuffer.parseObject(reqStr);

            if (req.success()) {
                if (req.containsKey("watchers")) {
                    JsonArray& reqWatchers = req["watchers"];
                    JsonObject& resWatchers = res.createNestedObject("watchers");
                    for (JsonArray::const_iterator i = reqWatchers.begin(); i != reqWatchers.end(); ++i) {
                        Watcher *w = watchers[*i];
                        if (w) {
                            resWatchers[i->asString()] = w->value();
                        } else {
                            status |= 2;
                        }
                    }
                }
                if (req.containsKey("workers")) {
                    JsonArray& reqWorkers = req["workers"];
                    for (JsonArray::const_iterator i = reqWorkers.begin(); i != reqWorkers.end(); ++i) {
                        TaskWorker *w = workers[*i];
                        if (w) {
                            w->work();
                        } else {
                            status |= 2;
                        }
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

}