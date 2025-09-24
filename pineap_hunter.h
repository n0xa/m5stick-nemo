// PineAP Hunter - WiFi Pineapple Detection System
// Detects Access Points advertising multiple ESSIDs (WiFi Pineapple signature)
// Defensive Security Tool for M5Stick-NEMO

#ifndef PINEAP_HUNTER_H
#define PINEAP_HUNTER_H

#include "WiFi.h"
#include <vector>
#include <map>
#include <algorithm>

// Data structures for PineAP Hunter
struct SSIDRecord {
  String essid;
  int32_t rssi;
  uint32_t last_seen;

  SSIDRecord(const String& ssid, int32_t signal) : essid(ssid), rssi(signal), last_seen(millis()) {}
};

struct PineRecord {
  uint8_t bssid[6];           // MAC address
  std::vector<SSIDRecord> essids;  // Associated network names with RSSI
  int32_t rssi;               // Signal strength of most recent scan
  uint32_t last_seen;         // Timestamp of last detection

  PineRecord() : rssi(-100), last_seen(0) {
    memset(bssid, 0, 6);
  }
};

struct PineAPHunterStats {
  std::vector<PineRecord> detected_pineaps;
  std::map<String, std::vector<SSIDRecord>> scan_buffer;  // BSSID -> SSIDs with RSSI
  uint32_t total_scans = 0;
  uint32_t last_scan_time = 0;
  uint32_t scan_cycle_start = 0;
  bool list_changed = false;
  int selected_bssid_index = 0; // Which BSSID is selected for SSID list view
  int view_mode = 0;  // 0=main list, 1=BSSID details, 2=SSID list
};

// // Global state
// extern PineAPHunterStats pineap_hunter_stats;
// extern bool pineap_hunter_active;
// extern uint32_t last_beep_time;

// Function declarations
void pineap_hunter_setup();
void pineap_hunter_loop();
void pineap_hunter_cleanup();
void scan_and_analyze();
void process_scan_results();
void update_pineapple_list();
void update_display();
void draw_main_list();
void draw_bssid_details();
void draw_ssid_list();
void add_scan_result(const String& bssid_str, const String& essid, int32_t rssi);
void maintain_buffer_size();
bool is_pineapple_detected(const std::vector<String>& essids);
String bssid_to_string(const uint8_t* bssid);
void string_to_bssid(const String& bssid_str, uint8_t* bssid);
void play_alert_beep();
void handle_main_list_input();
void handle_bssid_details_input();
void handle_ssid_list_input();

#endif