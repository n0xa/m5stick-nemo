#include "libssh_esp32.h"
#include <libssh/libssh.h>
#include <WiFi.h>

String ssh_wifi_ssid = ""; // Replace with your WiFi SSID
String ssh_wifi_password = ""; // Replace with your WiFi password

// SSH server configuration (initialize as empty strings)
String ssh_host = "";
String ssh_user = "";
String ssh_password = "";

// M5Cardputer setup
M5Canvas canvas(&DISP);
String commandBuffer = "> ";
int cursorY = 0;
const int lineHeight = 32;
unsigned long lastKeyPressMillis = 0;
const unsigned long debounceDelay = 200; // Adjust debounce delay as needed

ssh_session my_ssh_session;
ssh_channel channel;

bool filterAnsiSequences = true; // Set to false to disable ANSI sequence filtering

char mapToControlCharacter(char key) {
    // ASCII control characters are typically the first 32 characters in the ASCII table
    if (key >= 'a' && key <= 'z') {
        return key - 'a' + 1;  // 'a' - 1 -> 'z' - 26
    } else if (key >= 'A' && key <= 'Z') {
        return key - 'A' + 1;  // 'A' - 1 -> 'Z' - 26
    } else {
        // Here you can add specific cases for other characters, like '[' or '4',
        // or handle them with a default case.
        // Example: case '2': return '\x00'; // If Ctrl+2 is a special character in your context
        return key; // or some default handling or error signaling
    }
}

void waitForInput(String& input) {
    unsigned long startTime = millis();
    unsigned long lastKeyPressMillis = 0;
    const unsigned long debounceDelay = 200; // Adjust debounce delay as needed
    String currentInput = input;

    while (true) {
        M5Cardputer.update();
        if (M5Cardputer.Keyboard.isChange()) {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
            
            if (status.del && currentInput.length() > 0) {
                // Handle backspace key
                currentInput.remove(currentInput.length() - 1);
                DISP.setCursor(DISP.getCursorX() - 12, DISP.getCursorY());
                DISP.print(" ");
                DISP.setCursor(DISP.getCursorX() - 12, DISP.getCursorY());
                cursorY = DISP.getCursorY();
                lastKeyPressMillis = millis();
            }

            for (auto i : status.word) {
                if (millis() - lastKeyPressMillis >= debounceDelay) {
                    currentInput += i;
                    DISP.print(i);
                    cursorY = DISP.getCursorY();
                    lastKeyPressMillis = millis();
                }
            }

            if (status.enter) {
                DISP.println(); // Move to the next line
                input = currentInput;
                break;
            }
        }
    }
}

void ssh_setup() {
    Serial.println("Starting SSH Client Setup");
    DISP.setTextSize(MEDIUM_TEXT);
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 5, 1);
    DISP.print("SSH Client\n\n");
    DISP.setTextSize(SMALL_TEXT);
    DISP.print("SSID: ");
    delay(debounceDelay);
    waitForInput(ssh_wifi_ssid);
    DISP.print("Password: ");
    delay(debounceDelay);
    waitForInput(ssh_wifi_password);
    Serial.println(ssh_wifi_ssid);
    Serial.println(ssh_wifi_password);
    
    // Connect to WiFi
    DISP.print("Connecting");
    WiFi.begin(ssh_wifi_ssid, ssh_wifi_password);
    char wifi_connect_cont = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        DISP.print(".");
        Serial.print(".");
        wifi_connect_cont++;
        if (wifi_connect_cont > 20){
          ssh_wifi_ssid = ""; 
          ssh_wifi_password = "";
          wifi_connect_cont = 0;
          rstOverride = false;
          isSwitching = true;
          current_proc = 12;
          DISP.print("\n Connection Timeout.");
          Serial.println("\n Connection Timeout.");
          delay(1000);
          return;
        }
    }
    ssh_wifi_ssid = ""; 
    ssh_wifi_password = "";  
    DISP.print("\n Connected!");
    Serial.println("\nWiFi Connected");

    // Initialize the cursor Y position
    DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 5, 1);

    // Prompt for SSH host, username, and password
    DISP.print("SSH Host: ");
    waitForInput(ssh_host);
    delay(debounceDelay);
    DISP.print("SSH Username: ");
    waitForInput(ssh_user);
    delay(debounceDelay);
    DISP.print("SSH Password: ");
    waitForInput(ssh_password);
    delay(debounceDelay);

    // Connect and authenticate with SSH server
    my_ssh_session = ssh_new();
    if (my_ssh_session == NULL) {
        ssh_host = ""; 
        ssh_user = "";
        ssh_password = "";
        rstOverride = false;
        isSwitching = true;
        current_proc = 12; 
        DISP.print("SSH Session creation failed.");
        Serial.println("SSH Session creation failed.");
        delay(1000);            
        return;
    }
    ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, ssh_host.c_str());
    ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, ssh_user.c_str());

    if (ssh_connect(my_ssh_session) != SSH_OK) {
        ssh_host = ""; 
        ssh_user = "";
        ssh_password = "";
        rstOverride = false;
        isSwitching = true;
        current_proc = 12;
        ssh_free(my_ssh_session);  
        DISP.print("SSH Connect error.");
        Serial.println("SSH Connect error.");
        delay(1000);
        return;
    }

    if (ssh_userauth_password(my_ssh_session, NULL, ssh_password.c_str()) != SSH_AUTH_SUCCESS) {
        ssh_host = ""; 
        ssh_user = "";
        ssh_password = "";
        rstOverride = false;
        isSwitching = true;
        current_proc = 12;
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        DISP.print("SSH Authentication error.");
        Serial.println("SSH Authentication error.");
        delay(1000);
        return;
    }

    channel = ssh_channel_new(my_ssh_session);
    if (channel == NULL || ssh_channel_open_session(channel) != SSH_OK) {
        ssh_host = ""; 
        ssh_user = "";
        ssh_password = "";
        rstOverride = false;
        isSwitching = true;
        current_proc = 12;
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        DISP.print("SSH Channel open error.");
        Serial.println("SSH Channel open error.");
        delay(1000);
        return;
    }

    if (ssh_channel_request_pty(channel) != SSH_OK) {
      ssh_host = ""; 
        ssh_user = "";
        ssh_password = "";
        rstOverride = false;
        isSwitching = true;
        current_proc = 12;
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        DISP.print("SSH PTY request error.");
        Serial.println("SSH PTY request error.");
        delay(1000);
        return;
    }

    if (ssh_channel_request_shell(channel) != SSH_OK) {
        ssh_host = ""; 
        ssh_user = "";
        ssh_password = "";
        rstOverride = false;
        isSwitching = true;
        current_proc = 12;
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        DISP.print("SSH Shell request error.");
        Serial.println("SSH Shell request error.");
        delay(1000);
        return;
    }
    ssh_host = ""; 
    ssh_user = "";
    ssh_password = "";
    DISP.print("SSH setup completed.");    
    Serial.println("SSH setup completed.");
}

void ssh_loop() {
    M5Cardputer.update();

    bool controlMode = M5Cardputer.BtnA.isPressed(); // Check if btnA is pressed for control mode

    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
        unsigned long currentMillis = millis();
        if (currentMillis - lastKeyPressMillis >= debounceDelay) {
            lastKeyPressMillis = currentMillis;
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

            for (auto i : status.word) {
                if (controlMode) {
                    // If btnA is held down, send control character instead
                    char ctrlChar = mapToControlCharacter(i);
                    ssh_channel_write(channel, &ctrlChar, 1);
                } else {
                    // Normal character handling
                    commandBuffer += i;
                    DISP.print(i);
                    Serial.print(i);
                    cursorY = DISP.getCursorY();
                }
            }

            if (status.del && commandBuffer.length() > 2) {
                commandBuffer.remove(commandBuffer.length() - 1);
                DISP.setCursor(DISP.getCursorX() - 12, DISP.getCursorY());
                DISP.print(" ");
                DISP.setCursor(DISP.getCursorX() - 12, DISP.getCursorY());
                cursorY = DISP.getCursorY();
            }

            if (status.enter) {
                commandBuffer.trim(); // Trim the command buffer to remove accidental whitespaces/newlines
                String message = commandBuffer.substring(2); // Get the command part, exclude the "> "
                ssh_channel_write(channel, message.c_str(), message.length()); // Send the command
                ssh_channel_write(channel, "\r", 1); // Send exactly one carriage return (try "\n" or "\r\n" if needed)

                commandBuffer = "> "; // Reset command buffer
                DISP.print('\n'); // Move to the next line on display
                cursorY = DISP.getCursorY(); // Update cursor position
            }
        }
    }

    // Check if the cursor has reached the bottom of the display
    if (cursorY > DISP.height() - lineHeight) {
        DISP.scroll(0, -lineHeight);
        cursorY -= lineHeight;
        DISP.setCursor(DISP.getCursorX(), cursorY);
    }

    // Read data from SSH server and display it, handling ANSI sequences
    char buffer[128]; // Reduced buffer size for less memory usage
    int nbytes = ssh_channel_read_nonblocking(channel, buffer, sizeof(buffer), 0);
    bool isAnsiSequence = false; // To track when we are inside an ANSI sequence

    if (nbytes > 0) {
        for (int i = 0; i < nbytes; ++i) {
            char c = buffer[i];
            if (filterAnsiSequences) {
                if (c == '\033') {
                    isAnsiSequence = true; // Enter ANSI sequence mode
                } else if (isAnsiSequence) {
                    if (isalpha(c)) {
                        isAnsiSequence = false; // Exit ANSI sequence mode at the end character
                    }
                } else {
                    if (c == '\r') continue; // Ignore carriage return
                    DISP.write(c);
                    cursorY = DISP.getCursorY();
                }
            } else {
                if (c == '\r') continue; // Ignore carriage return
                DISP.write(c);
                cursorY = DISP.getCursorY();
            }
        }
    }

    // Handle channel closure and other conditions
    if (nbytes < 0 || ssh_channel_is_closed(channel)) {
        rstOverride = false;
        isSwitching = true;
        current_proc = 12; 
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        ssh_disconnect(my_ssh_session);
        ssh_free(my_ssh_session);
        DISP.println("\nSSH session closed.");
        delay(1000);
        return; // Exit the loop upon session closure
    }
}


