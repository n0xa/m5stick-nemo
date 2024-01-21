
bool sdcardMounted = false;
#if defined(SDCARD)
  #include <FS.h>
  #include <SD.h>
  #include <SPI.h>
  SPIClass sdcardSPI;
  SemaphoreHandle_t sdcardSemaphore;

  void appendToFile(fs::FS& fs, const char* path, const char* text) {
    if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE) {
      File file = fs.open(path, FILE_APPEND);
      if (!file) {
        Serial.println("Failed to open file for appending");
        xSemaphoreGive(sdcardSemaphore);
        return;
      }
      Serial.printf("Appending text '%s' to file: %s\n", text, path);
      if (file.println(text)) {
        Serial.println("Text appended");
      } else {
        Serial.println("Append failed");
      }
      file.close();
      xSemaphoreGive(sdcardSemaphore);
    }
  }
#endif

bool setupSdCard() {
#if defined(SDCARD)
  sdcardSemaphore = xSemaphoreCreateMutex();
  sdcardSPI.begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN); // start SPI communications

  delay(10);

  if (!SD.begin(SD_CS_PIN, sdcardSPI)) { //excluded * -> poiter indicator -
    Serial.println("Failed to mount SDCARD");
    sdcardSPI.end(); // Closes SPI connections and release header pins.
    return false;
  } else {
    Serial.println("SDCARD mounted successfully");
    sdcardMounted = true;
    return true;
  }
#else
  return false;
#endif
}

void ToggleSDCard()
{
  if (sdcardMounted == true) {
    sdcardMounted = false;
    uint8_t cardType = NULL;
    uint64_t cardSize = NULL;
    sdcardSPI.end(); // Closes SPI connections and release pins.
    DISP.println("Card Unmouted..");
    DISP.println("pin header released.");
    Serial.println("Card Unmounted...");
  } else {
    sdcardSPI.begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
    delay(10);

    if (!SD.begin(SD_CS_PIN, sdcardSPI)) {
      Serial.println("Card Mount Failed");
      DISP.println("Card Mount Failed");
      sdcardSPI.end();

    } else {
      // 
      sdcardMounted = true;
      uint8_t cardType = SD.cardType();
      if (cardType == CARD_NONE) {
        DISP.println("None SD Card");
        Serial.println("None SD Card");
      }
      DISP.print("SD Card Type: ");
      if (cardType == CARD_MMC) {
        DISP.println("MMC");
        Serial.println("MMC");
      } else if (cardType == CARD_SD) {
        DISP.println("SDSC");
        Serial.println("SDSC");
      } else if (cardType == CARD_SDHC) {
        DISP.println("SDHC");
        Serial.println("SDHC");
      } else {
        DISP.println("UNKNOWN");
        Serial.println("UNKNOWN");
      }

      uint64_t cardSize = SD.cardSize() / (1024 * 1024);
      DISP.printf("SD Card Size: %lluMB\n", cardSize);
      Serial.printf("SD Card Size: %lluMB\n", cardSize);

    }
  }
  delay(5000);

}

