// MyWatcher.ino

#include <ArdComLib.h>
#include <ArduinoJson.h>
#include "MyWatcher.h"

void setup()
{
  MyWatcher watcher("MyWatcher");

  Messenger pi(9600, 5000);
  pi.addWatcher(&watcher);

  pi.work();
}

void loop() {}
