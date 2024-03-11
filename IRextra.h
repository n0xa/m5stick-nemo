#include <FS.h>
#include <SD.h>
#include <SPI.h>  
#include <IRremoteESP8266.h>
#include <IRsend.h>

#define IR_DATA_BUFFER_SIZE 2000

File databaseFile;


void sendRawCommand(int frequency, String rawData);
void sendNECextCommand(String address, String command);
void sendNECCommand(String address, String command);
void sendRC5Command(String address, String command);
void sendSamsungCommand(String address, String command);
void sendSonyCommand(String address, String command);
void otherIRcodes();

//Setup
void otherIRcodes() {
  //Serial.begin(115200);

  databaseFile = SD.open("/Power_off.txt");
  if (!databaseFile) {
    Serial.println("Failed to open database file.");
    return;
  }
  Serial.println("Opened database file.");
  String line;
  while (databaseFile.available()) {
    line = databaseFile.readStringUntil('\n');
    if (line.startsWith("type:")) {
      String type = line.substring(5);
      type.trim();
      //Serial.println(type);
      //Serial.println("type1");
      if (type == "raw") {
        //Serial.println("RAW");
        int frequency = 0;
        String rawData = "";
        while (databaseFile.available()) {
          line = databaseFile.readStringUntil('\n');
          if (line.startsWith("frequency:")) {
            String frequencyString = line.substring(10);
            frequencyString.trim();
            frequency = frequencyString.toInt();
          } else if (line.startsWith("data:")) {
            rawData = line.substring(5);
            rawData.trim();
          } else if (line.indexOf("#") != -1) {
            //Serial.println(frequency);
            //Serial.println(rawData);
            sendRawCommand(frequency, rawData);
            rawData = "";
            frequency = 0;
            type = "";
            line = "";
            break;
          }
        }
      } else if (type == "parsed") {
        String protocol = "";
        String address = "";
        String command = "";
        //Serial.println("PARSED");
        while (databaseFile.available()) {
          line = databaseFile.readStringUntil('\n');
          if (line.startsWith("protocol:")) {
            protocol = line.substring(9);
            protocol.trim();
            //Serial.println(protocol);
          } else if (line.startsWith("address:")) {
            address = line.substring(8);
            address.trim();
            //Serial.println(address);
          } else if (line.startsWith("command:")) {
            command = line.substring(8);
            command.trim();
            //Serial.println(command);
          } else if (line.indexOf("#") != -1) {
            if (protocol == "NECext") {
              sendNECextCommand(address, command);
            } else if (protocol == "NEC") {
              sendNECCommand(address, command);
            } else if (protocol == "RC5") {
              sendRC5Command(address, command);
            } else if (protocol == "Samsung") {
              sendSamsungCommand(address, command);
            } else if (protocol.startsWith("SIRC")) {
              sendSonyCommand(address, command);
            }
            protocol = "";
            address = "";
            command = "";
            type = "";
            line = "";
            break;
          }
        }
      }
    }
    //else{
      //Serial.println("closed1");
    //}

  }
  databaseFile.close();
  //Serial.println("closed");
  //Serial.println("closed");
  //change to finished extra
  //Serial.println("EXTRA finished");
}

//IR commands
void sendNECCommand(String address, String command) {
  uint32_t addressValue = strtoul(address.c_str(), nullptr, 16);
  uint32_t commandValue = strtoul(command.c_str(), nullptr, 16);
  irsend.sendNEC(addressValue, commandValue, 32);
  //Serial.println("Sent1");
}

void sendNECextCommand(String address, String command) {
  uint32_t addressValue = strtoul(address.c_str(), nullptr, 16);
  uint32_t commandValue = strtoul(command.c_str(), nullptr, 16);
  irsend.sendNEC(addressValue, commandValue, 32);
  //Serial.println("Sent2");
}

void sendRC5Command(String address, String command) {
  uint32_t addressValue = strtoul(address.c_str(), nullptr, 16);
  uint32_t commandValue = strtoul(command.c_str(), nullptr, 16);
  irsend.sendRC5(addressValue, commandValue, 12);
  //Serial.println("Sent3");
}

void sendSamsungCommand(String address, String command) {
  uint64_t data = ((uint64_t)strtoul(address.c_str(), nullptr, 16) << 32) | strtoul(command.c_str(), nullptr, 16);
  irsend.sendSamsung36(data, 36);
  //Serial.println("Sent4");
}

void sendSonyCommand(String address, String command) {
  uint16_t data = (uint16_t)strtoul(command.c_str(), nullptr, 16);
  uint16_t addressValue = (uint16_t)strtoul(address.c_str(), nullptr, 16);
  irsend.sendSony(addressValue, data);
  //Serial.println("Sent5");
}

void sendRawCommand(int frequency, String rawData) {
  uint16_t dataBuffer[IR_DATA_BUFFER_SIZE];
  int count = 0;

  // Parse raw data string
  while (rawData.length() > 0 && count < IR_DATA_BUFFER_SIZE) {
    int delimiterIndex = rawData.indexOf(' ');
    if (delimiterIndex == -1) {
      delimiterIndex = rawData.length();
    }
    String dataChunk = rawData.substring(0, delimiterIndex);
    rawData.remove(0, delimiterIndex + 1);
    dataBuffer[count++] = dataChunk.toInt();
  }

  //Serial.println("Parsing raw data complete.");

  // Send raw command
  irsend.sendRaw(dataBuffer, count, frequency);

  //Serial.println("Sent6");
}
