// Deauth Hunter - WiFi Deauthentication Attack Detection
// Based on ESP32Marauder's deauth sniffing implementation
// Adapted for M5Stick-NEMO

#ifndef DEAUTH_HUNTER_H
#define DEAUTH_HUNTER_H

#include "WiFi.h"
#include "esp_wifi.h"
#include <vector>

// WiFi frame structure definitions (from ESP32Marauder)
typedef struct {
  int16_t fctl;
  int16_t duration;
  uint8_t da;
  uint8_t sa;
  uint8_t bssid;
  int16_t seqctl;
  unsigned char payload[];
} __attribute__((packed)) WifiMgmtHdr;

typedef struct {
  uint8_t payload[0];
  WifiMgmtHdr hdr;
} wifi_ieee80211_packet_t;

// Deauth Hunter globals
struct DeauthStats {
  uint32_t total_deauths = 0;
  uint32_t unique_aps = 0;
  int32_t rssi_sum = 0;
  uint32_t rssi_count = 0;
  int32_t avg_rssi = -90;
  uint32_t last_reset_time = 0;
};

// Channel hopping configuration
const uint8_t WIFI_CHANNELS[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const uint8_t NUM_CHANNELS = sizeof(WIFI_CHANNELS) / sizeof(WIFI_CHANNELS[0]);

// Global state
extern DeauthStats deauth_stats;
extern uint8_t current_channel_idx;
extern uint32_t last_channel_change;
extern uint32_t scan_cycle_start;
extern bool deauth_hunter_active;
extern std::vector<String> seen_ap_macs;

// Function declarations
void deauth_hunter_setup();
void deauth_hunter_loop();
void deauth_hunter_cleanup();
void start_deauth_monitoring();
void stop_deauth_monitoring();
void hop_channel();
void reset_stats_if_needed();
void add_unique_ap(const char* mac);
int calculate_rssi_bars(int rssi);
void draw_rssi_bar(int bars, int rssi);
static void deauth_sniffer_callback(void* buf, wifi_promiscuous_pkt_type_t type);
static void extract_mac(char *addr, uint8_t* data, uint16_t offset);

#endif