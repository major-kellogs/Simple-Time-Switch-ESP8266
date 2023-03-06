# Simple-Time-Switch-ESP8266 #

## Description ##
This is a simple time switch made with an ESP8266 (board: ESP01S). It is originally made for a small LED panel. But of course you can use it as you wish.

## Features ##
-  With the used hardware it is possible to switch an 12 volts output.
-  WIFI is used to set the current time of the microcontroller.

## Getting started ##
-  Import the project into the ide of your choice (CLion by Jetbrains is recommended) and make sure that you are using [PlatformIO](https://platformio.org/) as plugin.
### Adjust the time to switch ###
To adjust the time when the switch events should happen you need to modify the following code block  inside the function `void controlLEDs()` of the file **src->main.cpp** beginning at line 42.
```C++
uint8 isLEDBright =
        (timeInfo.tm_hour >= 10 && timeInfo.tm_hour < 15) ||
        (timeInfo.tm_hour >= 18 && timeInfo.tm_hour < 23);
```
As you can see, this code switches the output between **10:00am and 03:00pm** as well as between **06:00pm and 11:00pm** to `HIGH`.

### Get WIFI connectivity ###
The ESP8266 chip is only capable to connect to a 2.4 GHz WIFI. To get it working you simply need to insert your WIFI credentials inside the file **src->credentials.h**
```C++
const char *ssid = "YOUR SSID";
const char *password = "YOUR PASSPHRASE";
```
### Needed Components ###
-  pcb prototyping board with a grid of at least 20x6 (2,54mm)
-  ESP-01S microcontroller
-  12v LED panel or what ever you want to switch on and off (check the datasheets of the BC337 transistor and the LD1117AV33 Voltage regulator for the max current)
-  transistor BC337
-  Voltage regulator LD1117AV33 
-  resistor 2K2
-  resistor 10K
-  capacitor 100nF
-  capacitor 22µF
-  some wires and solder
-  appropriate 12v power source

Check **circuit-overview.png** for the correct wiring.
