// Nemo Firmware for the M5 Stack Stick C Plus
// github.com/n0xa | IG: @4x0nn
#include <M5StickCPlus.h>
#include <EEPROM.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "WORLD_IR_CODES.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

String formattedDate;
String dayStamp;
String timeStamp;

// globals for passing bluetooth info between routines
// AppleJuice Payload Data 
uint8_t Airpods[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x02, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t AirpodsPro[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0e, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t AirpodsMax[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0a, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t AirpodsGen2[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0f, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t AirpodsGen3[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x13, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t AirpodsProGen2[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x14, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t PowerBeats[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x03, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t PowerBeatsPro[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0b, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t BeatsSoloPro[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x0c, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t BeatsStudioBuds[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x11, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t BeatsFlex[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x10, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 
uint8_t BeatsX[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x05, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t BeatsSolo3[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x06, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t BeatsStudio3[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x09, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t BeatsStudioPro[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x17, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t BeatsFitPro[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x12, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t BeatsStudioBudsPlus[31] = {0x1e, 0xff, 0x4c, 0x00, 0x07, 0x19, 0x07, 0x16, 0x20, 0x75, 0xaa, 0x30, 0x01, 0x00, 0x00, 0x45, 0x12, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t AppleTVSetup[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x01, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t AppleTVPair[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x06, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t AppleTVNewUser[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x20, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t AppleTVAppleIDSetup[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x2b, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t AppleTVWirelessAudioSync[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0xc0, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t AppleTVHomekitSetup[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x0d, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t AppleTVKeyboard[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x13, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t AppleTVConnectingToNetwork[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x27, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t HomepodSetup[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x0b, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t SetupNewPhone[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x09, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t TransferNumber[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x02, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t TVColorBalance[23] = {0x16, 0xff, 0x4c, 0x00, 0x04, 0x04, 0x2a, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xc1, 0x1e, 0x60, 0x4c, 0x95, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00};
uint8_t* data;
int deviceType = 0; 

BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
BLEAdvertising *pAdvertising;

#define EEPROM_SIZE 1

struct MENU {
  char name[19];
  int command;
};
int cursor = 0;
int rotation = 1;
bool rstOverride = false;

/// SWITCHER ///
// Proc codes
// 0  - Clock
// 1  - Main Menu
// 2  - Settings Menu
// 3  - Clock set (not implemented yet)
// 4  - Dimmer Time adjustment
// 5  - TV B-GONE
// 6  - Battery info
// 7  - screen rotation
// 8  - AppleJuice Menu
// 9  - AppleJuice Advertisement

bool isSwitching = true;
//int current_proc = 0;
int current_proc = 1; // Temp. override since we're disabling the clock for the time being

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
      M5.Axp.ScreenBreath(11);
    }
    int newtime = M5.Rtc.Second + screen_dim_time + 2; // hacky but needs a couple extra seconds added

    if (newtime >= 60) {
      newtime = newtime - 60;
    }
    screen_dim_current = newtime;
  }
  if (screen_dim_dimmed == false) {
    if (M5.Rtc.Second == screen_dim_current || (M5.Rtc.Second + 1) == screen_dim_current || (M5.Rtc.Second + 2) == screen_dim_current) {
      M5.Axp.ScreenBreath(0);
      screen_dim_dimmed = true;
    }
  }
}

/// MAIN MENU ///
MENU mmenu[] = {
//  { "clock", 0}, // disabled for now
  { "TV B-GONE", 5},
  { "AppleJuice", 8},
  { "settings", 2},
};

void mmenu_drawmenu() {
  M5.Lcd.setTextSize(2);
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
  { "set dim time", 4},
  { "battery info", 6},
  { "rotation", 7},
  { "back", 1},
};

void smenu_drawmenu() {
  M5.Lcd.setTextSize(2);
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
  { "30 seconds", 30},
  { "25 seconds", 25},
  { "20 seconds", 20},
  { "15 seconds", 15},
  { "10 seconds", 10},
  { "5 seconds", 5},
  { "back", screen_dim_time},
};

void dmenu_drawmenu() {
  M5.Lcd.setTextSize(2);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 8, 1);
  for ( int i = 0 ; i < ( sizeof(dmenu) / sizeof(MENU) ) ; i++ ) {
    M5.Lcd.print((cursor == i) ? ">" : " ");
    M5.Lcd.println(dmenu[i].name);
  }
}

void dmenu_setup() {
  M5.Lcd.setRotation(rotation);
  cursor = 0;
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
    rstOverride = false;
    isSwitching = true;
    screen_dim_time = dmenu[cursor].command;
    current_proc = 2;
  }
}

/// Rotation MENU ///
MENU rmenu[] = {
  { "Right", 1},
  { "Left", 3},
  { "back", rotation},
};

void rmenu_drawmenu() {
  M5.Lcd.setTextSize(2);
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

void battery_drawmenu(int battery, int b, int c) {
  M5.Lcd.setTextSize(2);
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
void xmitCodeElement(uint16_t ontime, uint16_t offtime, uint8_t PWM_code );
void quickflashLEDx( uint8_t x );
void delay_ten_us(uint16_t us);
void quickflashLED( void );
uint8_t read_bits(uint8_t count);
uint16_t rawData[300];
#define MAX_WAIT_TIME 65535 //tens of us (ie: 655.350ms)
IRsend irsend(IRLED);  // Set the GPIO to be used to sending the message.
extern const IrCode* const NApowerCodes[];
extern const IrCode* const EUpowerCodes[];
extern uint8_t num_NAcodes, num_EUcodes;
uint8_t bitsleft_r = 0;
uint8_t bits_r = 0;
uint8_t code_ptr;
volatile const IrCode * powerCode;
uint8_t read_bits(uint8_t count)
{
  uint8_t i;
  uint8_t tmp = 0;
  for (i = 0; i < count; i++) {
    if (bitsleft_r == 0) {
      bits_r = powerCode->codes[code_ptr++];
      bitsleft_r = 8;
    }
    bitsleft_r--;
    tmp |= (((bits_r >> (bitsleft_r)) & 1) << (count - 1 - i));
  }
  return tmp;
}
#define BUTTON_PRESSED LOW
#define BUTTON_RELEASED HIGH
uint16_t ontime, offtime;
uint8_t i, num_codes;
uint8_t region;

void tvbgone_setup() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(4);
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.println("TV-B-Gone");
  irsend.begin();
  // Hack: Set IRLED high to turn it off after setup. Otherwise it stays on (active low)
  digitalWrite(IRLED, HIGH);

  delay_ten_us(5000);
  if (digitalRead(REGIONSWITCH)) {
    region = NA;
    M5.Lcd.println("Region: NA");
  }
  else {
    region = EU;
    M5.Lcd.println("Region: EU");
  }
  delay(1000); // Give time after loading
}

void sendAllCodes()
{
  bool endingEarly = false; //will be set to true if the user presses the button during code-sending
  if (digitalRead(REGIONSWITCH)) {
    region = NA;
    num_codes = num_NAcodes;
  }
  else {
    region = EU;
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
    M5.Lcd.setTextSize(4);
    M5.Lcd.setCursor(5, 1);
    M5.Lcd.println("TV-B-Gone");
    M5.Lcd.setTextSize(2);
    const uint8_t bitcompression = powerCode->bitcompression;
    code_ptr = 0;
    for (uint8_t k = 0; k < numpairs; k++) {
      uint16_t ti;
      ti = (read_bits(bitcompression)) * 2;
      offtime = powerCode->times[ti];  // read word 1 - ontime
      ontime = powerCode->times[ti + 1]; // read word 2 - offtime
      M5.Lcd.setTextSize(1);
      M5.Lcd.printf("rti = %d Pair = %d, %d\n", ti >> 1, ontime, offtime);
      rawData[k * 2] = offtime * 10;
      rawData[(k * 2) + 1] = ontime * 10;
      yield();
    }
    irsend.sendRaw(rawData, (numpairs * 2) , freq);
    // Hack: Set IRLED high to turn it off after each burst. Otherwise it stays on (active low)
    digitalWrite(IRLED, HIGH);
    yield();
    bitsleft_r = 0;
    delay_ten_us(20500);
    if (digitalRead(TRIGGER) == BUTTON_PRESSED)
    {
      while (digitalRead(TRIGGER) == BUTTON_PRESSED) {
        yield();
      }
      endingEarly = true;
      delay_ten_us(50000); //500ms delay
      quickflashLEDx(4);
      delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
      delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
      break; //exit the POWER code "for" loop
    }
  } 
  if (endingEarly == false)
  {
    delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
    delay_ten_us(MAX_WAIT_TIME); // wait 655.350ms
    quickflashLEDx(8);
  }
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

void delay_ten_us(uint16_t us) {
  uint8_t timer;
  while (us != 0) {
    for (timer = 0; timer <= DELAY_CNT; timer++) {
      NOP;
      NOP;
    }
    NOP;
    us--;
  }
}

void quickflashLED( void ) {
  digitalWrite(LED, LOW);
  delay_ten_us(3000);   // 30 ms ON-time delay
  digitalWrite(LED, HIGH);
}

void quickflashLEDx( uint8_t x ) {
  quickflashLED();
  while (--x) {
    delay_ten_us(25000);     // 250 ms OFF-time delay between flashes
    quickflashLED();
  }
}

/// CLOCK ///
void clock_setup() {
  M5.Lcd.setRotation(rotation);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(3);
}

void clock_loop() {
  M5.Rtc.GetBm8563Time();
  M5.Lcd.setCursor(40, 40, 2);
  M5.Lcd.printf("%02d:%02d:%02d\n", M5.Rtc.Hour, M5.Rtc.Minute, M5.Rtc.Second);
  delay(250);
}

/// ENTRY ///
void setup() {
  M5.begin();
  M5.Axp.ScreenBreath(11); // Brightness
  M5.Lcd.setRotation(rotation);
  M5.Lcd.setTextColor(GREEN, BLACK);
  EEPROM.begin(EEPROM_SIZE);
  rotation = EEPROM.read(0);

  // Boot Screen
  digitalWrite(M5_LED, HIGH); //LEDOFF
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(5, 10);
  M5.Lcd.setRotation(rotation);
  M5.Lcd.print("M5-NEMO\n");
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("For M5StickC-Plus\nBy Axon | IG: @4x0nn");
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

MENU ajmenu[] = {
  { "AirPods", 1},
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
  { "Transfer Number", 27},
  { "Setup New Phone", 28},
  { "back", 29},
};

void aj_drawmenu() {
  M5.Lcd.setRotation(rotation);
  M5.Lcd.setTextSize(2);
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
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.println("AppleJuice");
  delay(1000);  
  cursor = 0;
  rstOverride = true;
  aj_drawmenu();
}

void aj_loop(){

  if (digitalRead(M5_BUTTON_RST) == LOW) {
    cursor++;
    cursor = cursor % ( sizeof(ajmenu) / sizeof(MENU) );
    aj_drawmenu();
    delay(250);
  }
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    deviceType = ajmenu[cursor].command;
    // Also borrowed heavily from ronaldstoner / ECTO-1A esp32 AppleJuice
    //uint8_t* data;
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
      M5.Lcd.setTextSize(3);
      M5.Lcd.setCursor(5, 1);
      M5.Lcd.println("AppleJuice");
      M5.Lcd.setTextSize(2);
      M5.Lcd.print("Advertising:\n");
      M5.Lcd.print(ajmenu[cursor].name);
      M5.Lcd.print("\n\nHold Side Key: Exit");
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
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
  if (deviceType >= 18){
    oAdvertisementData.addData(std::string((char*)data, sizeof(AppleTVPair)));
  } else {
    oAdvertisementData.addData(std::string((char*)data, sizeof(Airpods)));
  }
  pAdvertising->setAdvertisementData(oAdvertisementData);
  pAdvertising->start();
  digitalWrite(M5_LED, LOW); //LED ON on Stick C Plus
  delay(50);
  digitalWrite(M5_LED, HIGH); //LED OFF on Stick C Plus
  delay(950); // 1 second between beacons when combined with LED On delay above for brightness
  pAdvertising->stop();
}

void loop() {
  // This is the code to handle running the main loops
  // Background processes
  switcher_button_proc();
  screen_dim_proc();

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
  }
}
