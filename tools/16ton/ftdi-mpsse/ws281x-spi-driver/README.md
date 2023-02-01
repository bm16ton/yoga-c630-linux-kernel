# ws281x-spi-driver
A small, efficient and **very** easy-to-use C++ library to drive ws281x LEDs (aka "NeoPixels") via the SPI bus.
It has practically no dependencies besides a proper a linux computer with an SPI bus (e.g. the Raspberry Pi - any version).
All you have to do is to clone it and hit "make" and you will have a number of examples on your hands which should work out of the box.

## Simple Cabling
Basically you just have to connect the SPI-MOSI pin of your host to the input pin of your first LED.
Besides that you need to connect +5V to the LEDs and provide a common ground (GND) between your host and the LED strip.
No extra chips, resistors, etc. required. Keep in mind that this simple setup a has a couple of limitations with regard to reliability.

## Raspberry Pi notes
You will need to enable the SPI bus first and reboot.
You *can* connect the +5V and GND of the LEDs to the GPIO-header on your Raspberry and power and control everything from the Raspberry. However I would not recommend to drive more then a handful of LEDs this way, as anything more might overload the supply capabilities of the Raspberry...
If you have troubles with the reliability, you could try to drive the LEDs from the 3.3V supply of the Raspberry. The LEDs usually work pretty well with only 3.3V. However the 3.3V supply power is even more limited.

## Advanced Cabling
If you want to use the LED strip as full-fledged SPI device and continue to use the SPI bus to drive other chips, you can use a level-shifter with a chip-enable input like the "74AHCT1G125GW".
A level-shifter also has the advantage that you can drive the 5V LEDs from e.g. a 3.3V host like the Raspberry *more reliably*
Have a look here "https://easyeda.com/Neegu0Sh/neopixel-level-shifter" for how to wire everything up.

## Level-Shifter notes
The LEDs run at 2500 KHz, make sure your level-shifter can support that speed.
Bi-directional level-shifters (usually for i2c) will most likely *NOT* work.

## Credits
This library was heavily inspired by Jeremy Garff's (jgarff) library "rpi_ws281x". Have a look here "https://github.com/jgarff/rpi_ws281x". All credits go to him for the idea to drive LEDs via PWM/SPI/etc.

![alt text](https://raw.githubusercontent.com/SIGSEGV111/ws281x-spi-driver/master/led-ring-example.jpg "LED Ring")
