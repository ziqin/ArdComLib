// simple.ino

#include <ArdComLib.h>
#include <ArduinoJson.h>

void setup()
{
  AnalogWatcher light("Sunlight", 0);
  DigitalWatcher human("Human", 7);

  Messenger pi(9600, 5000);
  pi.addWatcher(&light);
  pi.addWatcher(&human);

  pi.work();
}

void loop() {}