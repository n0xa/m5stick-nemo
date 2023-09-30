# M5Stick-NEMO
M5 Stick C firmware for high-tech pranks

## Name
NEMO is named after the small, clever and headstrong fish in Finding Nemo. This project stands in contrast to other gadgets that have become associated with certain sea-dwelling creatures.

## Features
* [TV B-Gone](http://www.righto.com/2010/11/improved-arduino-tv-b-gone.html) port (thanks to MrArm's [HAKRWATCH](https://github.com/MrARM/hakrwatch)) to shut off many infrared-controlled TVs, projectors and other devices
* [AppleJuice](https://github.com/ECTO-1A/AppleJuice) iOS Bluetooth device pairing spam
* WiFi Spam - Funny SSIDs, WiFi Rickrolling, and a Random mode that creates hundreds of randomly-named SSIDs per minute
* User-adjustable 24 Hour digital clock backed by the M5 Stick RTC so it holds relatively stable time even in deep sleep and low battery mode
* EEPROM-backed Settings for rotation, brightness and, automatic dimming
* Battery level and credits in settings menu

## Building from Source
* I have compiled successfully using Arduino IDE on Linux and Windows
* If app size is too large, you must switch partition schemes. Tools -> Partition Scheme -> No OTA (Large APP)
