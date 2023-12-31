
bool sdcardMounted = false;
#if defined(SDCARD)
  #include <FS.h>
  #include <SD.h>
  #include <SPI.h>
  SPIClass* sdcardSPI = NULL;
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
  sdcardSPI = new SPIClass(FSPI);
  sdcardSPI->begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);

  delay(10);

  if (!SD.begin(SD_CS_PIN, *sdcardSPI)) {
    Serial.println("Failed to mount SDCARD");
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
