// temperature.ino

#include <ArdComLib.h>
#include <ArduinoJson.h>
#include <Dht11.h>
#include "TemWatcher.h"

void setup()
{
  TemWatcher tem("Temperature", 7);

  Messenger pi(9600, 5000);
  pi.addWatcher(&tem);

  pi.work();
}

void loop() {}
