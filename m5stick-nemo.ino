// Nemo Firmware for the M5 Stack Stick C Plus
// github.com/n0xa | IG: @4x0nn
#include <M5StickCPlus.h>
#include <EEPROM.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "applejuice.h"
#include "WORLD_IR_CODES.h"
#include "wifispam.h"
#include <BLEUtils.h>
#include <BLEServer.h>

int advtime = 0; 
String formattedDate;
String dayStamp;
String timeStamp;
int cursor = 0;
int rotation = 1;
bool rstOverride = false;
#define EEPROM_SIZE 1

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
  { "clock", 0},
  { "TV B-GONE", 5},
  { "AppleJuice", 8},
  { "WiFi Spam", 12},
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
  { "set clock time", 3},
  { "set dim time", 4},
  { "battery info", 6},
  { "rotation", 7},
  { "credits", 10},
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

/// BATTERY INFO ///
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

/// TIMESET ///
void timeset_drawmenu(int nums) {
  M5.Lcd.setRotation(rotation);
  M5.Lcd.setTextSize(2);
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

/// AppleJuice ///
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
    delay(100);
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
  M5.Rtc.GetBm8563Time();
  if (M5.Rtc.Second != advtime){
    advtime = M5.Rtc.Second;
    pAdvertising->stop(); // This is placed here mostly for timing.
                          // It allows the BLE beacon to run through the loop.
    BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
    // sizeof() has to match the 31 and 23 byte char* however it doesn't seem
    // to work with bare integers, so sizeof() calls arbitrary elements of the
    // correct length. Without this if block, only 31-byte messages worked.
    if (deviceType >= 18){
      oAdvertisementData.addData(std::string((char*)data, sizeof(AppleTVPair)));
    } else {
      oAdvertisementData.addData(std::string((char*)data, sizeof(Airpods)));
    }
    pAdvertising->setAdvertisementData(oAdvertisementData);
    pAdvertising->start();
    digitalWrite(M5_LED, LOW); //LED ON on Stick C Plus
    delay(10);
    digitalWrite(M5_LED, HIGH); //LED OFF on Stick C Plus
  }
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    current_proc = 8;    
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
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(0, 25);
  M5.Lcd.print(" M5-NEMO\n");
  M5.Lcd.setTextSize(2);
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
  M5.Lcd.setTextSize(4);
  M5.Lcd.setCursor(5, 1);
  M5.Lcd.println("WiFi Spam");
  delay(1000);
  M5.Lcd.setTextSize(1);
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
  }
  M5.Lcd.setTextSize(2);
  current_proc = 11;
}

void wifispam_loop() {
  int i = 0;
  int len = 0;
  digitalWrite(M5_LED, LOW); //LED ON on Stick C Plus
  delay(1);
  digitalWrite(M5_LED, HIGH); //LED OFF on Stick C Plus
  // put your main code here, to run repeatedly:
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
    }
  }
}

/// WIFISPAM MENU ///
MENU wsmenu[] = {
  { "Funny", 0},
  { "Rickroll", 1},
  { "back", 2},
};

void wsmenu_drawmenu() {
  M5.Lcd.setTextSize(2);
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
    // Also borrowed heavily from ronaldstoner / ECTO-1A esp32 AppleJuice
    //uint8_t* data;
    switch(option) {
      case 0:
        spamtype = 1;
        rstOverride = false;
        isSwitching = true;
        current_proc = 11;
        break;
      case 1:
        spamtype = 2;
        rstOverride = false;
        isSwitching = true;
        current_proc = 11;
        break;
      case 2:
        rstOverride = false;
        isSwitching = true;
        current_proc = 1;
        break;
    }
  }
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
  M5.Lcd.setTextSize(4);
  M5.Lcd.setCursor(40, 15);
  M5.Lcd.setRotation(rotation);
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
  }
}
