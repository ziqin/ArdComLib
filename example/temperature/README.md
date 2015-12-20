We use DHT11 Sensor to measure atmospheric temperature in this example, and [adalton's Dht11 Library](https://github.com/adalton/arduino/tree/master/projects/Dht11_Library) was used.

To compile this example, you have to install the Dht11 Library mentioned above. It's quite easy. Just create a directory named `Dht11` in your Arduino IDE's libraries directory, and download [`Dht11.h`](https://github.com/adalton/arduino/blob/master/projects/Dht11_Library/Dht11.h) & [`Dht11.cpp`](https://github.com/adalton/arduino/blob/master/projects/Dht11_Library/Dht11.cpp) to it.

Since `loop()` was also defined in [`TempHumidity.cpp`](https://github.com/adalton/arduino/blob/master/projects/Dht11_Library/TempHumidity.cpp), you are not supposed to put it into `libraries/Dht11` directory, otherwise you'll encounter a multiple definition error.
