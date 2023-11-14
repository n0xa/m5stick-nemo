# M5Stick-NEMO
M5 Stick C firmware for high-tech pranks

## Name and Background
NEMO started a personal project to help me learn more about ESP32 development with the Arduino IDE. I decided to replicate a few common, trending pranks that were getting a lot of attention in the tech community, as a challenge to myself, and to also better understand these attacks.  
NEMO is named after the small, clever and stubborn fish in Finding Nemo. This project stands in contrast to another high-tech gadget that's associated with certain sea-dwelling creatures. I did want to prove that there are a lot of things you can do with a small development kit and some curiosity. I have no delusions of superseding the capabilities of any similar device with this project. It's just for fun, and my own education.  

## Features
* [TV B-Gone](http://www.righto.com/2010/11/improved-arduino-tv-b-gone.html) port (thanks to MrArm's [HAKRWATCH](https://github.com/MrARM/hakrwatch)) to shut off many infrared-controlled TVs, projectors and other devices
* [AppleJuice](https://github.com/ECTO-1A/AppleJuice) iOS Bluetooth device pairing spam
* WiFi Spam - Funny SSIDs, WiFi Rickrolling, and a Random mode that creates hundreds of randomly-named SSIDs per minute
* WiFi SSID Scanner - Display 2.4 GHz SSIDs nearby and get information about them
* User-adjustable 24 Hour digital clock backed by the M5 Stick RTC so it holds relatively stable time even in deep sleep and low battery mode
* EEPROM-backed Settings for rotation, brightness and, automatic dimming
* Battery level and credits in settings menu

## User Interface
* A quick tap of the power button (closest to the USB port) will bring up the main menu from anywhere.
* Long pressing the power button for 6 seconds turns off the unit.
* In Function modes, the side button stops or pauses the process and brings up a menu.
* In Menu mode, the side button scrolls the cursor to the next option in the menu.
* In Function modes, the front M5 button wakes up the dim screen.
* In Menu mode, the front M5 button activates the selected menu item next to the cursor.

## Install from M5Burner
This is the absolute easiest way to get NEMO
* [M5Stick C Plus Quick Start](https://docs.m5stack.com/en/quick_start/m5stickc_plus/uiflow) has links to the M5Burner app for Linux, MacOS and Windows. This is the official tool to install UIFlow and other official firmware. I provide up-to-date binaries for NEMO there.
* Launch M5Burner
* Select "StickC" from the menu on the left (or StampS3 for Cardputer)
* Use the search at the top of the app to look for "NEMO". My official builds will be uploaded by "4x0nn" and have photos.
* Click Download
* Click Burn

## Install .bin files manually with esptool.py
* Install ESP-IDF tools per the [Espressif Getting Started Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/)
* Open the esp-idf CMD tool (on Windows) - on Mac or Linux, esp-idf.py and esptool.py should be in the system path.
* esptool.py --port COMPORT -b 115200 write_flash -z 0x0 M5Nemo-VERSION.bin
  * port may be a COM port e.g. COM4, COM11 on Windows. On Mac and Linux it will usually be in /dev such as /dev/ttyUSB0, /dev/ttyACM0 or /dev/cu.usbserial-3
  * M5Nemo-VERSION.bin should be a version you downloaded from a GitHub Release -- preferably the latest available.

## Building from Source
If you want to customize NEMO or contribute to the project, you should be familiar with building NEMO from source.
* Install Arduino IDE. I've used Arduino 1.8 on Linux and Windows, and Arduino 2.2 on Windows successfully.
* Install the M5Stack boards for Arduino IDE: In File -> Preferences, paste this URL into the "Boards Manager URLs" text box. Use commas between URLs if there are already URLs present.  https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json
* If M5Stack -> M5Stick-C-Plus doesn't show up under Tools -> Boards, then use Tools -> Boards -> Boards Manager and search for M5Stack. This will install support for most of the M5Stack boards including the Stick C Plus.
* Ensure the correct device model (e.g. M5Stick-C, M5Stick-C-Plus or M5Cardputer) is selected in the boards menu.
* Install necessary libraries. In Sketch -> Include Library -> Library Manager, search for and install the following libraries and any dependencies they require:
  * M5StickCPlus, M5StickC or M5Cardputer
  * IRRemoteESP8266
* Un-comment the appropriate `#define` line near the top for your platform (STICK_C, STICK_C_PLUS or CARDPUTER)
* Switch partition schemes. `Tools` -> `Partition Scheme` -> `No OTA (Large APP)` - sometimes this option is labeled `Huge APP` 
* Configuration
  * The code should compile cleanly and work on an M5Stick C Plus out of the box from the master branch or a release tag.
  * Uncomment only the one appropriate `#define` option or compiler errors will occur. 
  * If for some reason the screen jumps from very dim at level 0 to almost fully bright at level 1 and further brightness levels don't affect anything, set the pct_brightness variable to false.
* Compile and upload the project
