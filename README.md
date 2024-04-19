# M5Stick-NEMO
Firmware for high-tech pranks on M5Stack ESP32 Devices

![M5-Nemo Matrix Logo](https://github.com/n0xa/m5stick-nemo/blob/main/NEMOMatrix.png)
Logo by @unagironin

## Name and Background
NEMO started a personal project to help me learn more about ESP32 development with the Arduino IDE. I decided to replicate a few common, trending pranks that were getting a lot of attention in the tech community, as a challenge to myself, and to also better understand these attacks.  
NEMO is named after the small, clever and stubborn fish in Finding Nemo. This project stands in contrast to another high-tech gadget that's associated with certain sea-dwelling creatures. I did want to prove that there are a lot of things you can do with a small development kit and some curiosity. I have no delusions of superseding the capabilities of any similar device with this project. It's just for fun, and my own education.  

![M5-Nemo on M5StickC family and M5Cardputer](https://github.com/n0xa/m5stick-nemo/blob/main/M5-Nemo.jpg)

## My Changelog
* Adjusted .github/workflow/compile.yml to compile with the DEAUTH function.
* Added support to SONG on StickC Plus and Plus2
* Added an "Attack Menu" when seeing details of an Access Point
  - Clone Portal (Creates an Evil portal with the same SSID of the target)
  - Deauth attack (broadcasts deauthentication frames to devices connected to this Access Point)
  - Deauth+Clone (Creates the evil portal with the same SSID and sends deauthentication frames to that AP)
* Added option in Settings to Mount/Unmount SDCard when using M5StickC devices
* Created new file to handle SPI/SD if not using CARDPUTER
* SDCARD is now working on M5StickC Plus2

## My ToDo list
* ideas?

## Features
* [TV B-Gone](http://www.righto.com/2010/11/improved-arduino-tv-b-gone.html) port (thanks to MrArm's [HAKRWATCH](https://github.com/MrARM/hakrwatch)) to shut off many infrared-controlled TVs, projectors and other devices
* [AppleJuice](https://github.com/ECTO-1A/AppleJuice) iOS Bluetooth device pairing spam
* Bluetooth device notification spamming for SwiftPair (Windows) and Android
* WiFi Spam - Funny SSIDs, WiFi Rickrolling, and a Random mode that creates hundreds of randomly-named SSIDs per minute
* WiFi NEMO Portal - A captive portal that tries to social engineer email credentials - saves usernames and passwords to SD Card (if inserted into a supported reader)
* WiFi SSID Scanner - Display 2.4 GHz SSIDs nearby, get information about them, and even clone the SSIDs in NEMO Portal
* User-adjustable 24 Hour digital clock backed by the M5 Stick RTC so it holds relatively stable time even in deep sleep and low battery mode
* EEPROM-backed Settings for rotation, brightness, automatic dimming and NEMO Portal SSID
* Battery level and credits in settings menu

## User Interface
There are three main controls:
* Home - Stops the current process and returns you to the menu from almost anywhere in NEMO
* Next - Moves the cursor to the next menu option. In function modes, this usually stops the process and returns you to the previous menu.
* Select - Activates the currently-selected menu option, and wakes up the dimmed screen in function modes  

* StickC and StickC-Plus
  * Power: Long-press the power button for 6 seconds to turn off the unit
  * Home: Tap the power button (closest to the USB port)
  * Next: Tap the side button
  * Select: Tap the M5 button on the front of the unit  

* Cardputer
  * Home: Tap the Esc/~/` key or the Left-Arrow/, key
  * Next/Prev: Tap the Down-Arrow/. key and Up-Arrow/; keys to navigate
  * Select: Tap the OK/Enter key or Right-Arrow/? key  

## NEMO Portal
In NEMO Portal mode, NEMO activates an open WiFi Hotspot named "Nemo Free WiFi" (configurable in portal.h) with DNS, DHCP and Web servers activated. 
* NEMO Portal serves a fake login page that claims to provide internet access if you log in.
* This is a social engineering attack, and will log the username and passwords entered on the page. 
* From the Wifi Scan details, you can clone an existing SSID from the scan list. Exiting NEMO Portal will clear the Evil Twin SSID
* You can view captured credentials by connecting to the portal from your own device and browsing to http://172.0.0.1/creds
* You can set a custom SSID by connecting to the portal from your own device and browsing to http://172.0.0.1/ssid
* If your device supports EEPROM for settings, the custom SSID you enter will be saved as the default, even if powered off.
* If your device has an SD Card reader with a FAT filesystem formatted card inserted, the usernames and passwords will be logged to nemo-portal-creds.txt on the SD Card for you to peruse later. 
* SD Card support is only enabled by default on the M5Stack Cardputer platform. It can be enabled on M5Stick devices but an SD Card reader must be built and attached to the front panel pin header.
* NEMO Portal is only for use on professional engagements with a valid scope of work, educational or demonstration purposes. Storage, sale, or use of personal information without consent is against the law. 🤓

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

## Building from Source (with Arduino CLI)

- Install Arduino CLI
- Add M5Stack Index to Arduino Core
- Add M5Stack Libraries

```bash

# Install m5stack boards
arduino-cli core install m5stack:esp32  --additional-urls https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json --log-level warn --verbose

# Install required library
arduino-cli lib install M5Cardputer --log-level warn --verbose
arduino-cli lib install IRRemoteESP8266 --log-level warn --verbose

# Compile sketch
arduino-cli compile --fqbn m5stack:esp32:m5stack_cardputer -e --build-property build.partitions=huge_app --build-property upload.maximum_size=3145728 ./m5stick-nemo.ino

```

- This will create multiple binaries based on partition sketch, you can merge a single binary using `esptool`
- Install esptool - `pip install -U esptool`

```bash

esptool.py --chip esp32s3 merge_bin --output final.bin 0x0000 m5stick-nemo.ino.bootloader.bin 0x8000 m5stick-nemo.ino.partitions.bin 0x10000 m5stick-nemo.ino.bin
```

- You can now flash the merged binary firmware using `esptool`

```bash

esptool.exe write_flash -z 0 final.bin
```

## Building from Source (Docker)

- Install Docker
- Run `./scripts/docker-build.sh <configs/.env.>`
- Run `./scripts/flash.sh --device=<your-device-port>`

```sh
# This will build an image will all required libraries based on the configured platform, and it will compile, output and merge binaries
# By default this will compile for the M5Cardputer in en-us locale, ./config/.env.M5Cardputer
./scripts/docker-build.sh 

# If you want to select a different build config you can pass it as a parameter. See ./configs/ for various configurations
./scripts/docker-build.sh ./config/.env.M5Cardputer

# Binary files will be output to ./build
ls ./build

# This will flash the build output from the build step, it reuses the container image from the previous step.
# By default this will compile for the M5Cardputer in en-us locale, ./config/.env.M5Cardputer
./scripts/flash.sh --device=/dev/ttyusb0 

# If you passed a different build config make sure to pass it along to the flash script
./scipts/flash.sh --device=/dev/ttyusb0 --build-config=./config/.env.M5Cardputer
```



## Troubleshooting
* Several features output debugging information to the serial monitor. Use the Serial Monitor feature in Arduino IDE or M5Burner to gather this information. It may have useful hints. When filing a bug report, it often helps to include serial monitor output.
* Reset the EEPROM. On models with EEPROM settings support, use "Clear Settings" from the settings menu, or hold the "Next" button (Side key on StickC models, Tab or Down Arrow on Cardputer) while powering on. 
* TV-B-Gone's IR LED can be observed through a smart phone camera, emitting a pale purple beam of light. If it seems to be on constantly, or if it never flashes at all during TV-B-Gone operations, something is wrong. Report a bug. There's a known issue with TVBG not working after using Bluetooth spam or random wifi spam.
* Try viewing wifi lists from several different devices if you suspect wifi spam isn't working. Sometimes, Linux network manager can see networks that smart phones cannot. Please include the results of this testing if reporting wifi spam problems.
* Apple has patched a lot of Bluetooth stuff since summer 2023. If testing AppleJuice, try some of the AppleTV device types, as they tend to be more reliable due to apple not filtering out weaker bluetooth signals for that platform.


## Reporting Bugs
Please report bugs via GitHub Issues. These are easier to track than comments on social media posts, M5Burner entries, etc. If something isn't working, please include:
* Firmware version
* How you installed it (M5Burner, compiled yourself, esptool.py)
* Hardware 
* Specifically what feature and options are not working
* How you determined that it is not working and what testing you did. Include device models and operating systems of what you tested with, and any errors or relevant output from Serial Monitor, if applicable.
* If you figure out how to fix a bug you identified, PRs are welcome!

## Contributing
Contributions are welcome. 
* Please look at the GitHub Issues for the project. There are feature suggestions and bugs reported there, and I'd appreciate PRs that address those.
* When submitting a Pull Request, please target the develop branch. The easiest way to do this is to fork ALL branches, or to simply create a "develop" branch in your own fork, then use GitHub to Sync your develop branch.
* Take note of how certain hardware (like the LED and RTC) are defined and gated in the code and try to stick to those patterns. Also, use the definitions for FGCOLOR, BGCOLOR, TEXT_SIZE* and the DISP alias when outputting things to the built-in display.
* Feel free to add your github to the contributors array as part of your pull request.

Things I'd like help on:
* Improved localization/translations of the menu, not just NEMO Portal HTML.
  * Probably needs a new .h file
  * Be configurable in settings and use an eeprom byte to save the setting
  * Make gratuitous use of `const` in the implementation so that localization strings are stored only in, and referenced directly from, the flash storage as opposed to using lots of SRAM.
* Infrared
  * A new "Region" of TV-B-Gone that's full of additional IR codes that can turn RGB LED strips, air conditioners, fans, sound bars and the like on and off
  * A way to convert or use flipper zero IR codes from within NEMO's code-base
* Figure out a way to read and display battery level on the Cardputer and StickC-Plus2 models that lack an AXP192 PMU. The [battery code in the Cardputer factory demo](https://github.com/m5stack/M5Cardputer-UserDemo/tree/main/main/hal/bat) might be a good place to start.
* TARGETED Deauthentication against a specific access point only. Deauth spamming PRs will be rejected.

Things I probably won't merge in:
* Bulk wifi deauthentication spamming
* Bluetooth spam that potentially disrupts health and fitness trackers, smart watches, etc.
